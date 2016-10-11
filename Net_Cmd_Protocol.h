#pragma once
#include <string>

//!�Ծ��ϴ�ָ��
#define REQUEST_UPLOADANS		0x1001			//�ļ��ϴ�
//!ɨ���
#define USER_LOGIN				0x2001			//��¼
#define USER_LOGOUT				0x2002			//ע����¼
#define USER_GETEXAMINFO		0x2003			//��ȡ������Ϣ
#define USER_SETMODELINFO		0x2004			//����ģ����Ϣ
#define USER_NEED_DOWN_MODEL	0x2005			//��������ģ��
#define USER_DOWN_MODEL			0x2006			//����ģ��
#define USER_NEED_CREATE_MODEL	0x2007			//�������������ģ�壬�����ƾ������ɵ����
#define USER_ELECTOMR_MODEL		0x2008			//�ϴ�ģ���е�ѡ������Ϣ

//Ӧ��ָ��
#define RESPONSE_UPLOADANS		0x4001			//Ӧ���ļ��ϴ����
#define USER_RESPONSE_LOGIN		0x4002			//Ӧ��ɨ��˵�¼
#define USER_RESPONSE_LOGOUT	0x4003			//Ӧ��ɨ���ע��
#define USER_RESPONSE_EXAMINFO	0x4004			//Ӧ���ȡ������Ϣ
#define USER_RESPONSE_MODELINFO 0x4005			//Ӧ������ģ����Ϣ
#define USER_RESPONSE_NEEDDOWN	0x4006			//Ӧ����������ģ��
#define USER_RESPONSE_DOWNMODEL	0x4007			//Ӧ������ģ��
#define USER_RESPONSE_CREATE_MODEL	0x4008		//Ӧ�����������ģ�壬�ƾ������ɵ����
#define USER_RESPONSE_ELECTOMR_MODEL	0x4009	//Ӧ��ģ����ѡ������Ϣ�������

//!֪ͨ��Ϣ
#define NOTIFY_RECVANSWERFIN		0x5001		//�ļ�������ɵ�֪ͨ

//!���&������
#define RESULT_ERROR_UNKNOWN		0x6000					//δ֪����
#define RESULT_SUCCESS				0x6001
#define RESULT_LOGIN_FAIL			0x6002					//��¼ʧ��
#define RESULT_EXAMINFO_SUCCESS		0x6003					//��ȡ������Ϣ�ɹ�
#define RESULT_EXAMINFO_FAIL		0x6004					//��ȡ������Ϣʧ��
#define RESULT_SETMODELINFO_SEND	0x6005					//��Ҫ����ģ����Ϣ
#define RESULT_SETMODELINFO_NO		0x6006					//����Ҫ���·���ģ����Ϣ
#define RESULT_DOWNMODEL_OK			0x6007					//������������
#define RESULT_DOWNMODEL_FAIL		0x6008					//���ص�ģ�岻����
#define RESULT_DOWNMODEL_NONEED		0x6009					//����Ҫ��������ģ��
#define RESULT_DOWNMODEL_RECV		0x6010					//����ģ���ļ�
#define RESULT_CREATE_MODEL_SUCCESS	0x6011					//���������ݺ�����ݳɹ�����ɨ��ģ��
#define RESULT_CREATE_MODEL_NOFIND	0x6012					//���û�д���ɨ��ģ�������
#define RESULT_CREATE_MODEL_FAIL	0x6013					//��������ú�����ݣ����Ǵ���ɨ��ģ��ʧ��
#define RESULT_CREATE_MODEL_NONEED	0x6014					//�Ѿ������ˣ�����Ҫ�������ɲ���
#define RESULT_CREATE_MODEL_DOING	0x6015					//���ڽ������ɲ���
#define RESULT_ELECTOMR_MODEL_FAIL	0x6016					//֪ͨ���ѡ����ģ����Ϣʧ��

#define RESULT_ERROR_FILEIO			0x600B					//�ļ���дʧ��
#define RESULT_ERROR_CHECKMD5		0x600C					//MD5У��ʧ��

//�ַ����ȶ���
#define VERIFYCODE			0x1122			//��ͷУ����
#define LEN_NAME			100
#define LEN_MD5				100
#define LEN_IPADDRESS		16
#define LEN_PWD				30
#define LEN_USERINFO		500


#define HEAD_SIZE	sizeof(ST_CMD_HEADER)

//!����ͷ
//CMD���wResultΪ����/Ӧ����
typedef	struct	tagCmdHeader
{
	unsigned short		usCmd;							//������
	unsigned short		usVerifyCode;					//У����
	unsigned int		uPackSize;						//����
	unsigned short		usResult;						//���
	tagCmdHeader()
	{
		usVerifyCode = VERIFYCODE;
		uPackSize = 0;
		usResult = RESULT_SUCCESS;
	}
}ST_CMD_HEADER, *pStCmdHeader;

typedef struct	tagLoginInfo
{
	char		szUserNo[LEN_NAME];			//�û��˺š����֤
	char		szPWD[LEN_PWD];				//��½����
	
	tagLoginInfo()
	{
	}
}ST_LOGIN_INFO, *pStLoginInfo;

typedef struct tagLoginResult
{
	int		nTeacherId;
	int		nUserId;
	char	szEzs[LEN_NAME];
	char	szUserInfo[LEN_USERINFO];
}ST_LOGIN_RESULT, *pST_LOGIN_RESULT;

typedef struct tagGetExamInfo
{
	char	szEzs[LEN_NAME];
	tagGetExamInfo()
	{
	}
}ST_EXAM_INFO, *pStExamInfo;

typedef struct tagModelInfo
{
	int		nExamID;
	int		nSubjectID;
	char	szUserNo[LEN_NAME];
	char	szMD5[LEN_MD5];
	char	szModelName[LEN_NAME];
	char	szEzs[LEN_NAME];
}ST_MODELINFO, *pST_MODELINFO;

typedef struct tagDownModel
{
	int		nExamID;
	int		nSubjectID;
	int		nModelSize;
	char	szUserNo[LEN_NAME];
	char	szMD5[LEN_MD5];
	char	szModelName[LEN_NAME];
}ST_DOWN_MODEL, *pST_DOWN_MODEL;

typedef struct tagCreateModel
{
	int		nExamID;
	int		nSubjectID;
	char	szEzs[LEN_NAME];
}ST_CREATE_MODEL, *pST_CREATE_MODEL;

//�ϴ����ļ���Ϣ
typedef struct tagFileInfo
{
	unsigned int	dwFileLen;							//�ļ�����
	char			szFileName[LEN_NAME];				//�ļ���
	char			szMD5[LEN_MD5];						//У����
}ST_FILE_INFO;

typedef struct tagElectOmr
{
	int		nExamID;
	int		nSubjectID;
	char	szEzs[LEN_NAME];
}ST_UPLOAD_ELECTOMR, *pST_UPLOAD_ELECTOMR;


