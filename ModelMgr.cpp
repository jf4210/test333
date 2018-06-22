//#include "stdafx.h"
#include "ModelMgr.h"


CModelMgr::CModelMgr()
{
}


CModelMgr::~CModelMgr()
{
}

pMODEL CModelMgr::LoadModelFile(std::string strModelPath)
{
	std::string strJsnModel = strModelPath + "\\model.dat";

	_strLog.clear();

	std::string strJsnData;
	std::ifstream in(strJsnModel);
	if (!in)
	{
		//LOG(ERROR) << "LoadModelFile fail. " << strJsnModel << " open fail.";
		std::stringstream ss;
		ss << "LoadModelFile fail. " << strJsnModel << " open fail.";
		_strLog.append(ss.str());
		return NULL;
	}

	std::string strJsnLine;
	while (!in.eof())
	{
		getline(in, strJsnLine);					//不过滤空格
		strJsnData.append(strJsnLine);
	}
	// 	while (in >> strJsnLine)					//读入的文件如果有空格，将会去除
	// 		strJsnData.append(strJsnLine);

	in.close();

	std::string strFileData;
#ifdef USES_FILE_ENC
	if (!decString(strJsnData, strFileData))
		strFileData = strJsnData;
#else
	strFileData = strJsnData;
#endif

	pMODEL pModel = NULL;
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result;
	try
	{
		result = parser.parse(strFileData);		//strJsnData
		Poco::JSON::Object::Ptr objData = result.extract<Poco::JSON::Object::Ptr>();

		pModel = new MODEL;
		pModel->strModelName = CMyCodeConvert::Utf8ToGb2312(objData->get("modelName").convert<std::string>());
		pModel->strModelDesc = CMyCodeConvert::Utf8ToGb2312(objData->get("modelDesc").convert<std::string>());
		if (objData->has("modelType"))
			pModel->nType = objData->get("modelType").convert<int>();
		else
			pModel->nType = 0;
		pModel->nSaveMode = objData->get("modeSaveMode").convert<int>();
		pModel->nPicNum = objData->get("paperModelCount").convert<int>();
		pModel->nEnableModify = objData->get("enableModify").convert<int>();
		pModel->nABModel = objData->get("abPaper").convert<int>();
		pModel->nHasHead = objData->get("hasHead").convert<int>();
		if (objData->has("hasElectOmr"))
			pModel->nHasElectOmr = objData->get("hasElectOmr").convert<int>();
		if (objData->has("nZkzhType"))
			pModel->nZkzhType = objData->get("nZkzhType").convert<int>();
		if (objData->has("nScanDpi"))
			pModel->nScanDpi = objData->get("nScanDpi").convert<int>();
		if (objData->has("nScanAutoCut"))
			pModel->nAutoCut = objData->get("nScanAutoCut").convert<int>();
		if (objData->has("nScanSize"))
			pModel->nScanSize = objData->get("nScanSize").convert<int>();
		if (objData->has("nScanType"))
			pModel->nScanType = objData->get("nScanType").convert<int>();
		if (objData->has("nUseWordAnchorPoint"))
			pModel->nUseWordAnchorPoint = objData->get("nUseWordAnchorPoint").convert<int>();
		if (objData->has("nCharacterAnchorPoint"))
			pModel->nCharacterAnchorPoint = objData->get("nCharacterAnchorPoint").convert<int>();
		if (objData->has("nUsePagination"))
			pModel->nUsePagination = objData->get("nUsePagination").convert<int>();
		if (objData->has("nChkLostCorner"))
			pModel->nChkLostCorner = objData->get("nChkLostCorner").convert<int>();
		if (objData->has("nCardType"))
			pModel->nCardType = objData->get("nCardType").convert<int>();

		// 		if (objData->has("gaussKernel"))
		// 			pModel->nGaussKernel = objData->get("gaussKernel").convert<int>();
		// 		if (objData->has("sharpKernel"))
		// 			pModel->nSharpKernel = objData->get("sharpKernel").convert<int>();
		// 		if (objData->has("cannyKernel"))
		// 			pModel->nCannyKernel = objData->get("cannyKernel").convert<int>();
		// 		if (objData->has("dilateKernel"))
		// 			pModel->nDilateKernel = objData->get("dilateKernel").convert<int>();

		if (objData->has("nExamId"))
			pModel->nExamID = objData->get("nExamId").convert<int>();
		if (objData->has("nSubjectId"))
			pModel->nSubjectID = objData->get("nSubjectId").convert<int>();
		if (objData->has("examUUID"))
			pModel->strExamUUID = objData->get("examUUID").convert<std::string>();
		if (objData->has("subjectUUID"))
			pModel->strSubjectUUID = objData->get("subjectUUID").convert<std::string>();

		Poco::JSON::Array::Ptr arrayPapers = objData->getArray("paperInfo");
		for (int i = 0; i < arrayPapers->size(); i++)
		{
			Poco::JSON::Object::Ptr jsnPaperObj = arrayPapers->getObject(i);

			pPAPERMODEL paperModelInfo = new PAPERMODEL;
			paperModelInfo->nPaper = jsnPaperObj->get("paperNum").convert<int>();
			paperModelInfo->strModelPicName = CMyCodeConvert::Utf8ToGb2312(jsnPaperObj->get("modelPicName").convert<std::string>());
			paperModelInfo->strModelPicPath = strModelPath + "\\" + paperModelInfo->strModelPicName;

			if (jsnPaperObj->has("picW"))			//add on 16.8.29
				paperModelInfo->nPicW = jsnPaperObj->get("picW").convert<int>();
			if (jsnPaperObj->has("picH"))			//add on 16.8.29
				paperModelInfo->nPicH = jsnPaperObj->get("picH").convert<int>();
			if (jsnPaperObj->has("picSaveRotion"))
				paperModelInfo->nPicSaveRotation = jsnPaperObj->get("picSaveRotion").convert<int>();

			paperModelInfo->rtHTracker.x = jsnPaperObj->get("rtHTracker.x").convert<int>();
			paperModelInfo->rtHTracker.y = jsnPaperObj->get("rtHTracker.y").convert<int>();
			paperModelInfo->rtHTracker.width = jsnPaperObj->get("rtHTracker.width").convert<int>();
			paperModelInfo->rtHTracker.height = jsnPaperObj->get("rtHTracker.height").convert<int>();
			paperModelInfo->rtVTracker.x = jsnPaperObj->get("rtVTracker.x").convert<int>();
			paperModelInfo->rtVTracker.y = jsnPaperObj->get("rtVTracker.y").convert<int>();
			paperModelInfo->rtVTracker.width = jsnPaperObj->get("rtVTracker.width").convert<int>();
			paperModelInfo->rtVTracker.height = jsnPaperObj->get("rtVTracker.height").convert<int>();
			paperModelInfo->rcSNTracker.rt.x = jsnPaperObj->get("rtSNTracker.x").convert<int>();
			paperModelInfo->rcSNTracker.rt.y = jsnPaperObj->get("rtSNTracker.y").convert<int>();
			paperModelInfo->rcSNTracker.rt.width = jsnPaperObj->get("rtSNTracker.width").convert<int>();
			paperModelInfo->rcSNTracker.rt.height = jsnPaperObj->get("rtSNTracker.height").convert<int>();
			if (jsnPaperObj->has("rtSNTracker.nRecogFlag"))
				paperModelInfo->rcSNTracker.nRecogFlag = jsnPaperObj->get("rtSNTracker.nRecogFlag").convert<int>();

			Poco::JSON::Array::Ptr arraySelHTracker = jsnPaperObj->getArray("hTrackerRect");
			Poco::JSON::Array::Ptr arraySelVTracker = jsnPaperObj->getArray("vTrackerRect");
			Poco::JSON::Array::Ptr arraySelFixRoi = jsnPaperObj->getArray("selRoiRect");
			Poco::JSON::Array::Ptr arrayFixCP = jsnPaperObj->getArray("FixCP");
			Poco::JSON::Array::Ptr arrayHHead = jsnPaperObj->getArray("H_Head");
			Poco::JSON::Array::Ptr arrayVHead = jsnPaperObj->getArray("V_Head");
			Poco::JSON::Array::Ptr arrayPage;
			if (jsnPaperObj->has("Pagination"))
				arrayPage = jsnPaperObj->getArray("Pagination");
			Poco::JSON::Array::Ptr arrayABModel = jsnPaperObj->getArray("ABModel");
			Poco::JSON::Array::Ptr arrayCourse = jsnPaperObj->getArray("Course");
			Poco::JSON::Array::Ptr arrayQKCP = jsnPaperObj->getArray("QKCP");
			Poco::JSON::Array::Ptr arrayWJCP;
			if (jsnPaperObj->has("WJCP"))
				arrayWJCP = jsnPaperObj->getArray("WJCP");
			Poco::JSON::Array::Ptr arrayGrayCP = jsnPaperObj->getArray("GrayCP");
			Poco::JSON::Array::Ptr arrayWhiteCP = jsnPaperObj->getArray("WhiteCP");
			Poco::JSON::Array::Ptr arraySn = jsnPaperObj->getArray("snList");
			Poco::JSON::Array::Ptr arrayOmr = jsnPaperObj->getArray("selOmrRect");
			Poco::JSON::Array::Ptr arrayElectOmr;
			if (jsnPaperObj->has("electOmrList"))
				arrayElectOmr = jsnPaperObj->getArray("electOmrList");
			Poco::JSON::Array::Ptr arrayCharacterAnchorArea;
			if (jsnPaperObj->has("characterAnchorArea"))
			{
				arrayCharacterAnchorArea = jsnPaperObj->getArray("characterAnchorArea");

				//加载模板图像，只有存在文字定时时才需要，用到了模板匹配
				//CString strPicPath = g_strCurrentPath + _T("Model\\") + A2T(pModel->strModelName.c_str()) + _T("\\") + A2T(paperModelInfo->strModelPicName.c_str());
				std::string strPicPath = _strModelDirPath + "\\" + paperModelInfo->strModelPicName;
				paperModelInfo->matModel = cv::imread(strPicPath);	//(std::string)(CT2CA)strPicPath
			}
			Poco::JSON::Array::Ptr arryZgt;
			if (jsnPaperObj->has("zgt"))
				arryZgt = jsnPaperObj->getArray("zgt");

			for (int i = 0; i < arrayFixCP->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arrayFixCP->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

				if (jsnRectInfoObj->has("standardArea"))
					rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
				if (jsnRectInfoObj->has("standardDensity"))
					rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
				if (jsnRectInfoObj->has("standardMeanGray"))
					rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
				if (jsnRectInfoObj->has("standardStddev"))
					rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lFix.push_back(rc);
			}
			for (int i = 0; i < arrayHHead->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arrayHHead->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

				if (jsnRectInfoObj->has("standardArea"))
					rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
				if (jsnRectInfoObj->has("standardDensity"))
					rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
				if (jsnRectInfoObj->has("standardMeanGray"))
					rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
				if (jsnRectInfoObj->has("standardStddev"))
					rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lH_Head.push_back(rc);
			}
			for (int i = 0; i < arrayVHead->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arrayVHead->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

				if (jsnRectInfoObj->has("standardArea"))
					rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
				if (jsnRectInfoObj->has("standardDensity"))
					rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
				if (jsnRectInfoObj->has("standardMeanGray"))
					rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
				if (jsnRectInfoObj->has("standardStddev"))
					rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lV_Head.push_back(rc);
			}
			if (jsnPaperObj->has("Pagination"))
			{
				for (int i = 0; i < arrayPage->size(); i++)
				{
					Poco::JSON::Object::Ptr jsnRectInfoObj = arrayPage->getObject(i);
					RECTINFO rc;
					rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
					rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
					rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

					if (jsnRectInfoObj->has("standardArea"))
						rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
					if (jsnRectInfoObj->has("standardDensity"))
						rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
					if (jsnRectInfoObj->has("standardMeanGray"))
						rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
					if (jsnRectInfoObj->has("standardStddev"))
						rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

					rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
					rc.nHItem = jsnRectInfoObj->get("hHeadItem").convert<int>();
					rc.nVItem = jsnRectInfoObj->get("vHeadItem").convert<int>();
					rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
					rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
					rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
					rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

					if (jsnRectInfoObj->has("gaussKernel"))
						rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
					if (jsnRectInfoObj->has("sharpKernel"))
						rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
					if (jsnRectInfoObj->has("cannyKernel"))
						rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
					if (jsnRectInfoObj->has("dilateKernel"))
						rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

					paperModelInfo->lPagination.push_back(rc);
				}
			}
			for (int i = 0; i < arrayABModel->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arrayABModel->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

				if (jsnRectInfoObj->has("standardArea"))
					rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
				if (jsnRectInfoObj->has("standardDensity"))
					rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
				if (jsnRectInfoObj->has("standardMeanGray"))
					rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
				if (jsnRectInfoObj->has("standardStddev"))
					rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.nHItem = jsnRectInfoObj->get("hHeadItem").convert<int>();
				rc.nVItem = jsnRectInfoObj->get("vHeadItem").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lABModel.push_back(rc);
			}
			for (int i = 0; i < arrayCourse->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arrayCourse->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

				if (jsnRectInfoObj->has("standardArea"))
					rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
				if (jsnRectInfoObj->has("standardDensity"))
					rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
				if (jsnRectInfoObj->has("standardMeanGray"))
					rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
				if (jsnRectInfoObj->has("standardStddev"))
					rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.nHItem = jsnRectInfoObj->get("hHeadItem").convert<int>();
				rc.nVItem = jsnRectInfoObj->get("vHeadItem").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lCourse.push_back(rc);
			}
			for (int i = 0; i < arrayQKCP->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arrayQKCP->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

				if (jsnRectInfoObj->has("standardArea"))
					rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
				if (jsnRectInfoObj->has("standardDensity"))
					rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
				if (jsnRectInfoObj->has("standardMeanGray"))
					rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
				if (jsnRectInfoObj->has("standardStddev"))
					rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.nHItem = jsnRectInfoObj->get("hHeadItem").convert<int>();
				rc.nVItem = jsnRectInfoObj->get("vHeadItem").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lQK_CP.push_back(rc);
			}
			if (jsnPaperObj->has("WJCP"))
			{
				for (int i = 0; i < arrayWJCP->size(); i++)
				{
					Poco::JSON::Object::Ptr jsnRectInfoObj = arrayWJCP->getObject(i);
					RECTINFO rc;
					rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
					rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
					rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

					if (jsnRectInfoObj->has("standardArea"))
						rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
					if (jsnRectInfoObj->has("standardDensity"))
						rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
					if (jsnRectInfoObj->has("standardMeanGray"))
						rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
					if (jsnRectInfoObj->has("standardStddev"))
						rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

					rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
					rc.nHItem = jsnRectInfoObj->get("hHeadItem").convert<int>();
					rc.nVItem = jsnRectInfoObj->get("vHeadItem").convert<int>();
					rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
					rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
					rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
					rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

					if (jsnRectInfoObj->has("gaussKernel"))
						rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
					if (jsnRectInfoObj->has("sharpKernel"))
						rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
					if (jsnRectInfoObj->has("cannyKernel"))
						rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
					if (jsnRectInfoObj->has("dilateKernel"))
						rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

					paperModelInfo->lWJ_CP.push_back(rc);
				}
			}
			for (int i = 0; i < arrayGrayCP->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arrayGrayCP->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

				if (jsnRectInfoObj->has("standardArea"))
					rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
				if (jsnRectInfoObj->has("standardDensity"))
					rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
				if (jsnRectInfoObj->has("standardMeanGray"))
					rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
				if (jsnRectInfoObj->has("standardStddev"))
					rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.nHItem = jsnRectInfoObj->get("hHeadItem").convert<int>();
				rc.nVItem = jsnRectInfoObj->get("vHeadItem").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lGray.push_back(rc);
			}
			for (int i = 0; i < arrayWhiteCP->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arrayWhiteCP->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();

				if (jsnRectInfoObj->has("standardArea"))
					rc.fStandardArea = jsnRectInfoObj->get("standardArea").convert<float>();
				if (jsnRectInfoObj->has("standardDensity"))
					rc.fStandardDensity = jsnRectInfoObj->get("standardDensity").convert<float>();
				if (jsnRectInfoObj->has("standardMeanGray"))
					rc.fStandardMeanGray = jsnRectInfoObj->get("standardMeanGray").convert<float>();
				if (jsnRectInfoObj->has("standardStddev"))
					rc.fStandardStddev = jsnRectInfoObj->get("standardStddev").convert<float>();

				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.nHItem = jsnRectInfoObj->get("hHeadItem").convert<int>();
				rc.nVItem = jsnRectInfoObj->get("vHeadItem").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lWhite.push_back(rc);
			}
			for (int i = 0; i < arraySelFixRoi->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arraySelFixRoi->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				//				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();
				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lSelFixRoi.push_back(rc);
			}
			for (int i = 0; i < arraySelHTracker->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arraySelHTracker->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				//				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();
				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lSelHTracker.push_back(rc);
			}
			for (int i = 0; i < arraySelVTracker->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arraySelVTracker->getObject(i);
				RECTINFO rc;
				rc.eCPType = (CPType)jsnRectInfoObj->get("eType").convert<int>();
				rc.fStandardValuePercent = jsnRectInfoObj->get("standardValPercent").convert<float>();
				//				rc.fStandardValue = jsnRectInfoObj->get("standardVal").convert<float>();
				rc.nThresholdValue = jsnRectInfoObj->get("thresholdValue").convert<int>();
				rc.rt.x = jsnRectInfoObj->get("left").convert<int>();
				rc.rt.y = jsnRectInfoObj->get("top").convert<int>();
				rc.rt.width = jsnRectInfoObj->get("width").convert<int>();
				rc.rt.height = jsnRectInfoObj->get("height").convert<int>();

				if (jsnRectInfoObj->has("gaussKernel"))
					rc.nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
				if (jsnRectInfoObj->has("sharpKernel"))
					rc.nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
				if (jsnRectInfoObj->has("cannyKernel"))
					rc.nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
				if (jsnRectInfoObj->has("dilateKernel"))
					rc.nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

				paperModelInfo->lSelVTracker.push_back(rc);
			}
			for (int i = 0; i < arrayOmr->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arrayOmr->getObject(i);
				OMR_QUESTION objOmr;
				objOmr.nTH = jsnRectInfoObj->get("nTH").convert<int>();
				objOmr.nSingle = jsnRectInfoObj->get("nSingle").convert<int>();
				Poco::JSON::Array::Ptr omrList = jsnRectInfoObj->getArray("omrlist");
				for (int j = 0; j < omrList->size(); j++)
				{
					Poco::JSON::Object::Ptr jsnOmrObj = omrList->getObject(j);
					RECTINFO rc;
					rc.eCPType = (CPType)jsnOmrObj->get("eType").convert<int>();
					rc.fStandardValuePercent = jsnOmrObj->get("standardValPercent").convert<float>();
					rc.fStandardValue = jsnOmrObj->get("standardVal").convert<float>();

					if (jsnOmrObj->has("standardArea"))
						rc.fStandardArea = jsnOmrObj->get("standardArea").convert<float>();
					if (jsnOmrObj->has("standardDensity"))
						rc.fStandardDensity = jsnOmrObj->get("standardDensity").convert<float>();
					if (jsnOmrObj->has("standardMeanGray"))
						rc.fStandardMeanGray = jsnOmrObj->get("standardMeanGray").convert<float>();
					if (jsnOmrObj->has("standardStddev"))
						rc.fStandardStddev = jsnOmrObj->get("standardStddev").convert<float>();

					rc.nThresholdValue = jsnOmrObj->get("thresholdValue").convert<int>();
					rc.nHItem = jsnOmrObj->get("hHeadItem").convert<int>();
					rc.nVItem = jsnOmrObj->get("vHeadItem").convert<int>();
					rc.nTH = jsnOmrObj->get("nTH").convert<int>();
					rc.nAnswer = jsnOmrObj->get("nAnswer").convert<int>();
					rc.nSingle = jsnOmrObj->get("nSingle").convert<int>();
					rc.nRecogFlag = jsnOmrObj->get("nOmrRecogFlag").convert<int>();
					rc.rt.x = jsnOmrObj->get("left").convert<int>();
					rc.rt.y = jsnOmrObj->get("top").convert<int>();
					rc.rt.width = jsnOmrObj->get("width").convert<int>();
					rc.rt.height = jsnOmrObj->get("height").convert<int>();

					if (jsnOmrObj->has("gaussKernel"))
						rc.nGaussKernel = jsnOmrObj->get("gaussKernel").convert<int>();
					if (jsnOmrObj->has("sharpKernel"))
						rc.nSharpKernel = jsnOmrObj->get("sharpKernel").convert<int>();
					if (jsnOmrObj->has("cannyKernel"))
						rc.nCannyKernel = jsnOmrObj->get("cannyKernel").convert<int>();
					if (jsnOmrObj->has("dilateKernel"))
						rc.nDilateKernel = jsnOmrObj->get("dilateKernel").convert<int>();

					objOmr.lSelAnswer.push_back(rc);
				}
				paperModelInfo->lOMR2.push_back(objOmr);
			}
			for (int i = 0; i < arraySn->size(); i++)
			{
				Poco::JSON::Object::Ptr jsnRectInfoObj = arraySn->getObject(i);
				pSN_ITEM pSnItem = new SN_ITEM;
				pSnItem->nItem = jsnRectInfoObj->get("nItem").convert<int>();
				pSnItem->nRecogVal = jsnRectInfoObj->get("nRecogVal").convert<int>();
				Poco::JSON::Array::Ptr snList = jsnRectInfoObj->getArray("snList");
				for (int j = 0; j < snList->size(); j++)
				{
					Poco::JSON::Object::Ptr jsnSnObj = snList->getObject(j);
					RECTINFO rc;
					rc.eCPType = (CPType)jsnSnObj->get("eType").convert<int>();
					rc.fStandardValuePercent = jsnSnObj->get("standardValPercent").convert<float>();
					rc.fStandardValue = jsnSnObj->get("standardVal").convert<float>();

					if (jsnSnObj->has("standardArea"))
						rc.fStandardArea = jsnSnObj->get("standardArea").convert<float>();
					if (jsnSnObj->has("standardDensity"))
						rc.fStandardDensity = jsnSnObj->get("standardDensity").convert<float>();
					if (jsnSnObj->has("standardMeanGray"))
						rc.fStandardMeanGray = jsnSnObj->get("standardMeanGray").convert<float>();
					if (jsnSnObj->has("standardStddev"))
						rc.fStandardStddev = jsnSnObj->get("standardStddev").convert<float>();

					rc.nThresholdValue = jsnSnObj->get("thresholdValue").convert<int>();
					rc.nHItem = jsnSnObj->get("hHeadItem").convert<int>();
					rc.nVItem = jsnSnObj->get("vHeadItem").convert<int>();
					rc.nTH = jsnSnObj->get("nTH").convert<int>();
					rc.nSnVal = jsnSnObj->get("nSnVal").convert<int>();
					rc.nAnswer = jsnSnObj->get("nAnswer").convert<int>();
					rc.nSingle = jsnSnObj->get("nSingle").convert<int>();
					rc.nRecogFlag = jsnSnObj->get("nSnRecogFlag").convert<int>();
					rc.rt.x = jsnSnObj->get("left").convert<int>();
					rc.rt.y = jsnSnObj->get("top").convert<int>();
					rc.rt.width = jsnSnObj->get("width").convert<int>();
					rc.rt.height = jsnSnObj->get("height").convert<int>();

					if (jsnSnObj->has("gaussKernel"))
						rc.nGaussKernel = jsnSnObj->get("gaussKernel").convert<int>();
					if (jsnSnObj->has("sharpKernel"))
						rc.nSharpKernel = jsnSnObj->get("sharpKernel").convert<int>();
					if (jsnSnObj->has("cannyKernel"))
						rc.nCannyKernel = jsnSnObj->get("cannyKernel").convert<int>();
					if (jsnSnObj->has("dilateKernel"))
						rc.nDilateKernel = jsnSnObj->get("dilateKernel").convert<int>();

					pSnItem->lSN.push_back(rc);
				}
				paperModelInfo->lSNInfo.push_back(pSnItem);
			}
			if (jsnPaperObj->has("electOmrList"))
			{
				for (int i = 0; i < arrayElectOmr->size(); i++)
				{
					Poco::JSON::Object::Ptr jsnRectInfoObj = arrayElectOmr->getObject(i);
					ELECTOMR_QUESTION objElectOmr;
					objElectOmr.sElectOmrGroupInfo.nGroupID = jsnRectInfoObj->get("nGroupID").convert<int>();
					objElectOmr.sElectOmrGroupInfo.nAllCount = jsnRectInfoObj->get("nAllCount").convert<int>();
					objElectOmr.sElectOmrGroupInfo.nRealCount = jsnRectInfoObj->get("nRealCount").convert<int>();
					Poco::JSON::Array::Ptr omrList = jsnRectInfoObj->getArray("omrlist");
					for (int j = 0; j < omrList->size(); j++)
					{
						Poco::JSON::Object::Ptr jsnOmrObj = omrList->getObject(j);
						RECTINFO rc;
						rc.eCPType = (CPType)jsnOmrObj->get("eType").convert<int>();
						rc.nThresholdValue = jsnOmrObj->get("thresholdValue").convert<int>();
						rc.fStandardValuePercent = jsnOmrObj->get("standardValPercent").convert<float>();
						rc.fStandardValue = jsnOmrObj->get("standardVal").convert<float>();

						if (jsnOmrObj->has("standardArea"))
							rc.fStandardArea = jsnOmrObj->get("standardArea").convert<float>();
						if (jsnOmrObj->has("standardDensity"))
							rc.fStandardDensity = jsnOmrObj->get("standardDensity").convert<float>();
						if (jsnOmrObj->has("standardMeanGray"))
							rc.fStandardMeanGray = jsnOmrObj->get("standardMeanGray").convert<float>();
						if (jsnOmrObj->has("standardStddev"))
							rc.fStandardStddev = jsnOmrObj->get("standardStddev").convert<float>();

						rc.nTH = jsnOmrObj->get("nTH").convert<int>();
						rc.nAnswer = jsnOmrObj->get("nAnswer").convert<int>();
						rc.rt.x = jsnOmrObj->get("left").convert<int>();
						rc.rt.y = jsnOmrObj->get("top").convert<int>();
						rc.rt.width = jsnOmrObj->get("width").convert<int>();
						rc.rt.height = jsnOmrObj->get("height").convert<int>();
						rc.nHItem = jsnOmrObj->get("hHeadItem").convert<int>();
						rc.nVItem = jsnOmrObj->get("vHeadItem").convert<int>();

						if (jsnOmrObj->has("gaussKernel"))
							rc.nGaussKernel = jsnOmrObj->get("gaussKernel").convert<int>();
						if (jsnOmrObj->has("sharpKernel"))
							rc.nSharpKernel = jsnOmrObj->get("sharpKernel").convert<int>();
						if (jsnOmrObj->has("cannyKernel"))
							rc.nCannyKernel = jsnOmrObj->get("cannyKernel").convert<int>();
						if (jsnOmrObj->has("dilateKernel"))
							rc.nDilateKernel = jsnOmrObj->get("dilateKernel").convert<int>();

						objElectOmr.lItemInfo.push_back(rc);
					}
					paperModelInfo->lElectOmr.push_back(objElectOmr);
				}
			}
			if (jsnPaperObj->has("characterAnchorArea"))
			{
				for (int i = 0; i < arrayCharacterAnchorArea->size(); i++)
				{
					Poco::JSON::Object::Ptr jsnRectInfoObj = arrayCharacterAnchorArea->getObject(i);
					pST_CHARACTER_ANCHOR_AREA pobjCharacterAnchorArea = new ST_CHARACTER_ANCHOR_AREA();
					pobjCharacterAnchorArea->nIndex = jsnRectInfoObj->get("nIndex").convert<int>();
					pobjCharacterAnchorArea->nThresholdValue = jsnRectInfoObj->get("nThreshold").convert<int>();
					if (jsnRectInfoObj->has("nConfidence"))
						pobjCharacterAnchorArea->nCharacterConfidence = jsnRectInfoObj->get("nConfidence").convert<int>();
					if (jsnRectInfoObj->has("nRectsInArea"))
						pobjCharacterAnchorArea->nRects = jsnRectInfoObj->get("nRectsInArea").convert<int>();
					pobjCharacterAnchorArea->nGaussKernel = jsnRectInfoObj->get("gaussKernel").convert<int>();
					pobjCharacterAnchorArea->nSharpKernel = jsnRectInfoObj->get("sharpKernel").convert<int>();
					pobjCharacterAnchorArea->nCannyKernel = jsnRectInfoObj->get("cannyKernel").convert<int>();
					pobjCharacterAnchorArea->nDilateKernel = jsnRectInfoObj->get("dilateKernel").convert<int>();

					pobjCharacterAnchorArea->rt.x = jsnRectInfoObj->get("left").convert<int>();
					pobjCharacterAnchorArea->rt.y = jsnRectInfoObj->get("top").convert<int>();
					pobjCharacterAnchorArea->rt.width = jsnRectInfoObj->get("width").convert<int>();
					pobjCharacterAnchorArea->rt.height = jsnRectInfoObj->get("height").convert<int>();

					Poco::JSON::Array::Ptr omrList = jsnRectInfoObj->getArray("characterAnchorPointList");
					for (int j = 0; j < omrList->size(); j++)
					{
						Poco::JSON::Object::Ptr jsnOmrObj = omrList->getObject(j);
						pST_CHARACTER_ANCHOR_POINT pstCharacterRt = new ST_CHARACTER_ANCHOR_POINT();;
						RECTINFO rc;
						rc.eCPType = (CPType)jsnOmrObj->get("eType").convert<int>();
						rc.nThresholdValue = jsnOmrObj->get("thresholdValue").convert<int>();
						rc.fStandardValuePercent = jsnOmrObj->get("standardValPercent").convert<float>();
						rc.fStandardValue = jsnOmrObj->get("standardVal").convert<float>();

						if (jsnOmrObj->has("standardArea"))
							rc.fStandardArea = jsnOmrObj->get("standardArea").convert<float>();
						if (jsnOmrObj->has("standardDensity"))
							rc.fStandardDensity = jsnOmrObj->get("standardDensity").convert<float>();
						if (jsnOmrObj->has("standardMeanGray"))
							rc.fStandardMeanGray = jsnOmrObj->get("standardMeanGray").convert<float>();
						if (jsnOmrObj->has("standardStddev"))
							rc.fStandardStddev = jsnOmrObj->get("standardStddev").convert<float>();

						rc.nTH = jsnOmrObj->get("nTH").convert<int>();
						rc.nAnswer = jsnOmrObj->get("nAnswer").convert<int>();
						rc.rt.x = jsnOmrObj->get("left").convert<int>();
						rc.rt.y = jsnOmrObj->get("top").convert<int>();
						rc.rt.width = jsnOmrObj->get("width").convert<int>();
						rc.rt.height = jsnOmrObj->get("height").convert<int>();
						rc.nHItem = jsnOmrObj->get("hHeadItem").convert<int>();
						rc.nVItem = jsnOmrObj->get("vHeadItem").convert<int>();

						if (jsnOmrObj->has("gaussKernel"))
							rc.nGaussKernel = jsnOmrObj->get("gaussKernel").convert<int>();
						if (jsnOmrObj->has("sharpKernel"))
							rc.nSharpKernel = jsnOmrObj->get("sharpKernel").convert<int>();
						if (jsnOmrObj->has("cannyKernel"))
							rc.nCannyKernel = jsnOmrObj->get("cannyKernel").convert<int>();
						if (jsnOmrObj->has("dilateKernel"))
							rc.nDilateKernel = jsnOmrObj->get("dilateKernel").convert<int>();

						//---------------
						pstCharacterRt->nIndex = jsnOmrObj->get("nIndex").convert<int>();
						pstCharacterRt->fConfidence = jsnOmrObj->get("fConfidence").convert<double>();
						pstCharacterRt->strVal = CMyCodeConvert::Utf8ToGb2312(jsnOmrObj->get("strRecogChar").convert<std::string>());
						pstCharacterRt->rc = rc;
						pobjCharacterAnchorArea->vecCharacterRt.push_back(pstCharacterRt);
					}
					paperModelInfo->lCharacterAnchorArea.push_back(pobjCharacterAnchorArea);
				}
			}
			if (jsnPaperObj->has("zgt"))
			{
				for (int i = 0; i < arryZgt->size(); i++)
				{
					Poco::JSON::Object::Ptr jsnObj = arryZgt->getObject(i);
					ST_ZGT stZgt;
					stZgt.nType = jsnObj->get("type").convert<int>();
					stZgt.nCounts = jsnObj->get("counts").convert<int>();
					stZgt.strTh = jsnObj->get("th").convert<std::string>();
// 					stZgt.nS_Th = jsnObj->get("s_th").convert<int>();
// 					stZgt.nE_Th = jsnObj->get("e_th").convert<int>();
					Poco::JSON::Array::Ptr arryRegion = jsnObj->getArray("region");
					for (int k = 0; k < arryRegion->size(); k++)
					{
						Poco::JSON::Object::Ptr jsnRegion = arryRegion->getObject(k);
						ST_ZgtRegion stRegion;
						stRegion.nId = jsnRegion->get("id").convert<int>();
						stRegion.nPageId = jsnRegion->get("pageId").convert<int>();
						Poco::JSON::Object::Ptr jsnPos = jsnRegion->getObject("pos");
						stRegion.rt.x = jsnPos->get("x").convert<int>();
						stRegion.rt.y = jsnPos->get("y").convert<int>();
						stRegion.rt.width = jsnPos->get("w").convert<int>();
						stRegion.rt.height = jsnPos->get("h").convert<int>();
						stZgt.vecRegion.push_back(stRegion);
					}
					paperModelInfo->lZgt.push_back(stZgt);
				}
			}

			std::vector<pPAPERMODEL>::iterator itBegin = pModel->vecPaperModel.begin();
			for (; itBegin != pModel->vecPaperModel.end();)
			{
				if (paperModelInfo->nPaper < (*itBegin)->nPaper)
				{
					pModel->vecPaperModel.insert(itBegin, paperModelInfo);
					break;
				}
				else
					itBegin++;
			}
			if (itBegin == pModel->vecPaperModel.end())
				pModel->vecPaperModel.push_back(paperModelInfo);
		}
	}
	catch (Poco::JSON::JSONException& jsone)
	{
		if (pModel)
		{
			delete pModel;
			pModel = NULL;
		}
		std::string strErrInfo;
		strErrInfo.append("加载模板文件解析json失败: ");
		strErrInfo.append(jsone.message());
		//LOG(ERROR) << "LoadModelFile : " << strErrInfo;
		std::stringstream ss;
		ss << "LoadModelFile : " << strErrInfo;
		_strLog.append(ss.str());
	}
	catch (Poco::Exception& exc)
	{
		if (pModel)
		{
			delete pModel;
			pModel = NULL;
		}
		std::string strErrInfo;
		strErrInfo.append("加载模板文件解析json失败2: ");
		strErrInfo.append(exc.message());
		//LOG(ERROR) << "LoadModelFile : " << strErrInfo;
		std::stringstream ss;
		ss << "LoadModelFile : " << strErrInfo;
		_strLog.append(ss.str());
	}

	return pModel;
}

