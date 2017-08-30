#pragma once
#include <list>
#include <vector>
#include <opencv2\opencv.hpp>

#define SAFE_RELEASE(pObj)	if(pObj){delete pObj; pObj = NULL;}
#define SAFE_RELEASE_ARRY(pObj) if(pObj) {delete[] pObj; pObj = NULL;}

typedef enum CPType
{
	UNKNOWN = 0,
	Fix_CP,			//定点，坐标计算用
	H_HEAD,			//水平同步头
	V_HEAD,			//垂直同步头
	ABMODEL,		//AB卷型
	COURSE,			//科目
	QK_CP,			//缺考
	WJ_CP,			//违纪
	GRAY_CP,		//灰度校验
	WHITE_CP,		//白校验
	SN,				//考号区
	OMR,			//选择题设置
	ELECT_OMR,		//选做题
	CHARACTER_AREA		//文字定位区
};

typedef struct _RectInfo_
{
	CPType		eCPType;						//校验点类型
	int			nThresholdValue;				//此矩形识别时要求的标准值，即达到的灰度值的阀值
	float		fStandardValue;					//此矩形识别时标准测量值，即按照灰度阀值计算的灰度值
	float		fStandardArea;					//模板矩形块面积，计算密度用
	float		fStandardDensity;				//模板矩形块的密度，计算方式 = fStandardValue/fStandardArea
	float		fStandardMeanGray;				//模板平均灰度
	float		fStandardStddev;				//模板的标准差
	float		fRealValue;						//
	float		fRealArea;						//实际矩形块面积
	float		fRealDensity;					//实际矩形块密度
	float		fRealMeanGray;					//实际矩形块的平均灰度
	float		fStandardValuePercent;			//此矩形要求的标准值比例，即达到给定的灰度值的比例
	float		fRealValuePercent;				//此矩形实际的比例(灰度值)
	float		fRealStddev;					//模板的标准差
	int			nHItem;							//第几个水平同步头
	int			nVItem;							//第几个垂直同步头
	int			nSnVal;							//标识准考证的数字 0-9
	int			nTH;							//题号
	int			nAnswer;						//答案循序，属于第几个答案，如1-A,2-B,3-C,4-D,5-E,6-F...
	int			nSingle;						//0-单选，1-多选, 2-判断题
	int			nRecogFlag;						//识别标识：识别SN时--识别考号顺序与选项方向的考号窗口标识值；识别OMR时--识别题号顺序与选项方向的OMR设置窗口的标识值
	int			nZkzhType;						//准考证号的类型，1-OMR，2-条码or二维码
	
	int		nGaussKernel;		//高斯核
	int		nSharpKernel;		//锐化
	int		nCannyKernel;		//边缘
	int		nDilateKernel;		//膨胀

	//	cv::Point	ptFix;
	cv::Rect	rt;				//cv::Rect
	//	cv::Rect	rtFix;
	_RectInfo_()
	{
		eCPType = UNKNOWN;
		nSnVal = -1;
		nHItem = -1;
		nVItem = -1;
		nTH = -1;
		nAnswer = -1;
		nRecogFlag = 0;
		nZkzhType = 1;
		nSingle = 0;
		nThresholdValue = 0;
		fRealValuePercent = 0.0;
		fStandardValuePercent = 0.0;
		fStandardValue = 0.0;
		fStandardMeanGray = 0.0;
		fRealValue = 0.0;
		fStandardArea = 0.0;
		fStandardDensity = 0.0;
		fRealArea = 0.0;
		fRealDensity = 0.0;
		fRealMeanGray = 0.0;
		fRealStddev = 0.0;
		
		nGaussKernel = 5;
		nSharpKernel = 5;
		nCannyKernel = 90;
		nDilateKernel = 6;
		//		ptFix = cv::Point(0, 0);
	}
}RECTINFO, *pRECTINFO;

typedef std::list<RECTINFO> RECTLIST;			//矩形位置列表

typedef struct _OmrQuestion_			//题目
{
	int nTH;
	int nSingle;						//0-单选，1-多选, 2-判断题
	std::string strRecogVal;			//识别结果：A、B、C...
	RECTLIST	lSelAnswer;				//选项列表
	_OmrQuestion_()
	{
		nTH = -1;
		nSingle = 0;
	}
}OMR_QUESTION, *pOMR_QUESTION;
typedef std::list<OMR_QUESTION> OMRLIST;

