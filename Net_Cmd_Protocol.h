#pragma once
//!�Ծ��ϴ�ָ��
#define REQUEST_UPLOADANS		0x1001			//�ļ��ϴ�
//!ɨ���
#define USER_LOGIN				0x2001			//��¼
#define USER_GETEXAMINFO		0x2002			//��ȡ������Ϣ


//Ӧ��ָ��
#define RESPONSE_UPLOADANS		0x4001			//Ӧ���ļ��ϴ����
#define USER_RESPONSE_LOGIN		0x4002			//Ӧ��ɨ��˵�¼
#define USER_RESPONSE_EXAMINFO	0x4003			//Ӧ���ȡ������Ϣ

//!֪ͨ��Ϣ
#define NOTIFY_RECVANSWERFIN		0x5001		//�ļ�������ɵ�֪ͨ

//!���&������
#define RESULT_ERROR_UNKNOWN		0x6000					//δ֪����
#define RESULT_SUCCESS				0x6001
#define RESULT_LOGIN_FAIL			0x6002					//��¼ʧ��
#define RESULT_EXAMINFO_SUCCESS		0x6003					//��ȡ������Ϣ�ɹ�
#define RESULT_EXAMINFO_FAIL		0x6004					//��ȡ������Ϣʧ��


#define RESULT_ERROR_FILEIO			0x600B					//�ļ���дʧ��
#define RESULT_ERROR_CHECKMD5		0x600C					//MD5У��ʧ��

//�ַ����ȶ���
#define VERIFYCODE			0x1122			//��ͷУ����
#define LEN_NAME			100
#define LEN_MD5				100
#define LEN_IPADDRESS		16
#define LEN_PWD				30


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
// 		memset(szUserNo, 0, LEN_NAME);
// 		memset(szPWD, 0, LEN_PWD);
	}
}ST_LOGIN_INFO, *pStLoginInfo;

typedef struct tagGetExamInfo
{
	char	szEzs[LEN_NAME];
	tagGetExamInfo()
	{
//		memset(szEzs, 0, LEN_NAME);
	}
}ST_EXAM_INFO, *pStExamInfo;

//�ϴ����ļ���Ϣ
typedef struct tagFileInfo
{
	unsigned int	dwFileLen;							//�ļ�����
	char			szFileName[LEN_NAME];				//�ļ���
	char			szMD5[LEN_MD5];						//У����
}ST_FILE_INFO;