bool CModelMgr::SaveModelFile(pMODEL pModel)
{
	std::string modelPath = _strModelDirPath + pModel->strModelName;
	_strLog.clear();

	try
	{
		Poco::File fDir(CMyCodeConvert::Gb2312ToUtf8(modelPath));
		if (!fDir.exists())
			fDir.createDirectories();
	}
	catch (Poco::Exception& exc)
	{
		std::string strLog = "创建模板保存路径失败: " + exc.displayText() + "\n";
		//LOG(ERROR) << "SaveModelFile : " << strLog;
		std::stringstream ss;
		ss << "SaveModelFile : " << strLog;
		_strLog.append(ss.str());
		return false;
	}

	Poco::JSON::Object jsnModel;
	Poco::JSON::Array  jsnPicModel;
	Poco::JSON::Array  jsnPaperModel;				//卷形模板，AB卷用
	for (int i = 0; i < pModel->nPicNum; i++)
	{
		Poco::JSON::Object jsnPaperObj;

		//CString strOldPath = m_vecPaperModelInfo[i]->strModelPicPath;
		std::string strOldPath = pModel->vecPaperModel[i]->strModelPicPath;
		try
		{
			std::string strUtf8OldPath = CMyCodeConvert::Gb2312ToUtf8(strOldPath);
			std::string strUtf8ModelPath = CMyCodeConvert::Gb2312ToUtf8(modelPath);

			Poco::File modelPicPath(strUtf8OldPath);	//T2A(strOldPath)
			modelPicPath.copyTo(strUtf8ModelPath);	//T2A(modelPath)
		}
		catch (Poco::Exception &exc)
		{
			std::string strLog;
			strLog.append("file cope error: " + exc.displayText());
			std::string strGBLog = CMyCodeConvert::Utf8ToGb2312(strLog);
			_strLog.append(strGBLog);
			//LOG(WARNING) << "SaveModelFile : " << strGBLog;
			std::stringstream ss;
			ss << "SaveModelFile : " << strGBLog;
			_strLog.append(ss.str());
		}

		std::string strPicName = pModel->vecPaperModel[i]->strModelPicName;

		Poco::JSON::Array jsnSNArry;
		Poco::JSON::Array jsnSelHTrackerArry;
		Poco::JSON::Array jsnSelVTrackerArry;
		Poco::JSON::Array jsnSelRoiArry;
		Poco::JSON::Array jsnFixCPArry;
		Poco::JSON::Array jsnHHeadArry;
		Poco::JSON::Array jsnVHeadArry;
		Poco::JSON::Array jsnPaginationArry;
		Poco::JSON::Array jsnABModelArry;
		Poco::JSON::Array jsnCourseArry;
		Poco::JSON::Array jsnQKArry;
		Poco::JSON::Array jsnWJArry;
		Poco::JSON::Array jsnGrayCPArry;
		Poco::JSON::Array jsnWhiteCPArry;
		Poco::JSON::Array jsnOMRArry;
		Poco::JSON::Array jsnElectOmrArry;
		Poco::JSON::Array jsnCharacterAnchorAreaArry;
		Poco::JSON::Array jsnZgt;
		RECTLIST::iterator itFix = pModel->vecPaperModel[i]->lFix.begin();
		for (; itFix != pModel->vecPaperModel[i]->lFix.end(); itFix++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itFix->eCPType);
			jsnObj.set("left", itFix->rt.x);
			jsnObj.set("top", itFix->rt.y);
			jsnObj.set("width", itFix->rt.width);
			jsnObj.set("height", itFix->rt.height);
			jsnObj.set("thresholdValue", itFix->nThresholdValue);
			jsnObj.set("standardValPercent", itFix->fStandardValuePercent);
			jsnObj.set("standardVal", itFix->fStandardValue);
			jsnObj.set("standardArea", itFix->fStandardArea);
			jsnObj.set("standardDensity", itFix->fStandardDensity);
			jsnObj.set("standardMeanGray", itFix->fStandardMeanGray);
			jsnObj.set("standardStddev", itFix->fStandardStddev);

			jsnObj.set("gaussKernel", itFix->nGaussKernel);
			jsnObj.set("sharpKernel", itFix->nSharpKernel);
			jsnObj.set("cannyKernel", itFix->nCannyKernel);
			jsnObj.set("dilateKernel", itFix->nDilateKernel);
			jsnFixCPArry.add(jsnObj);
		}
		RECTLIST::iterator itHHead = pModel->vecPaperModel[i]->lH_Head.begin();
		for (; itHHead != pModel->vecPaperModel[i]->lH_Head.end(); itHHead++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itHHead->eCPType);
			jsnObj.set("left", itHHead->rt.x);
			jsnObj.set("top", itHHead->rt.y);
			jsnObj.set("width", itHHead->rt.width);
			jsnObj.set("height", itHHead->rt.height);
			jsnObj.set("thresholdValue", itHHead->nThresholdValue);
			jsnObj.set("standardValPercent", itHHead->fStandardValuePercent);
			jsnObj.set("standardVal", itHHead->fStandardValue);
			jsnObj.set("standardArea", itHHead->fStandardArea);
			jsnObj.set("standardDensity", itHHead->fStandardDensity);
			jsnObj.set("standardMeanGray", itHHead->fStandardMeanGray);
			jsnObj.set("standardStddev", itHHead->fStandardStddev);

			jsnObj.set("gaussKernel", itHHead->nGaussKernel);
			jsnObj.set("sharpKernel", itHHead->nSharpKernel);
			jsnObj.set("cannyKernel", itHHead->nCannyKernel);
			jsnObj.set("dilateKernel", itHHead->nDilateKernel);
			jsnHHeadArry.add(jsnObj);
		}
		RECTLIST::iterator itVHead = pModel->vecPaperModel[i]->lV_Head.begin();
		for (; itVHead != pModel->vecPaperModel[i]->lV_Head.end(); itVHead++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itVHead->eCPType);
			jsnObj.set("left", itVHead->rt.x);
			jsnObj.set("top", itVHead->rt.y);
			jsnObj.set("width", itVHead->rt.width);
			jsnObj.set("height", itVHead->rt.height);
			jsnObj.set("thresholdValue", itVHead->nThresholdValue);
			jsnObj.set("standardValPercent", itVHead->fStandardValuePercent);
			jsnObj.set("standardVal", itVHead->fStandardValue);
			jsnObj.set("standardArea", itVHead->fStandardArea);
			jsnObj.set("standardDensity", itVHead->fStandardDensity);
			jsnObj.set("standardMeanGray", itVHead->fStandardMeanGray);
			jsnObj.set("standardStddev", itVHead->fStandardStddev);

			jsnObj.set("gaussKernel", itVHead->nGaussKernel);
			jsnObj.set("sharpKernel", itVHead->nSharpKernel);
			jsnObj.set("cannyKernel", itVHead->nCannyKernel);
			jsnObj.set("dilateKernel", itVHead->nDilateKernel);
			jsnVHeadArry.add(jsnObj);
		}
		RECTLIST::iterator itPage = pModel->vecPaperModel[i]->lPagination.begin();
		for (; itPage != pModel->vecPaperModel[i]->lPagination.end(); itPage++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itPage->eCPType);
			jsnObj.set("left", itPage->rt.x);
			jsnObj.set("top", itPage->rt.y);
			jsnObj.set("width", itPage->rt.width);
			jsnObj.set("height", itPage->rt.height);
			jsnObj.set("hHeadItem", itPage->nHItem);
			jsnObj.set("vHeadItem", itPage->nVItem);
			jsnObj.set("thresholdValue", itPage->nThresholdValue);
			jsnObj.set("standardValPercent", itPage->fStandardValuePercent);
			jsnObj.set("standardVal", itPage->fStandardValue);
			jsnObj.set("standardArea", itPage->fStandardArea);
			jsnObj.set("standardDensity", itPage->fStandardDensity);
			jsnObj.set("standardMeanGray", itPage->fStandardMeanGray);
			jsnObj.set("standardStddev", itPage->fStandardStddev);

			jsnObj.set("gaussKernel", itPage->nGaussKernel);
			jsnObj.set("sharpKernel", itPage->nSharpKernel);
			jsnObj.set("cannyKernel", itPage->nCannyKernel);
			jsnObj.set("dilateKernel", itPage->nDilateKernel);
			jsnPaginationArry.add(jsnObj);
		}
		RECTLIST::iterator itABModel = pModel->vecPaperModel[i]->lABModel.begin();
		for (; itABModel != pModel->vecPaperModel[i]->lABModel.end(); itABModel++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itABModel->eCPType);
			jsnObj.set("left", itABModel->rt.x);
			jsnObj.set("top", itABModel->rt.y);
			jsnObj.set("width", itABModel->rt.width);
			jsnObj.set("height", itABModel->rt.height);
			jsnObj.set("hHeadItem", itABModel->nHItem);
			jsnObj.set("vHeadItem", itABModel->nVItem);
			jsnObj.set("thresholdValue", itABModel->nThresholdValue);
			jsnObj.set("standardValPercent", itABModel->fStandardValuePercent);
			jsnObj.set("standardVal", itABModel->fStandardValue);
			jsnObj.set("standardArea", itABModel->fStandardArea);
			jsnObj.set("standardDensity", itABModel->fStandardDensity);
			jsnObj.set("standardMeanGray", itABModel->fStandardMeanGray);
			jsnObj.set("standardStddev", itABModel->fStandardStddev);

			jsnObj.set("gaussKernel", itABModel->nGaussKernel);
			jsnObj.set("sharpKernel", itABModel->nSharpKernel);
			jsnObj.set("cannyKernel", itABModel->nCannyKernel);
			jsnObj.set("dilateKernel", itABModel->nDilateKernel);
			jsnABModelArry.add(jsnObj);
		}
		RECTLIST::iterator itCourse = pModel->vecPaperModel[i]->lCourse.begin();
		for (; itCourse != pModel->vecPaperModel[i]->lCourse.end(); itCourse++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itCourse->eCPType);
			jsnObj.set("left", itCourse->rt.x);
			jsnObj.set("top", itCourse->rt.y);
			jsnObj.set("width", itCourse->rt.width);
			jsnObj.set("height", itCourse->rt.height);
			jsnObj.set("hHeadItem", itCourse->nHItem);
			jsnObj.set("vHeadItem", itCourse->nVItem);
			jsnObj.set("thresholdValue", itCourse->nThresholdValue);
			jsnObj.set("standardValPercent", itCourse->fStandardValuePercent);
			jsnObj.set("standardVal", itCourse->fStandardValue);
			jsnObj.set("standardArea", itCourse->fStandardArea);
			jsnObj.set("standardDensity", itCourse->fStandardDensity);
			jsnObj.set("standardMeanGray", itCourse->fStandardMeanGray);
			jsnObj.set("standardStddev", itCourse->fStandardStddev);

			jsnObj.set("gaussKernel", itCourse->nGaussKernel);
			jsnObj.set("sharpKernel", itCourse->nSharpKernel);
			jsnObj.set("cannyKernel", itCourse->nCannyKernel);
			jsnObj.set("dilateKernel", itCourse->nDilateKernel);
			jsnCourseArry.add(jsnObj);
		}
		RECTLIST::iterator itQKCP = pModel->vecPaperModel[i]->lQK_CP.begin();
		for (; itQKCP != pModel->vecPaperModel[i]->lQK_CP.end(); itQKCP++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itQKCP->eCPType);
			jsnObj.set("left", itQKCP->rt.x);
			jsnObj.set("top", itQKCP->rt.y);
			jsnObj.set("width", itQKCP->rt.width);
			jsnObj.set("height", itQKCP->rt.height);
			jsnObj.set("hHeadItem", itQKCP->nHItem);
			jsnObj.set("vHeadItem", itQKCP->nVItem);
			jsnObj.set("thresholdValue", itQKCP->nThresholdValue);
			jsnObj.set("standardValPercent", itQKCP->fStandardValuePercent);
			jsnObj.set("standardVal", itQKCP->fStandardValue);
			jsnObj.set("standardArea", itQKCP->fStandardArea);
			jsnObj.set("standardDensity", itQKCP->fStandardDensity);
			jsnObj.set("standardMeanGray", itQKCP->fStandardMeanGray);
			jsnObj.set("standardStddev", itQKCP->fStandardStddev);

			jsnObj.set("gaussKernel", itQKCP->nGaussKernel);
			jsnObj.set("sharpKernel", itQKCP->nSharpKernel);
			jsnObj.set("cannyKernel", itQKCP->nCannyKernel);
			jsnObj.set("dilateKernel", itQKCP->nDilateKernel);
			jsnQKArry.add(jsnObj);
		}
		RECTLIST::iterator itWJCP = pModel->vecPaperModel[i]->lWJ_CP.begin();
		for (; itWJCP != pModel->vecPaperModel[i]->lWJ_CP.end(); itWJCP++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itWJCP->eCPType);
			jsnObj.set("left", itWJCP->rt.x);
			jsnObj.set("top", itWJCP->rt.y);
			jsnObj.set("width", itWJCP->rt.width);
			jsnObj.set("height", itWJCP->rt.height);
			jsnObj.set("hHeadItem", itWJCP->nHItem);
			jsnObj.set("vHeadItem", itWJCP->nVItem);
			jsnObj.set("thresholdValue", itWJCP->nThresholdValue);
			jsnObj.set("standardValPercent", itWJCP->fStandardValuePercent);
			jsnObj.set("standardVal", itWJCP->fStandardValue);
			jsnObj.set("standardArea", itWJCP->fStandardArea);
			jsnObj.set("standardDensity", itWJCP->fStandardDensity);
			jsnObj.set("standardMeanGray", itWJCP->fStandardMeanGray);
			jsnObj.set("standardStddev", itWJCP->fStandardStddev);

			jsnObj.set("gaussKernel", itWJCP->nGaussKernel);
			jsnObj.set("sharpKernel", itWJCP->nSharpKernel);
			jsnObj.set("cannyKernel", itWJCP->nCannyKernel);
			jsnObj.set("dilateKernel", itWJCP->nDilateKernel);
			jsnWJArry.add(jsnObj);
		}
		RECTLIST::iterator itGrayCP = pModel->vecPaperModel[i]->lGray.begin();
		for (; itGrayCP != pModel->vecPaperModel[i]->lGray.end(); itGrayCP++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itGrayCP->eCPType);
			jsnObj.set("left", itGrayCP->rt.x);
			jsnObj.set("top", itGrayCP->rt.y);
			jsnObj.set("width", itGrayCP->rt.width);
			jsnObj.set("height", itGrayCP->rt.height);
			jsnObj.set("hHeadItem", itGrayCP->nHItem);
			jsnObj.set("vHeadItem", itGrayCP->nVItem);
			jsnObj.set("thresholdValue", itGrayCP->nThresholdValue);
			jsnObj.set("standardValPercent", itGrayCP->fStandardValuePercent);
			jsnObj.set("standardVal", itGrayCP->fStandardValue);
			jsnObj.set("standardArea", itGrayCP->fStandardArea);
			jsnObj.set("standardDensity", itGrayCP->fStandardDensity);
			jsnObj.set("standardMeanGray", itGrayCP->fStandardMeanGray);
			jsnObj.set("standardStddev", itGrayCP->fStandardStddev);

			jsnObj.set("gaussKernel", itGrayCP->nGaussKernel);
			jsnObj.set("sharpKernel", itGrayCP->nSharpKernel);
			jsnObj.set("cannyKernel", itGrayCP->nCannyKernel);
			jsnObj.set("dilateKernel", itGrayCP->nDilateKernel);
			jsnGrayCPArry.add(jsnObj);
		}
		RECTLIST::iterator itWhiteCP = pModel->vecPaperModel[i]->lWhite.begin();
		for (; itWhiteCP != pModel->vecPaperModel[i]->lWhite.end(); itWhiteCP++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itWhiteCP->eCPType);
			jsnObj.set("left", itWhiteCP->rt.x);
			jsnObj.set("top", itWhiteCP->rt.y);
			jsnObj.set("width", itWhiteCP->rt.width);
			jsnObj.set("height", itWhiteCP->rt.height);
			jsnObj.set("hHeadItem", itWhiteCP->nHItem);
			jsnObj.set("vHeadItem", itWhiteCP->nVItem);
			jsnObj.set("thresholdValue", itWhiteCP->nThresholdValue);
			jsnObj.set("standardValPercent", itWhiteCP->fStandardValuePercent);
			jsnObj.set("standardVal", itWhiteCP->fStandardValue);
			jsnObj.set("standardArea", itWhiteCP->fStandardArea);
			jsnObj.set("standardDensity", itWhiteCP->fStandardDensity);
			jsnObj.set("standardMeanGray", itWhiteCP->fStandardMeanGray);
			jsnObj.set("standardStddev", itWhiteCP->fStandardStddev);

			jsnObj.set("gaussKernel", itWhiteCP->nGaussKernel);
			jsnObj.set("sharpKernel", itWhiteCP->nSharpKernel);
			jsnObj.set("cannyKernel", itWhiteCP->nCannyKernel);
			jsnObj.set("dilateKernel", itWhiteCP->nDilateKernel);
			jsnWhiteCPArry.add(jsnObj);
		}
		RECTLIST::iterator itSelRoi = pModel->vecPaperModel[i]->lSelFixRoi.begin();
		for (; itSelRoi != pModel->vecPaperModel[i]->lSelFixRoi.end(); itSelRoi++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itSelRoi->eCPType);
			jsnObj.set("left", itSelRoi->rt.x);
			jsnObj.set("top", itSelRoi->rt.y);
			jsnObj.set("width", itSelRoi->rt.width);
			jsnObj.set("height", itSelRoi->rt.height);
			jsnObj.set("thresholdValue", itSelRoi->nThresholdValue);
			jsnObj.set("standardValPercent", itSelRoi->fStandardValuePercent);
			//			jsnObj.set("standardVal", itSelRoi->fStandardValue);

			jsnObj.set("gaussKernel", itSelRoi->nGaussKernel);
			jsnObj.set("sharpKernel", itSelRoi->nSharpKernel);
			jsnObj.set("cannyKernel", itSelRoi->nCannyKernel);
			jsnObj.set("dilateKernel", itSelRoi->nDilateKernel);
			jsnSelRoiArry.add(jsnObj);
		}
		RECTLIST::iterator itSelHTracker = pModel->vecPaperModel[i]->lSelHTracker.begin();
		for (; itSelHTracker != pModel->vecPaperModel[i]->lSelHTracker.end(); itSelHTracker++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itSelHTracker->eCPType);
			jsnObj.set("left", itSelHTracker->rt.x);
			jsnObj.set("top", itSelHTracker->rt.y);
			jsnObj.set("width", itSelHTracker->rt.width);
			jsnObj.set("height", itSelHTracker->rt.height);
			jsnObj.set("thresholdValue", itSelHTracker->nThresholdValue);
			jsnObj.set("standardValPercent", itSelHTracker->fStandardValuePercent);
			//			jsnObj.set("standardVal", itSelHTracker->fStandardValue);

			jsnObj.set("gaussKernel", itSelHTracker->nGaussKernel);
			jsnObj.set("sharpKernel", itSelHTracker->nSharpKernel);
			jsnObj.set("cannyKernel", itSelHTracker->nCannyKernel);
			jsnObj.set("dilateKernel", itSelHTracker->nDilateKernel);
			jsnSelHTrackerArry.add(jsnObj);
		}
		RECTLIST::iterator itSelVTracker = pModel->vecPaperModel[i]->lSelVTracker.begin();
		for (; itSelVTracker != pModel->vecPaperModel[i]->lSelVTracker.end(); itSelVTracker++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("eType", (int)itSelVTracker->eCPType);
			jsnObj.set("left", itSelVTracker->rt.x);
			jsnObj.set("top", itSelVTracker->rt.y);
			jsnObj.set("width", itSelVTracker->rt.width);
			jsnObj.set("height", itSelVTracker->rt.height);
			jsnObj.set("thresholdValue", itSelVTracker->nThresholdValue);
			jsnObj.set("standardValPercent", itSelVTracker->fStandardValuePercent);
			//			jsnObj.set("standardVal", itSelVTracker->fStandardValue);

			jsnObj.set("gaussKernel", itSelVTracker->nGaussKernel);
			jsnObj.set("sharpKernel", itSelVTracker->nSharpKernel);
			jsnObj.set("cannyKernel", itSelVTracker->nCannyKernel);
			jsnObj.set("dilateKernel", itSelVTracker->nDilateKernel);
			jsnSelVTrackerArry.add(jsnObj);
		}
		OMRLIST::iterator itOmr = pModel->vecPaperModel[i]->lOMR2.begin();
		for (; itOmr != pModel->vecPaperModel[i]->lOMR2.end(); itOmr++)
		{
			Poco::JSON::Object jsnTHObj;
			Poco::JSON::Array  jsnArry;
			RECTLIST::iterator itOmrSel = itOmr->lSelAnswer.begin();
			for (; itOmrSel != itOmr->lSelAnswer.end(); itOmrSel++)
			{
				Poco::JSON::Object jsnObj;
				jsnObj.set("eType", (int)itOmrSel->eCPType);
				jsnObj.set("nTH", itOmrSel->nTH);
				jsnObj.set("nAnswer", itOmrSel->nAnswer);
				jsnObj.set("nSingle", itOmrSel->nSingle);
				jsnObj.set("nOmrRecogFlag", itOmrSel->nRecogFlag);
				jsnObj.set("left", itOmrSel->rt.x);
				jsnObj.set("top", itOmrSel->rt.y);
				jsnObj.set("width", itOmrSel->rt.width);
				jsnObj.set("height", itOmrSel->rt.height);
				jsnObj.set("hHeadItem", itOmrSel->nHItem);
				jsnObj.set("vHeadItem", itOmrSel->nVItem);
				jsnObj.set("thresholdValue", itOmrSel->nThresholdValue);
				jsnObj.set("standardValPercent", itOmrSel->fStandardValuePercent);
				jsnObj.set("standardVal", itOmrSel->fStandardValue);
				jsnObj.set("standardArea", itOmrSel->fStandardArea);
				jsnObj.set("standardDensity", itOmrSel->fStandardDensity);
				jsnObj.set("standardMeanGray", itOmrSel->fStandardMeanGray);
				jsnObj.set("standardStddev", itOmrSel->fStandardStddev);

				jsnObj.set("gaussKernel", itOmrSel->nGaussKernel);
				jsnObj.set("sharpKernel", itOmrSel->nSharpKernel);
				jsnObj.set("cannyKernel", itOmrSel->nCannyKernel);
				jsnObj.set("dilateKernel", itOmrSel->nDilateKernel);
				jsnArry.add(jsnObj);
			}
			jsnTHObj.set("nTH", itOmr->nTH);
			jsnTHObj.set("nSingle", itOmr->nSingle);
			jsnTHObj.set("omrlist", jsnArry);
			jsnOMRArry.add(jsnTHObj);
		}
		SNLIST::iterator itSn = pModel->vecPaperModel[i]->lSNInfo.begin();
		for (; itSn != pModel->vecPaperModel[i]->lSNInfo.end(); itSn++)
		{
			Poco::JSON::Object jsnSNObj;
			Poco::JSON::Array  jsnArry;
			RECTLIST::iterator itSnDetail = (*itSn)->lSN.begin();
			for (; itSnDetail != (*itSn)->lSN.end(); itSnDetail++)
			{
				Poco::JSON::Object jsnObj;
				jsnObj.set("eType", (int)itSnDetail->eCPType);
				jsnObj.set("nTH", itSnDetail->nTH);
				jsnObj.set("nSnVal", itSnDetail->nSnVal);
				jsnObj.set("nAnswer", itSnDetail->nAnswer);
				jsnObj.set("nSingle", itSnDetail->nSingle);
				jsnObj.set("nSnRecogFlag", itSnDetail->nRecogFlag);
				jsnObj.set("left", itSnDetail->rt.x);
				jsnObj.set("top", itSnDetail->rt.y);
				jsnObj.set("width", itSnDetail->rt.width);
				jsnObj.set("height", itSnDetail->rt.height);
				jsnObj.set("hHeadItem", itSnDetail->nHItem);
				jsnObj.set("vHeadItem", itSnDetail->nVItem);
				jsnObj.set("thresholdValue", itSnDetail->nThresholdValue);
				jsnObj.set("standardValPercent", itSnDetail->fStandardValuePercent);
				jsnObj.set("standardVal", itSnDetail->fStandardValue);
				jsnObj.set("standardArea", itSnDetail->fStandardArea);
				jsnObj.set("standardDensity", itSnDetail->fStandardDensity);
				jsnObj.set("standardMeanGray", itSnDetail->fStandardMeanGray);
				jsnObj.set("standardStddev", itSnDetail->fStandardStddev);

				jsnObj.set("gaussKernel", itSnDetail->nGaussKernel);
				jsnObj.set("sharpKernel", itSnDetail->nSharpKernel);
				jsnObj.set("cannyKernel", itSnDetail->nCannyKernel);
				jsnObj.set("dilateKernel", itSnDetail->nDilateKernel);
				jsnArry.add(jsnObj);
			}
			jsnSNObj.set("nItem", (*itSn)->nItem);
			jsnSNObj.set("nRecogVal", (*itSn)->nRecogVal);
			jsnSNObj.set("snList", jsnArry);
			jsnSNArry.add(jsnSNObj);
		}
		ELECTOMR_LIST::iterator itElectOmr = pModel->vecPaperModel[i]->lElectOmr.begin();
		for (; itElectOmr != pModel->vecPaperModel[i]->lElectOmr.end(); itElectOmr++)
		{
			pModel->nHasElectOmr = 1;		//设置标识

			Poco::JSON::Object jsnTHObj;
			Poco::JSON::Array  jsnArry;
			RECTLIST::iterator itOmrSel = itElectOmr->lItemInfo.begin();
			for (; itOmrSel != itElectOmr->lItemInfo.end(); itOmrSel++)
			{
				Poco::JSON::Object jsnObj;
				jsnObj.set("eType", (int)itOmrSel->eCPType);
				jsnObj.set("nTH", itOmrSel->nTH);
				jsnObj.set("nAnswer", itOmrSel->nAnswer);
				jsnObj.set("left", itOmrSel->rt.x);
				jsnObj.set("top", itOmrSel->rt.y);
				jsnObj.set("width", itOmrSel->rt.width);
				jsnObj.set("height", itOmrSel->rt.height);
				jsnObj.set("hHeadItem", itOmrSel->nHItem);
				jsnObj.set("vHeadItem", itOmrSel->nVItem);
				jsnObj.set("thresholdValue", itOmrSel->nThresholdValue);
				jsnObj.set("standardValPercent", itOmrSel->fStandardValuePercent);
				jsnObj.set("standardVal", itOmrSel->fStandardValue);
				jsnObj.set("standardArea", itOmrSel->fStandardArea);
				jsnObj.set("standardDensity", itOmrSel->fStandardDensity);
				jsnObj.set("standardMeanGray", itOmrSel->fStandardMeanGray);
				jsnObj.set("standardStddev", itOmrSel->fStandardStddev);

				jsnObj.set("gaussKernel", itOmrSel->nGaussKernel);
				jsnObj.set("sharpKernel", itOmrSel->nSharpKernel);
				jsnObj.set("cannyKernel", itOmrSel->nCannyKernel);
				jsnObj.set("dilateKernel", itOmrSel->nDilateKernel);
				jsnArry.add(jsnObj);
			}
			jsnTHObj.set("nGroupID", itElectOmr->sElectOmrGroupInfo.nGroupID);
			jsnTHObj.set("nAllCount", itElectOmr->sElectOmrGroupInfo.nAllCount);
			jsnTHObj.set("nRealCount", itElectOmr->sElectOmrGroupInfo.nRealCount);
			jsnTHObj.set("omrlist", jsnArry);
			jsnElectOmrArry.add(jsnTHObj);
		}
		CHARACTER_ANCHOR_AREA_LIST::iterator itRecogCharInfo = pModel->vecPaperModel[i]->lCharacterAnchorArea.begin();
		for (; itRecogCharInfo != pModel->vecPaperModel[i]->lCharacterAnchorArea.end(); itRecogCharInfo++)
		{
			Poco::JSON::Object jsnCharacterAnchorAreaObj;
			Poco::JSON::Array  jsnArry;
			std::vector<pST_CHARACTER_ANCHOR_POINT>::iterator itCharRt = (*itRecogCharInfo)->vecCharacterRt.begin();
			for (; itCharRt != (*itRecogCharInfo)->vecCharacterRt.end(); itCharRt++)
			{
				RECTINFO rcTmp = (*itCharRt)->rc;
				Poco::JSON::Object jsnObj;
				jsnObj.set("eType", (int)rcTmp.eCPType);
				jsnObj.set("nTH", rcTmp.nTH);
				jsnObj.set("nAnswer", rcTmp.nAnswer);
				jsnObj.set("left", rcTmp.rt.x);
				jsnObj.set("top", rcTmp.rt.y);
				jsnObj.set("width", rcTmp.rt.width);
				jsnObj.set("height", rcTmp.rt.height);
				jsnObj.set("hHeadItem", rcTmp.nHItem);
				jsnObj.set("vHeadItem", rcTmp.nVItem);
				jsnObj.set("thresholdValue", rcTmp.nThresholdValue);
				jsnObj.set("standardValPercent", rcTmp.fStandardValuePercent);
				jsnObj.set("standardVal", rcTmp.fStandardValue);
				jsnObj.set("standardArea", rcTmp.fStandardArea);
				jsnObj.set("standardDensity", rcTmp.fStandardDensity);
				jsnObj.set("standardMeanGray", rcTmp.fStandardMeanGray);
				jsnObj.set("standardStddev", rcTmp.fStandardStddev);

				jsnObj.set("gaussKernel", rcTmp.nGaussKernel);
				jsnObj.set("sharpKernel", rcTmp.nSharpKernel);
				jsnObj.set("cannyKernel", rcTmp.nCannyKernel);
				jsnObj.set("dilateKernel", rcTmp.nDilateKernel);

				//------------------
				jsnObj.set("nIndex", (*itCharRt)->nIndex);
				jsnObj.set("fConfidence", (*itCharRt)->fConfidence);
				jsnObj.set("strRecogChar", CMyCodeConvert::Gb2312ToUtf8((*itCharRt)->strVal));
				jsnArry.add(jsnObj);
			}
			jsnCharacterAnchorAreaObj.set("nIndex", (*itRecogCharInfo)->nIndex);
			jsnCharacterAnchorAreaObj.set("nThreshold", (*itRecogCharInfo)->nThresholdValue);
			jsnCharacterAnchorAreaObj.set("nConfidence", (*itRecogCharInfo)->nCharacterConfidence);
			jsnCharacterAnchorAreaObj.set("nRectsInArea", (*itRecogCharInfo)->nRects);

			jsnCharacterAnchorAreaObj.set("gaussKernel", (*itRecogCharInfo)->nGaussKernel);
			jsnCharacterAnchorAreaObj.set("sharpKernel", (*itRecogCharInfo)->nSharpKernel);
			jsnCharacterAnchorAreaObj.set("cannyKernel", (*itRecogCharInfo)->nCannyKernel);
			jsnCharacterAnchorAreaObj.set("dilateKernel", (*itRecogCharInfo)->nDilateKernel);

			jsnCharacterAnchorAreaObj.set("left", (*itRecogCharInfo)->rt.x);
			jsnCharacterAnchorAreaObj.set("top", (*itRecogCharInfo)->rt.y);
			jsnCharacterAnchorAreaObj.set("width", (*itRecogCharInfo)->rt.width);
			jsnCharacterAnchorAreaObj.set("height", (*itRecogCharInfo)->rt.height);

			jsnCharacterAnchorAreaObj.set("characterAnchorPointList", jsnArry);
			jsnCharacterAnchorAreaArry.add(jsnCharacterAnchorAreaObj);
		}
		ZGT_LIST::iterator itZgt = pModel->vecPaperModel[i]->lZgt.begin();
		for (; itZgt != pModel->vecPaperModel[i]->lZgt.end(); itZgt++)
		{
			Poco::JSON::Object jsnObj;
			jsnObj.set("type", itZgt->nType);
			jsnObj.set("counts", itZgt->nCounts);
			jsnObj.set("th", itZgt->strTh);
// 			jsnObj.set("s_th", itZgt->nS_Th);
// 			jsnObj.set("e_th", itZgt->nE_Th);
			Poco::JSON::Array arryRegion;
			for (int k = 0; k < itZgt->vecRegion.size(); k++)
			{
				Poco::JSON::Object jsnRegion;
				jsnRegion.set("id", itZgt->vecRegion[k].nId);
				jsnRegion.set("pageId", itZgt->vecRegion[k].nPageId);
				Poco::JSON::Object jsnPos;
				jsnPos.set("x", itZgt->vecRegion[k].rt.x);
				jsnPos.set("y", itZgt->vecRegion[k].rt.y);
				jsnPos.set("w", itZgt->vecRegion[k].rt.width);
				jsnPos.set("h", itZgt->vecRegion[k].rt.height);
				jsnRegion.set("pos", jsnPos);
				arryRegion.add(jsnRegion);
			}
			jsnObj.set("region", arryRegion);
			jsnZgt.add(jsnObj);
		}
		jsnPaperObj.set("paperNum", i);
		jsnPaperObj.set("modelPicName", CMyCodeConvert::Gb2312ToUtf8(strPicName));		//CMyCodeConvert::Gb2312ToUtf8(T2A(strPicName))
		jsnPaperObj.set("FixCP", jsnFixCPArry);
		jsnPaperObj.set("H_Head", jsnHHeadArry);
		jsnPaperObj.set("V_Head", jsnVHeadArry);
		jsnPaperObj.set("Pagination", jsnPaginationArry);
		jsnPaperObj.set("ABModel", jsnABModelArry);
		jsnPaperObj.set("Course", jsnCourseArry);
		jsnPaperObj.set("QKCP", jsnQKArry);
		jsnPaperObj.set("WJCP", jsnWJArry);
		jsnPaperObj.set("GrayCP", jsnGrayCPArry);
		jsnPaperObj.set("WhiteCP", jsnWhiteCPArry);
		jsnPaperObj.set("selRoiRect", jsnSelRoiArry);
		jsnPaperObj.set("hTrackerRect", jsnSelHTrackerArry);
		jsnPaperObj.set("vTrackerRect", jsnSelVTrackerArry);
		jsnPaperObj.set("selOmrRect", jsnOMRArry);
		jsnPaperObj.set("snList", jsnSNArry);
		jsnPaperObj.set("electOmrList", jsnElectOmrArry);
		jsnPaperObj.set("characterAnchorArea", jsnCharacterAnchorAreaArry);
		jsnPaperObj.set("zgt", jsnZgt);

		jsnPaperObj.set("picSaveRotion", pModel->vecPaperModel[i]->nPicSaveRotation);
		jsnPaperObj.set("picW", pModel->vecPaperModel[i]->nPicW);		//add on 16.8.29
		jsnPaperObj.set("picH", pModel->vecPaperModel[i]->nPicH);		//add on 16.8.29
		jsnPaperObj.set("rtHTracker.x", pModel->vecPaperModel[i]->rtHTracker.x);
		jsnPaperObj.set("rtHTracker.y", pModel->vecPaperModel[i]->rtHTracker.y);
		jsnPaperObj.set("rtHTracker.width", pModel->vecPaperModel[i]->rtHTracker.width);
		jsnPaperObj.set("rtHTracker.height", pModel->vecPaperModel[i]->rtHTracker.height);
		jsnPaperObj.set("rtVTracker.x", pModel->vecPaperModel[i]->rtVTracker.x);
		jsnPaperObj.set("rtVTracker.y", pModel->vecPaperModel[i]->rtVTracker.y);
		jsnPaperObj.set("rtVTracker.width", pModel->vecPaperModel[i]->rtVTracker.width);
		jsnPaperObj.set("rtVTracker.height", pModel->vecPaperModel[i]->rtVTracker.height);
		jsnPaperObj.set("rtSNTracker.x", pModel->vecPaperModel[i]->rcSNTracker.rt.x);
		jsnPaperObj.set("rtSNTracker.y", pModel->vecPaperModel[i]->rcSNTracker.rt.y);
		jsnPaperObj.set("rtSNTracker.width", pModel->vecPaperModel[i]->rcSNTracker.rt.width);
		jsnPaperObj.set("rtSNTracker.height", pModel->vecPaperModel[i]->rcSNTracker.rt.height);
		jsnPaperObj.set("rtSNTracker.nRecogFlag", pModel->vecPaperModel[i]->rcSNTracker.nRecogFlag);

		jsnPicModel.add(jsnPaperObj);
	}

	jsnModel.set("modelName", CMyCodeConvert::Gb2312ToUtf8(pModel->strModelName));		//CMyCodeConvert::Gb2312ToUtf8(T2A(pModel->strModelName))
	jsnModel.set("modelDesc", CMyCodeConvert::Gb2312ToUtf8(pModel->strModelDesc));
	jsnModel.set("modelType", pModel->nType);
	jsnModel.set("modeSaveMode", pModel->nSaveMode);
	jsnModel.set("paperModelCount", pModel->nPicNum);			//此模板有几页试卷(图片)
	jsnModel.set("enableModify", pModel->nEnableModify);		//是否可以修改标识
	jsnModel.set("abPaper", pModel->nABModel);					//是否是AB卷					*************	暂时没加入AB卷的模板	**************
	jsnModel.set("hasHead", pModel->nHasHead);					//是否有同步头
	jsnModel.set("hasElectOmr", pModel->nHasElectOmr);			//是否有选做题
	jsnModel.set("nZkzhType", pModel->nZkzhType);				//准考证号识别类型
	jsnModel.set("nScanDpi", pModel->nScanDpi);					//扫描的dpi设置
	jsnModel.set("nScanSize", pModel->nScanSize);				//扫描用的纸张类型，1-a4, 2-a3, 3-定制
	jsnModel.set("nScanType", pModel->nScanType);				//扫描模式：1-灰度扫描，2-彩色扫描
	jsnModel.set("nScanAutoCut", pModel->nAutoCut);				//扫描仪是否自动裁剪，超长卡不能裁剪
	jsnModel.set("nUseWordAnchorPoint", pModel->nUseWordAnchorPoint);		//是否使用文字定点来定位识别
	jsnModel.set("nCharacterAnchorPoint", pModel->nCharacterAnchorPoint);	//用来计算矩形位置的文字定点个数
	jsnModel.set("nUsePagination", pModel->nUsePagination);					//是否使用页码标识
	jsnModel.set("nChkLostCorner", pModel->nChkLostCorner);					//是否需要进行缺角检测
	jsnModel.set("nCardType", pModel->nCardType);							//卡类型：0-网阅卡，1-手阅卡

	jsnModel.set("nExamId", pModel->nExamID);
	jsnModel.set("nSubjectId", pModel->nSubjectID);
	jsnModel.set("examUUID", pModel->strExamUUID);
	jsnModel.set("subjectUUID", pModel->strSubjectUUID);
	jsnModel.set("paperInfo", jsnPicModel);

	std::stringstream jsnString;
	jsnModel.stringify(jsnString, 0);

	std::string strFileData;