typedef struct _ElectOmrGroupInfo_	//选做题组信息
{
	int nGroupID;		//第几组选做题
	int nAllCount;		//总选项
	int nRealCount;		//有效选项			3选2，则此为2
	_ElectOmrGroupInfo_()
	{
		nGroupID = 0;
		nAllCount = 0;
		nRealCount = 0;
	}
}ELECTOMRGROUPINFO, *pELECTOMRGROUPINFO;

typedef struct _ElectOmrQuestion_	//选做题
{
	int		nDoubt;				//0-无怀疑, 1-有怀疑, 2-空值
	std::string strRecogResult;	//识别结果	1\2\3...
	std::string strRecogResult2;	//识别结果	1\2\3...
	ELECTOMRGROUPINFO sElectOmrGroupInfo;
	RECTLIST lItemInfo;	//选项信息
	_ElectOmrQuestion_()
	{
		nDoubt = 0;
	}
}ELECTOMR_QUESTION, *pELECTOMR_QUESTION;
typedef std::list<ELECTOMR_QUESTION> ELECTOMR_LIST;

typedef struct _OmrResult_
{
	int		nTH;				//题号
	int		nSingle;			//0-单选，1-多选, 2-判断题
	int		nDoubt;				//0-无怀疑, 1-有怀疑, 2-空值
	std::string strRecogVal;	//最终识别结果：A、B、C...
	std::string strRecogVal1;
	std::string strRecogVal2;
	std::string strRecogVal3;
	RECTLIST	lSelAnswer;				//选项列表
	_OmrResult_()
	{
		nDoubt = 0;
		nTH = -1;
		nSingle = 0;
	}
}OMR_RESULT, *pOMR_RESULT;
typedef std::list<OMR_RESULT> OMRRESULTLIST;

typedef struct _SN_
{
	int nItem;			//第几位数
	int nRecogVal;		//识别的结果
	RECTLIST	lSN;
	_SN_()
	{
		nItem = -1;
	}
}SN_ITEM, *pSN_ITEM;
typedef std::list<pSN_ITEM> SNLIST;

typedef struct _PaperModel_
{
	int			nPaper;					//标识此模板属于第几张试卷
	int			nPicW;					//图片宽
	int			nPicH;					//图片高
	int			nPaperType;				//试卷类型，A3-1，A4-2
	std::string	strModelPicName;		//模板图片名称
	cv::Rect	rtHTracker;
	cv::Rect	rtVTracker;
//	cv::Rect	rtSNTracker;
	RECTINFO	rcSNTracker;
	SNLIST		lSNInfo;				//SN信息
	RECTLIST	lSelHTracker;			//选择的水平同步头区域
	RECTLIST	lSelVTracker;			//选择的垂直同步头区域
	RECTLIST	lSelFixRoi;				//选择定点的ROI的矩形列表，框选定点的大矩形框
	RECTLIST	lFix;					//定点列表
	RECTLIST	lH_Head;				//水平校验点列表
	RECTLIST	lV_Head;				//垂直同步头列表
	RECTLIST	lABModel;				//卷型校验点
	RECTLIST	lCourse;				//科目校验点
	RECTLIST	lQK_CP;					//缺考校验点
	RECTLIST	lWJ_CP;					//违纪校验点
	RECTLIST	lGray;					//灰度校验点
	RECTLIST	lWhite;					//空白校验点
	OMRLIST		lOMR2;
	ELECTOMR_LIST	lElectOmr;			//选做题列表
	_PaperModel_()
	{
		nPaper = -1;
		nPicW = -1;
		nPicH = -1;
		nPaperType = -1;
	}
	~_PaperModel_()
	{
		SNLIST::iterator itSn = lSNInfo.begin();
		for (; itSn != lSNInfo.end();)
		{
			pSN_ITEM pSNItem = *itSn;
			itSn = lSNInfo.erase(itSn);
			SAFE_RELEASE(pSNItem);
		}
	}
}PAPERMODEL, *pPAPERMODEL;

