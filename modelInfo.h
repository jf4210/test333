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
	CHARACTER_AREA,	//文字定位区
	PAGINATION,		//页码标识
	ZGT				//主观题区域
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
	float		fMeanGray_Contract;				//使用对比度亮度调整后的平均灰度
	float		fStandardValuePercent;			//此矩形要求的标准值比例，即达到给定的灰度值的比例
	float		fRealValuePercent;				//此矩形实际的比例(灰度值)
	float		fRealStddev;					//模板的标准差
	int			nHItem;							//第几个水平同步头
	int			nVItem;							//第几个垂直同步头
	int			nSnVal;							//标识准考证的数字 0-9
	int			nTH;							//题号，用于文字识别时表示属于第几个识别区，用于定点:表按框选顺序的第几个定点，选做题时表示第几组
	int			nAnswer;						//答案循序，属于第几个答案，如0-A,1-B,2-C,3-D,4-E,5-F...,用于文字识别时表示属于当前识别区的第几个识别项，如第1个、第2个识别字
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
		fMeanGray_Contract = 0.0;
		
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
	int		nPageId;			//页面ID，属于第几页的Omr, 1,2,3...
	std::string strRecogResult;	//识别结果	1\2\3...
	std::string strRecogResult2;	//识别结果	1\2\3...
	ELECTOMRGROUPINFO sElectOmrGroupInfo;
	RECTLIST lItemInfo;	//选项信息
	_ElectOmrQuestion_()
	{
		nDoubt = 0;
		nPageId = 0;
	}
}ELECTOMR_QUESTION, *pELECTOMR_QUESTION;
typedef std::list<ELECTOMR_QUESTION> ELECTOMR_LIST;

typedef struct _OmrResult_
{
	int		nTH;				//题号
	int		nSingle;			//0-单选，1-多选, 2-判断题
	int		nDoubt;				//0-无怀疑, 1-有怀疑, 2-空值
	int		nPageId;			//页面ID，属于第几页的Omr, 1,2,3...
	float fWhiteAreaGray;
	float fWhiteAreaGrayModel;
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
		nPageId = 1;
		fWhiteAreaGray = 0.0;
		fWhiteAreaGrayModel = 0.0;
	}
}OMR_RESULT, *pOMR_RESULT;
typedef std::list<OMR_RESULT> OMRRESULTLIST;

typedef struct _SN_
{
	int nItem;			//第几位数
	int nRecogVal;		//识别的结果
	cv::Rect rt;		//识别结果的位置
	RECTLIST	lSN;
	_SN_()
	{
		nItem = -1;
	}
}SN_ITEM, *pSN_ITEM;
typedef std::list<pSN_ITEM> SNLIST;

//文字定位点信息
typedef struct _CharacterAnchorPoint_
{
	int			nIndex;							//识别次序索引
	float		fConfidence;					//识别信心值
	std::string strVal;
	RECTINFO	rc;
	_CharacterAnchorPoint_()
	{
		nIndex = -1;
		fConfidence = 0.0;
	}
}ST_CHARACTER_ANCHOR_POINT, *pST_CHARACTER_ANCHOR_POINT;

//文字定位区域
typedef struct _CharacterAnchorArea_
{
	int		nIndex;							//识别次序索引

	int		nThresholdValue;				//此矩形识别时要求的标准值，即达到的灰度值的阀值
	int		nGaussKernel;		//高斯核
	int		nSharpKernel;		//锐化
	int		nCannyKernel;		//边缘
	int		nDilateKernel;		//膨胀
	int		nCharacterConfidence;	//文字识别要求的信心值

	int		arryMaxDist[2];		//距离最大的两个字的索引, 如果只有1个字，则第2个数组置-1

	int		nRects;				//当前区域内查找到的矩形数量，在判断图像方向时有用
//	Poco::FastMutex rectsLock;	//nRects的锁

	cv::Rect	rt;				//识别大区域
	std::vector<pST_CHARACTER_ANCHOR_POINT> vecCharacterRt;	//每个文字定位点的信息
	_CharacterAnchorArea_()
	{
		nIndex = -1;
		nThresholdValue = 0;
		nGaussKernel = 5;
		nSharpKernel = 5;
		nCannyKernel = 90;
		nDilateKernel = 6;
		nCharacterConfidence = 60;
		arryMaxDist[0] = 0;
		arryMaxDist[1] = 0;
		nRects = -1;
	}
	~_CharacterAnchorArea_()
	{
		for (int i = 0; i < vecCharacterRt.size(); i++)
			SAFE_RELEASE(vecCharacterRt[i]);
	}
}ST_CHARACTER_ANCHOR_AREA, *pST_CHARACTER_ANCHOR_AREA;
typedef std::list<pST_CHARACTER_ANCHOR_AREA> CHARACTER_ANCHOR_AREA_LIST;	//文字定位区域列表定义

typedef struct _zgtOmrScoreRt_
{
	float fScore;			//该分数块的分值
	cv::Rect rt;			//该分数块的坐标
}ST_ZgtOmrScoreRect, *pST_ZgtOmrScoreRect;		//主观题: 圈阅部分每个分数识别块的分数信息即位置

typedef struct _zgtHandRecog_
{
	int nFlag;		//1-得分加，2-得分减
	cv::Rect rtHandRecog;	//分数识别区, 含3个部分，前面是+/-，后面两位是手写的分数
	_zgtHandRecog_()
	{
		nFlag = 1;
	}
}ST_ZgtHandRecogScore, *pST_ZgtHandRecogScore;		//主观题: 手写分数识别

