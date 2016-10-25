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
	GRAY_CP,		//�Ҷ�У��
	WHITE_CP,		//��У��
	SN,				//������
	OMR,			//ѡ��������
	ELECT_OMR		//ѡ����
};

typedef struct _RectInfo_
{
	CPType		eCPType;						//У�������
	int			nThresholdValue;				//�˾���ʶ��ʱҪ��ı�׼ֵ�����ﵽ�ĻҶ�ֵ�ķ�ֵ
	float		fStandardValue;					//�˾���ʶ��ʱ��׼����ֵ�������ջҶȷ�ֵ����ĻҶ�ֵ
	float		fStandardArea;					//ģ����ο�����������ܶ���
	float		fStandardDensity;				//ģ����ο���ܶȣ����㷽ʽ = fStandardValue/fStandardArea
	float		fRealValue;						//
	float		fRealArea;						//ʵ�ʾ��ο����
	float		fRealDensity;					//ʵ�ʾ��ο��ܶ�
	float		fStandardValuePercent;			//�˾���Ҫ��ı�׼ֵ���������ﵽ�����ĻҶ�ֵ�ı���
	float		fRealValuePercent;				//�˾���ʵ�ʵı���(�Ҷ�ֵ)
	int			nHItem;							//�ڼ���ˮƽͬ��ͷ
	int			nVItem;							//�ڼ�����ֱͬ��ͷ
	int			nSnVal;							//��ʶ׼��֤������ 0-9
	int			nTH;							//���
	int			nAnswer;						//��ѭ�����ڵڼ����𰸣���1-A,2-B,3-C,4-D,5-E,6-F...
	int			nSingle;						//0-��ѡ��1-��ѡ
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
		fRealValue = 0.0;
		fStandardArea = 0.0;
		fStandardDensity = 0.0;
		fRealArea = 0.0;
		fRealDensity = 0.0;
		
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
	int nSingle;						//0-��ѡ��1-��ѡ
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
	std::string strRecogResult;	//ʶ����	1\2\3...
	ELECTOMRGROUPINFO sElectOmrGroupInfo;
	RECTLIST lItemInfo;	//ѡ����Ϣ
}ELECTOMR_QUESTION, *pELECTOMR_QUESTION;
typedef std::list<ELECTOMR_QUESTION> ELECTOMR_LIST;

typedef struct _OmrResult_
{
	int		nTH;				//���
	int		nSingle;			//0-��ѡ��1-��ѡ
	int		nDoubt;				//0-�޻���, 1-�л���, 2-��ֵ
	std::string strRecogVal;	//ʶ������A��B��C...
	std::string strRecogVal2;
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
	std::string	strModelPicName;		//ģ��ͼƬ����
	cv::Rect	rtHTracker;
	cv::Rect	rtVTracker;
	cv::Rect	rtSNTracker;
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
	RECTLIST	lGray;					//�Ҷ�У���
	RECTLIST	lWhite;					//�հ�У���
	OMRLIST		lOMR2;
	ELECTOMR_LIST	lElectOmr;			//��ѡ���б�
	_PaperModel_()
	{
		nPaper = -1;
		nPicW = -1;
		nPicH = -1;
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
	
	std::string	strModelName;			//ģ������
	std::string	strModelDesc;			//ģ������

	std::vector<pPAPERMODEL> vecPaperModel;	//�洢ÿһҳ�Ծ��ģ����Ϣ
	_Model_()
	{
		nType = 0;
		nEnableModify = 1;
		nPicNum = 0;
		nABModel = 0;
		nHasHead = 1;
		nHasElectOmr = 0;
		nExamID = 0;
		nSubjectID = 0;
		nSaveMode = 1;
		nZkzhType = 1;
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