typedef struct _Model_
{
	int			nType;					//类型：0-通过扫描的图片手动制作的，1-通过制卷工具自动生成的
	int			nEnableModify;			//模板是否可以修改
	int			nPicNum;				//图片数量
	int			nABModel;				//是否是AB卷模式
	int			nHasHead;				//是否有水平和垂直同步头
	int			nHasElectOmr;			//是否有选做题
	int			nZkzhType;				//准考证号识别类型: 1 - OMR，2 - 条码or二维码
	int			nExamID;
	int			nSubjectID;
	int			nSaveMode;				//保存模式: 1-本地模式，2-远程联网模式
	int			nScanDpi;				//扫描图片dpi
	int			nScanSize;				//扫描图片大小，1-A4，2-A3，3-定制
	int			nScanType;				//扫描模式：1-灰度扫描，2-彩色扫描
	int			nAutoCut;				//扫描仪的自动裁剪功能(针对超长纸不能打开此开关)
	
	std::string	strModelName;			//模板名称
	std::string	strModelDesc;			//模板描述

	std::vector<pPAPERMODEL> vecPaperModel;	//存储每一页试卷的模板信息
	_Model_()
	{
		nType = 0;
		nEnableModify = 1;
		nPicNum = 0;
		nABModel = 0;
		nHasHead = 0;
		nHasElectOmr = 0;
		nExamID = 0;
		nSubjectID = 0;
		nSaveMode = 2;
		nZkzhType = 1;
		nScanDpi = 200;
		nScanSize = 1;
		nScanType = 2;
		nAutoCut = 1;
	}
	~_Model_()
	{
		std::vector<pPAPERMODEL>::iterator itModel = vecPaperModel.begin();
		for (; itModel != vecPaperModel.end();)
		{
			pPAPERMODEL pModel = *itModel;
			itModel = vecPaperModel.erase(itModel);
			SAFE_RELEASE(pModel);
		}
	}
}MODEL, *pMODEL;
typedef std::list<pMODEL> MODELLIST;	//模板列表

//文字定位信息
typedef struct _CharacterRectInfo_
{
	int			nIndex;							//识别次序索引
	float		fConfidence;					//识别信心值
	std::string strVal;
	RECTINFO	rc;
	_CharacterRectInfo_()
	{
		nIndex = -1;
		fConfidence = 0.0;
	}
}ST_CHARACTER_RECTINFO, *pST_CHARACTER_RECTINFO;

typedef struct _RecogCharacterInfo_
{
	int		nIndex;							//识别次序索引

	int		nThresholdValue;				//此矩形识别时要求的标准值，即达到的灰度值的阀值
	int		nGaussKernel;		//高斯核
	int		nSharpKernel;		//锐化
	int		nCannyKernel;		//边缘
	int		nDilateKernel;		//膨胀

	cv::Rect	rt;				//识别大区域
	std::vector<ST_CHARACTER_RECTINFO> vecCharacterRt;	//每个文字的区域
	_RecogCharacterInfo_()
	{
		nIndex = -1;
		nThresholdValue = 0;
		nGaussKernel = 5;
		nSharpKernel = 5;
		nCannyKernel = 90;
		nDilateKernel = 6;
	}
}ST_RECOG_CHARACTER_INFO, *pST_RECOG_CHARACTER_INFO;

#if 0
typedef struct _PicInfo_				//图片信息
{
	bool			bRecoged;		//是否已经识别过
	bool			bFindIssue;		//是否找到问题点
	void*			pPaper;			//所属试卷的信息
	cv::Rect		rtFix;			//定点矩形
	std::string		strPicName;		//图片名称
	std::string		strPicPath;		//图片路径
	RECTLIST		lFix;			//定点列表
	RECTLIST		lNormalRect;	//识别出来的正常点位置
	RECTLIST		lIssueRect;		//识别出来的问题试卷的问题点位置，只要出现问题点就不进行下一页的识别
	// 	cv::Mat			matSrc;
	// 	cv::Mat			matDest;
	_PicInfo_()
	{
		bRecoged = false;
		bFindIssue = false;
		pPaper = NULL;
		//		ptFix = cv::Point(0, 0);
		//		ptModelFix = cv::Point(0, 0);
		//		bImgOpen = false;
	}
}ST_PicInfo, *pST_PicInfo;
typedef std::list<pST_PicInfo> PIC_LIST;	//图片列表定义