#ifdef USES_FILE_ENC
	if (!encString(jsnString.str(), strFileData))
		strFileData = jsnString.str();
#else
	strFileData = jsnString.str();
#endif

	std::string strJsnFile = modelPath;
	strJsnFile += "\\model.dat";
	ofstream out(strJsnFile);
	if (!out)
	{
		std::string strLog = "创建模板信息文件失败: " + strJsnFile + "\n";
		_strLog.append(strLog);
		//LOG(ERROR) << "SaveModelFile : " << strLog;
		std::stringstream ss;
		ss << "SaveModelFile : " << strLog;
		_strLog.append(ss.str());
		return false;
	}
	out << strFileData.c_str();
	out.close();
	return true;
}

void CModelMgr::SetBaseInfo(std::string strModelDirPath, std::string EncPwd)
{
	_strModelDirPath = strModelDirPath;
	_strEncPwd = EncPwd;
}

bool CModelMgr::encString(std::string& strSrc, std::string& strDst)
{
	bool bResult = true;
	if (_strEncPwd.empty())
	{
		strDst = strSrc;
		return bResult;
	}
	try
	{
		Poco::Crypto::Cipher::Ptr pCipher = Poco::Crypto::CipherFactory::defaultFactory().createCipher(Poco::Crypto::CipherKey("aes256", _strEncPwd));

		strDst = pCipher->encryptString(strSrc, Poco::Crypto::Cipher::ENC_BINHEX);
	}
	catch (...)
	{
		bResult = false;
		std::string strLog = "数据加密失败，按原数据操作\n";
		//LOG(WARNING) << strLog;
		_strLog.append(strLog);
	}
	return bResult;
}

bool CModelMgr::decString(std::string& strSrc, std::string& strDst)
{
	bool bResult = true;
	if (_strEncPwd.empty())
	{
		strDst = strSrc;
		return bResult;
	}
	try
	{
		Poco::Crypto::Cipher::Ptr pCipher = Poco::Crypto::CipherFactory::defaultFactory().createCipher(Poco::Crypto::CipherKey("aes256", _strEncPwd));

		strDst = pCipher->decryptString(strSrc, Poco::Crypto::Cipher::ENC_BINHEX);
	}
	catch (...)
	{
		bResult = false;
		std::string strLog = "数据解密失败，按原数据操作\n";
		//LOG(WARNING) << strLog;
		_strLog.append(strLog);
	}
	return bResult;
}

std::string CModelMgr::GetLog()
{
	return _strLog;
}
