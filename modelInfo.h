#pragma once
#include <list>
#include <vector>
#include <opencv2\opencv.hpp>

#define SAFE_RELEASE(pObj)	if(pObj){delete pObj; pObj = NULL;}
#define SAFE_RELEASE_ARRY(pObj) if(pObj) {delete[] pObj; pObj = NULL;}

typedef enum CPType
{
	UNKNOWN = 0,
	Fix_CP,			//���㣬���������
	H_HEAD,			//ˮƽͬ��ͷ
	V_HEAD,			//��ֱͬ��ͷ
	ABMODEL,		//AB����
	COURSE,			//��Ŀ
	QK_CP,			//ȱ��
	WJ_CP,			//Υ��
	GRAY_CP,		//�Ҷ�У��
	WHITE_CP,		//��У��
	SN,				//������
	OMR,			//ѡ��������
	ELECT_OMR,		//ѡ����
	CHARACTER_AREA		//���ֶ�λ��
};

typedef struct _RectInfo_
{
	CPType		eCPType;						//У�������
	int			nThresholdValue;				//�˾���ʶ��ʱҪ��ı�׼ֵ�����ﵽ�ĻҶ�ֵ�ķ�ֵ
	float		fStandardValue;					//�˾���ʶ��ʱ��׼����ֵ�������ջҶȷ�ֵ����ĻҶ�ֵ
	float		fStandardArea;					//ģ����ο�����������ܶ���
	float		fStandardDensity;				//ģ����ο���ܶȣ����㷽ʽ = fStandardValue/fStandardArea
	float		fStandardMeanGray;				//ģ��ƽ���Ҷ�
	float		fStandardStddev;				//ģ��ı�׼��
	float		fRealValue;						//
	float		fRealArea;						//ʵ�ʾ��ο����
	float		fRealDensity;					//ʵ�ʾ��ο��ܶ�
	float		fRealMeanGray;					//ʵ�ʾ��ο��ƽ���Ҷ�
	float		fStandardValuePercent;			//�˾���Ҫ��ı�׼ֵ���������ﵽ�����ĻҶ�ֵ�ı���
	float		fRealValuePercent;				//�˾���ʵ�ʵı���(�Ҷ�ֵ)
	float		fRealStddev;					//ģ��ı�׼��
	int			nHItem;							//�ڼ���ˮƽͬ��ͷ
	int			nVItem;							//�ڼ�����ֱͬ��ͷ
	int			nSnVal;							//��ʶ׼��֤������ 0-9
	int			nTH;							//���
	int			nAnswer;						//��ѭ�����ڵڼ����𰸣���1-A,2-B,3-C,4-D,5-E,6-F...
	int			nSingle;						//0-��ѡ��1-��ѡ, 2-�ж���
	int			nRecogFlag;						//ʶ���ʶ��ʶ��SNʱ--ʶ�𿼺�˳����ѡ���Ŀ��Ŵ��ڱ�ʶֵ��ʶ��OMRʱ--ʶ�����˳����ѡ����OMR���ô��ڵı�ʶֵ
	int			nZkzhType;						//׼��֤�ŵ����ͣ�1-OMR��2-����or��ά��
	
	int		nGaussKernel;		//��˹��
	int		nSharpKernel;		//��
	int		nCannyKernel;		//��Ե
	int		nDilateKernel;		//����

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

typedef std::list<RECTINFO> RECTLIST;			//����λ���б�

typedef struct _OmrQuestion_			//��Ŀ
{
	int nTH;
	int nSingle;						//0-��ѡ��1-��ѡ, 2-�ж���
	std::string strRecogVal;			//ʶ������A��B��C...
	RECTLIST	lSelAnswer;				//ѡ���б�
	_OmrQuestion_()
	{
		nTH = -1;
		nSingle = 0;
	}
}OMR_QUESTION, *pOMR_QUESTION;
typedef std::list<OMR_QUESTION> OMRLIST;

typedef struct _ElectOmrGroupInfo_	//ѡ��������Ϣ
{
	int nGroupID;		//�ڼ���ѡ����
	int nAllCount;		//��ѡ��
	int nRealCount;		//��Чѡ��			3ѡ2�����Ϊ2
	_ElectOmrGroupInfo_()
	{
		nGroupID = 0;
		nAllCount = 0;
		nRealCount = 0;
	}
}ELECTOMRGROUPINFO, *pELECTOMRGROUPINFO;

typedef struct _ElectOmrQuestion_	//ѡ����
{
	int		nDoubt;				//0-�޻���, 1-�л���, 2-��ֵ
	std::string strRecogResult;	//ʶ����	1\2\3...
	std::string strRecogResult2;	//ʶ����	1\2\3...
	ELECTOMRGROUPINFO sElectOmrGroupInfo;
	RECTLIST lItemInfo;	//ѡ����Ϣ
	_ElectOmrQuestion_()
	{
		nDoubt = 0;
	}
}ELECTOMR_QUESTION, *pELECTOMR_QUESTION;
typedef std::list<ELECTOMR_QUESTION> ELECTOMR_LIST;

typedef struct _OmrResult_
{
	int		nTH;				//���
	int		nSingle;			//0-��ѡ��1-��ѡ, 2-�ж���
	int		nDoubt;				//0-�޻���, 1-�л���, 2-��ֵ
	std::string strRecogVal;	//����ʶ������A��B��C...
	std::string strRecogVal1;
	std::string strRecogVal2;
	std::string strRecogVal3;
	RECTLIST	lSelAnswer;				//ѡ���б�
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
	int nItem;			//�ڼ�λ��
	int nRecogVal;		//ʶ��Ľ��
	RECTLIST	lSN;
	_SN_()
	{
		nItem = -1;
	}
}SN_ITEM, *pSN_ITEM;
typedef std::list<pSN_ITEM> SNLIST;

typedef struct _PaperModel_
{
	int			nPaper;					//��ʶ��ģ�����ڵڼ����Ծ�
	int			nPicW;					//ͼƬ��
	int			nPicH;					//ͼƬ��
	int			nPaperType;				//�Ծ����ͣ�A3-1��A4-2
	std::string	strModelPicName;		//ģ��ͼƬ����
	cv::Rect	rtHTracker;
	cv::Rect	rtVTracker;
//	cv::Rect	rtSNTracker;
	RECTINFO	rcSNTracker;
	SNLIST		lSNInfo;				//SN��Ϣ
	RECTLIST	lSelHTracker;			//ѡ���ˮƽͬ��ͷ����
	RECTLIST	lSelVTracker;			//ѡ��Ĵ�ֱͬ��ͷ����
	RECTLIST	lSelFixRoi;				//ѡ�񶨵��ROI�ľ����б���ѡ����Ĵ���ο�
	RECTLIST	lFix;					//�����б�
	RECTLIST	lH_Head;				//ˮƽУ����б�
	RECTLIST	lV_Head;				//��ֱͬ��ͷ�б�
	RECTLIST	lABModel;				//����У���
	RECTLIST	lCourse;				//��ĿУ���
	RECTLIST	lQK_CP;					//ȱ��У���
	RECTLIST	lWJ_CP;					//Υ��У���
	RECTLIST	lGray;					//�Ҷ�У���
	RECTLIST	lWhite;					//�հ�У���
	OMRLIST		lOMR2;
	ELECTOMR_LIST	lElectOmr;			//ѡ�����б�
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
	int			nType;					//���ͣ�0-ͨ��ɨ���ͼƬ�ֶ������ģ�1-ͨ���ƾ����Զ����ɵ�
	int			nEnableModify;			//ģ���Ƿ�����޸�
	int			nPicNum;				//ͼƬ����
	int			nABModel;				//�Ƿ���AB��ģʽ
	int			nHasHead;				//�Ƿ���ˮƽ�ʹ�ֱͬ��ͷ
	int			nHasElectOmr;			//�Ƿ���ѡ����
	int			nZkzhType;				//׼��֤��ʶ������: 1 - OMR��2 - ����or��ά��
	int			nExamID;
	int			nSubjectID;
	int			nSaveMode;				//����ģʽ: 1-����ģʽ��2-Զ������ģʽ
	int			nScanDpi;				//ɨ��ͼƬdpi
	int			nScanSize;				//ɨ��ͼƬ��С��1-A4��2-A3��3-����
	int			nScanType;				//ɨ��ģʽ��1-�Ҷ�ɨ�裬2-��ɫɨ��
	int			nAutoCut;				//ɨ���ǵ��Զ��ü�����(��Գ���ֽ���ܴ򿪴˿���)
	
	std::string	strModelName;			//ģ������
	std::string	strModelDesc;			//ģ������

	std::vector<pPAPERMODEL> vecPaperModel;	//�洢ÿһҳ�Ծ��ģ����Ϣ
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
typedef std::list<pMODEL> MODELLIST;	//ģ���б�

//���ֶ�λ��Ϣ
typedef struct _CharacterRectInfo_
{
	int			nIndex;							//ʶ���������
	float		fConfidence;					//ʶ������ֵ
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
	int		nIndex;							//ʶ���������

	int		nThresholdValue;				//�˾���ʶ��ʱҪ��ı�׼ֵ�����ﵽ�ĻҶ�ֵ�ķ�ֵ
	int		nGaussKernel;		//��˹��
	int		nSharpKernel;		//��
	int		nCannyKernel;		//��Ե
	int		nDilateKernel;		//����

	cv::Rect	rt;				//ʶ�������
	std::vector<ST_CHARACTER_RECTINFO> vecCharacterRt;	//ÿ�����ֵ�����
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
typedef struct _PicInfo_				//ͼƬ��Ϣ
{
	bool			bRecoged;		//�Ƿ��Ѿ�ʶ���
	bool			bFindIssue;		//�Ƿ��ҵ������
	void*			pPaper;			//�����Ծ����Ϣ
	cv::Rect		rtFix;			//�������
	std::string		strPicName;		//ͼƬ����
	std::string		strPicPath;		//ͼƬ·��
	RECTLIST		lFix;			//�����б�
	RECTLIST		lNormalRect;	//ʶ�������������λ��
	RECTLIST		lIssueRect;		//ʶ������������Ծ�������λ�ã�ֻҪ���������Ͳ�������һҳ��ʶ��
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
typedef std::list<pST_PicInfo> PIC_LIST;	//ͼƬ�б���

typedef struct _PaperInfo_
{
	bool		bIssuePaper;		//�Ƿ��������Ծ�
	int			nQKFlag;			//ȱ����ʶ
	pMODEL		pModel;				//ʶ���ѧ���Ծ����õ�ģ��
	void*		pPapers;			//�������Ծ����Ϣ
	void*		pSrcDlg;			//��Դ�������ĸ����ڣ�ɨ��or�����Ծ���
	std::string strStudentInfo;		//ѧ����Ϣ	
	std::string strSN;

	SNLIST				lSnResult;
	OMRRESULTLIST		lOmrResult;			//OMRRESULTLIST
	ELECTOMR_LIST		lElectOmrResult;	//ʶ���ѡ����OMR���
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
}ST_PaperInfo, *pST_PaperInfo;		//�Ծ���Ϣ��һ��ѧ����Ӧһ���Ծ�һ���Ծ�����ж��ͼƬ
typedef std::list<pST_PaperInfo> PAPER_LIST;	//�Ծ��б�

typedef struct _PapersInfo_				//�Ծ����Ϣ�ṹ��
{
	int		nPaperCount;				//�Ծ�����Ծ�������(ѧ����)
	int		nRecogErrCount;				//ʶ������Ծ�����

	//++ͳ����Ϣ
	int		nOmrDoubt;				//OMR���ɵ�����
	int		nOmrNull;				//OMRʶ��Ϊ�յ�����
	int		nSnNull;				//׼��֤��ʶ��Ϊ�յ�����

	Poco::FastMutex	fmOmrStatistics;//omrͳ����
	Poco::FastMutex fmSnStatistics; //zkzhͳ����
	//--

	Poco::FastMutex fmlPaper;			//���Ծ��б��д��
	Poco::FastMutex fmlIssue;			//�������Ծ��б��д��
	std::string  strPapersName;			//�Ծ������
	std::string	 strPapersDesc;			//�Ծ����ϸ����

	PAPER_LIST	lPaper;					//���Ծ�����Ծ��б�
	PAPER_LIST	lIssue;					//���Ծ����ʶ����������Ծ��б�
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
typedef std::list<pPAPERSINFO> PAPERS_LIST;		//�Ծ���б�

typedef struct _RecogTask_
{
	int		nPic;						//���Ծ�����ģ��ĵڼ���
	pMODEL pModel;						//ʶ���õ�ģ��
	std::string strPath;
	pST_PaperInfo	pPaper;				//��Ҫʶ����Ծ�
}RECOGTASK, *pRECOGTASK;
typedef std::list<pRECOGTASK> RECOGTASKLIST;	//ʶ�������б�
#endif