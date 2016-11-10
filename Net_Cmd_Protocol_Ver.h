#pragma once
#include <string>

#define GET_FILELIST				0x1001					//获取文件列表
#define GET_FILE					0x1002					//请求下载文件

#define RESPONSE_GET_FILELIST		0x4001					//回复文件列表
#define RESPONSE_GET_FILE			0x4002					//回复下载文件

//!结果&错误码
#define RESULT_ERROR_UNKNOWN		0x6000					//未知错误
#define RESULT_SUCCESS				0x6001
#define RESULT_FILE_NULL			0x6002					//文件列表为空

#define RESULT_ERROR_FILEIO			0x600B					//文件读写失败
#define RESULT_ERROR_CHECKMD5		0x600C					//MD5校验失败

//字符长度定义
#define VERIFYCODE			0x1122			//包头校验码
#define LEN_NAME			100
#define LEN_MD5				100
#define LEN_IPADDRESS		16
#define LEN_PWD				30
#define LEN_USERINFO		500


#define HEAD_SIZE	sizeof(ST_CMD_HEADERTOVER)

//!命令头
//CMD命令：wResult为请求/应答结果
typedef	struct	tagCmdHeaderToVer
{
	unsigned short		usCmd;							//命令字
	unsigned short		usVerifyCode;					//校验码
	unsigned int		uPackSize;						//包长
	unsigned short		usResult;						//结果
	tagCmdHeaderToVer()
	{
		usVerifyCode = VERIFYCODE;
		uPackSize = 0;
		usResult = RESULT_SUCCESS;
	}
}ST_CMD_HEADERTOVER, *pStCmdHeaderToVer;


