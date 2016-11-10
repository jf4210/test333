#pragma once
#include <string>

#define GET_FILELIST				0x1001					//��ȡ�ļ��б�
#define GET_FILE					0x1002					//���������ļ�

#define RESPONSE_GET_FILELIST		0x4001					//�ظ��ļ��б�
#define RESPONSE_GET_FILE			0x4002					//�ظ������ļ�

//!���&������
#define RESULT_ERROR_UNKNOWN		0x6000					//δ֪����
#define RESULT_SUCCESS				0x6001
#define RESULT_FILE_NULL			0x6002					//�ļ��б�Ϊ��

#define RESULT_ERROR_FILEIO			0x600B					//�ļ���дʧ��
#define RESULT_ERROR_CHECKMD5		0x600C					//MD5У��ʧ��

//�ַ����ȶ���
#define VERIFYCODE			0x1122			//��ͷУ����
#define LEN_NAME			100
#define LEN_MD5				100
#define LEN_IPADDRESS		16
#define LEN_PWD				30
#define LEN_USERINFO		500


#define HEAD_SIZE	sizeof(ST_CMD_HEADERTOVER)

//!����ͷ
//CMD���wResultΪ����/Ӧ����
typedef	struct	tagCmdHeaderToVer
{
	unsigned short		usCmd;							//������
	unsigned short		usVerifyCode;					//У����
	unsigned int		uPackSize;						//����
	unsigned short		usResult;						//���
	tagCmdHeaderToVer()
	{
		usVerifyCode = VERIFYCODE;
		uPackSize = 0;
		usResult = RESULT_SUCCESS;
	}
}ST_CMD_HEADERTOVER, *pStCmdHeaderToVer;