typedef struct _zgtOmrRecog_
{
	//<=20分, 有22个给分框(含0.5), >20分, 分十位数、个位数给分框(含0.5, 11个框)
	int nPotFive;			//解答题: 该题是否有0.5分
	int nRtW;				//解答题: 每个分数框的宽度
	int nRtH;				//解答题: 每个分数框的高度
	cv::Rect rtScore;		//解答题: 整个分数栏的坐标, 矩形框定位方法: 最右边为0.5分数框，依次0-9，再间隔一空，再十分位
	std::list<ST_ZgtOmrScoreRect> scoreList;	//解答题: 每个分数块的信息列表

	std::list<cv::Rect> rtList;			//填空题的圈阅识别，每个空对应一个矩形框，打叉的就扣分，什么都不做的就表示正确
}ST_ZgtOmrRecogScore, *pST_ZgtOmrRecogScore;		//主观题: 圈阅分数识别

typedef struct _zgtScore_
{
	int nRecogType;		//1-手写识别, 2-圈阅识别
	int nScores;		//该题总分
	pST_ZgtHandRecogScore pScoreHandRecog;		//分数手写识别
	pST_ZgtOmrRecogScore pScoreOmrRecog;		//分数圈阅识别
	_zgtScore_()
	{
		nRecogType = 1;
		nScores = 0;
		pScoreHandRecog = NULL;
		pScoreOmrRecog = NULL;
	}
	~_zgtScore_()
	{
		SAFE_RELEASE(pScoreHandRecog);
		SAFE_RELEASE(pScoreOmrRecog);
	}
}ST_ZgtScore, *pST_ZgtScore;		//主观题分数识别信息

typedef struct _ZgtRegion_
{
	int nId;			//该题的答题区ID，可能存在多个答题区，比如2个，一部分在第2栏下面，一部分在第3栏上面
	int nPageId;		//该部分答题区所在试卷的第几页，从0计算
	cv::Rect rt;
}ST_ZgtRegion, *pST_ZgtRegion;		//主观题的答题区域

typedef struct _Zgt_
{
	int nType;			//题目类型		1-填空题, 2-解答题，3-英语作文，4-语文作文，5-选做题...
	int nTh;			//题号
	pST_ZgtScore pRecogScore;	//手阅的分数识别部分
	std::vector<ST_ZgtRegion> vecRegion;
	_Zgt_()
	{
		nType = 2;
		nTh = 0;
		pRecogScore = NULL;
	}
	~_Zgt_()
	{
		SAFE_RELEASE(pRecogScore);
	}
}ST_ZGT, *pST_ZGT;
typedef std::list<ST_ZGT>	ZGT_LIST;

typedef struct _PaperModel_
{
	int			nPaper;					//标识此模板属于第几张试卷
	int			nPicW;					//图片宽
	int			nPicH;					//图片高
	int			nPaperType;				//试卷类型，A4-1, A3-2
	int			nPicSaveRotation;		/*图片保存方向, 图像的原始方向，相对视觉的方向(即考试作答方向)，在文字识别时要调整到视觉正常方向，模板保存时设置
										0:未知方向，1: 正常视觉方向(考试作答方向)，2-正常方向左旋90后的方向，3-正常方向右旋90后的方向，4-正常方向旋转180度后的方向*/
	std::string	strModelPicName;		//模板图片名称
	std::string strModelPicPath;		//模板图片路径
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
	RECTLIST	lPagination;			//页码点
	OMRLIST		lOMR2;
	ELECTOMR_LIST	lElectOmr;			//选做题列表
	CHARACTER_ANCHOR_AREA_LIST lCharacterAnchorArea;	//文字识别定位区域
	ZGT_LIST	lZgt;					//主观题列表
	cv::Mat		matModel;				//模板的图像，在文字识别部分用到了模板匹配，需要模板的图像

	_PaperModel_()
	{
		nPicSaveRotation = 0;
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
		CHARACTER_ANCHOR_AREA_LIST::iterator itCharAnchorArea = lCharacterAnchorArea.begin();
		for (; itCharAnchorArea != lCharacterAnchorArea.end();)
		{
			pST_CHARACTER_ANCHOR_AREA pCharAnchorArea = *itCharAnchorArea;
			itCharAnchorArea = lCharacterAnchorArea.erase(itCharAnchorArea);
			SAFE_RELEASE(pCharAnchorArea);
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

	int			nUseWordAnchorPoint;	//是否使用文字作为定点，0-不用，默认用黑框做定点，1-使用文字识别做定点
	int			nCharacterAnchorPoint;	//用来计算矩形位置的文字定点个数
	int			nUsePagination;			//是否使用页码标识，针对多页试卷的情况，默认不开启
	int			nLastPageBlank;			//针对多页模式，最后一页空白

	int			nChkLostCorner;			//是否进行缺角检测
	int			nCardType;				//卡类型：0-网阅卡，1-手阅卡(手阅卡需要后台去识别手写分数,不需要进行主观题划分了)
	
	std::string strExamUUID;
	std::string strSubjectUUID;

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
		nUseWordAnchorPoint = 0;
		nCharacterAnchorPoint = 4;
		nUsePagination = 0;
		nLastPageBlank = 0;
		nChkLostCorner = 0;
		nCardType = 0;
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

