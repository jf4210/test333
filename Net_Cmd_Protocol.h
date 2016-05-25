#pragma once
//!试卷上传指令
#define REQUEST_UPLOADANS		0x1001			//文件上传
//!扫描端
#define USER_LOGIN				0x2001			//登录
#define USER_GETEXAMINFO		0x2002			//获取考试信息


//应答指令
#define RESPONSE_UPLOADANS		0x4001			//应答文件上传结果
#define USER_RESPONSE_LOGIN		0x4002			//应答扫描端登录
#define USER_RESPONSE_EXAMINFO	0x4003			//应答获取考试信息

//!通知消息
#define NOTIFY_RECVANSWERFIN		0x5001		//文件接收完成的通知

//!结果&错误码
#define RESULT_ERROR_UNKNOWN		0x6000					//未知错误
#define RESULT_SUCCESS				0x6001
#define RESULT_LOGIN_FAIL			0x6002					//登录失败
#define RESULT_EXAMINFO_SUCCESS		0x6003					//获取考试信息成功
#define RESULT_EXAMINFO_FAIL		0x6004					//获取考试信息失败


#define RESULT_ERROR_FILEIO			0x600B					//文件读写失败
#define RESULT_ERROR_CHECKMD5		0x600C					//MD5校验失败

//字符长度定义
#define VERIFYCODE			0x1122			//包头校验码
#define LEN_NAME			100
#define LEN_MD5				100
#define LEN_IPADDRESS		16
#define LEN_PWD				30


#define HEAD_SIZE	sizeof(ST_CMD_HEADER)

//!命令头
//CMD命令：wResult为请求/应答结果
typedef	struct	tagCmdHeader
{
	unsigned short		usCmd;							//命令字
	unsigned short		usVerifyCode;					//校验码
	unsigned int		uPackSize;						//包长
	unsigned short		usResult;						//结果
	tagCmdHeader()
	{
		usVerifyCode = VERIFYCODE;
		uPackSize = 0;
		usResult = RESULT_SUCCESS;
	}
}ST_CMD_HEADER, *pStCmdHeader;

typedef struct	tagLoginInfo
{
	char		szUserNo[LEN_NAME];			//用户账号、身份证
	char		szPWD[LEN_PWD];				//登陆密码
	
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

//上传的文件信息
typedef struct tagFileInfo
{
	unsigned int	dwFileLen;							//文件长度
	char			szFileName[LEN_NAME];				//文件名
	char			szMD5[LEN_MD5];						//校验码
}ST_FILE_INFO;