typedef struct _PaperInfo_
{
	bool		bIssuePaper;		//是否是问题试卷
	int			nQKFlag;			//缺考标识
	pMODEL		pModel;				//识别此学生试卷所用的模板
	void*		pPapers;			//所属的试卷袋信息
	void*		pSrcDlg;			//来源，来自哪个窗口，扫描or导入试卷窗口
	std::string strStudentInfo;		//学生信息	
	std::string strSN;

	SNLIST				lSnResult;
	OMRRESULTLIST		lOmrResult;			//OMRRESULTLIST
	ELECTOMR_LIST		lElectOmrResult;	//识别的选做题OMR结果
	PIC_LIST	lPic;
	_PaperInfo_()
	{
		bIssuePaper = false;
		nQKFlag = 0;
		pModel = NULL;
		pPapers = NULL;
		pSrcDlg = NULL;
	}
	~_PaperInfo_()
	{
		SNLIST::iterator itSn = lSnResult.begin();
		for (; itSn != lSnResult.end();)
		{
			pSN_ITEM pSNItem = *itSn;
			itSn = lSnResult.erase(itSn);
			SAFE_RELEASE(pSNItem);
		}

		PIC_LIST::iterator itPic = lPic.begin();
		for (; itPic != lPic.end();)
		{
			pST_PicInfo pPic = *itPic;
			SAFE_RELEASE(pPic);
			itPic = lPic.erase(itPic);
		}
	}
}ST_PaperInfo, *pST_PaperInfo;		//试卷信息，一个学生对应一份试卷，一份试卷可以有多份图片
typedef std::list<pST_PaperInfo> PAPER_LIST;	//试卷列表

typedef struct _PapersInfo_				//试卷袋信息结构体
{
	int		nPaperCount;				//试卷袋中试卷总数量(学生数)
	int		nRecogErrCount;				//识别错误试卷数量

	//++统计信息
	int		nOmrDoubt;				//OMR怀疑的数量
	int		nOmrNull;				//OMR识别为空的数量
	int		nSnNull;				//准考证号识别为空的数量

	Poco::FastMutex	fmOmrStatistics;//omr统计锁
	Poco::FastMutex fmSnStatistics; //zkzh统计锁
	//--

	Poco::FastMutex fmlPaper;			//对试卷列表读写锁
	Poco::FastMutex fmlIssue;			//对问题试卷列表读写锁
	std::string  strPapersName;			//试卷袋名称
	std::string	 strPapersDesc;			//试卷袋详细描述

	PAPER_LIST	lPaper;					//此试卷袋中试卷列表
	PAPER_LIST	lIssue;					//此试卷袋中识别有问题的试卷列表
	_PapersInfo_()
	{
		nPaperCount = 0;
		nRecogErrCount = 0;
		nOmrDoubt = 0;
		nOmrNull = 0;
		nSnNull = 0;
	}
	~_PapersInfo_()
	{
		fmlPaper.lock();
		PAPER_LIST::iterator itPaper = lPaper.begin();
		for (; itPaper != lPaper.end();)
		{
			pST_PaperInfo pPaper = *itPaper;
			SAFE_RELEASE(pPaper);
			itPaper = lPaper.erase(itPaper);
		}
		fmlPaper.unlock();
		fmlIssue.lock();
		PAPER_LIST::iterator itIssuePaper = lIssue.begin();
		for (; itIssuePaper != lIssue.end();)
		{
			pST_PaperInfo pPaper = *itIssuePaper;
			SAFE_RELEASE(pPaper);
			itIssuePaper = lIssue.erase(itIssuePaper);
		}
		fmlIssue.unlock();
	}
}PAPERSINFO, *pPAPERSINFO;
typedef std::list<pPAPERSINFO> PAPERS_LIST;		//试卷袋列表

typedef struct _RecogTask_
{
	int		nPic;						//此试卷属于模板的第几张
	pMODEL pModel;						//识别用的模板
	std::string strPath;
	pST_PaperInfo	pPaper;				//需要识别的试卷
}RECOGTASK, *pRECOGTASK;
typedef std::list<pRECOGTASK> RECOGTASKLIST;	//识别任务列表
#endif