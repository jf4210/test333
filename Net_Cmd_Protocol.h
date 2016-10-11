#pragma once
#include <string>

//!试卷上传指令
#define REQUEST_UPLOADANS		0x1001			//文件上传
//!扫描端
#define USER_LOGIN				0x2001			//登录
#define USER_LOGOUT				0x2002			//注销登录
#define USER_GETEXAMINFO		0x2003			//获取考试信息
#define USER_SETMODELINFO		0x2004			//设置模板信息
#define USER_NEED_DOWN_MODEL	0x2005			//请求下载模板
#define USER_DOWN_MODEL			0x2006			//下载模板
#define USER_NEED_CREATE_MODEL	0x2007			//请求服务器生成模板，用于制卷工具生成的情况
#define USER_ELECTOMR_MODEL		0x2008			//上传模板中的选做题信息

//应答指令
#define RESPONSE_UPLOADANS		0x4001			//应答文件上传结果
#define USER_RESPONSE_LOGIN		0x4002			//应答扫描端登录
#define USER_RESPONSE_LOGOUT	0x4003			//应答扫描端注销
#define USER_RESPONSE_EXAMINFO	0x4004			//应答获取考试信息
#define USER_RESPONSE_MODELINFO 0x4005			//应答设置模板信息
#define USER_RESPONSE_NEEDDOWN	0x4006			//应答请求下载模板
#define USER_RESPONSE_DOWNMODEL	0x4007			//应答下载模板
#define USER_RESPONSE_CREATE_MODEL	0x4008		//应答服务器生成模板，制卷工具生成的情况
#define USER_RESPONSE_ELECTOMR_MODEL	0x4009	//应答模板中选做题信息接收情况

//!通知消息
#define NOTIFY_RECVANSWERFIN		0x5001		//文件接收完成的通知

//!结果&错误码
#define RESULT_ERROR_UNKNOWN		0x6000					//未知错误
#define RESULT_SUCCESS				0x6001
#define RESULT_LOGIN_FAIL			0x6002					//登录失败
#define RESULT_EXAMINFO_SUCCESS		0x6003					//获取考试信息成功
#define RESULT_EXAMINFO_FAIL		0x6004					//获取考试信息失败
#define RESULT_SETMODELINFO_SEND	0x6005					//需要发送模板信息
#define RESULT_SETMODELINFO_NO		0x6006					//不需要重新发送模板信息
#define RESULT_DOWNMODEL_OK			0x6007					//可以正常下载
#define RESULT_DOWNMODEL_FAIL		0x6008					//下载的模板不存在
#define RESULT_DOWNMODEL_NONEED		0x6009					//不需要重新下载模板
#define RESULT_DOWNMODEL_RECV		0x6010					//接收模板文件
#define RESULT_CREATE_MODEL_SUCCESS	0x6011					//服务器根据后端数据成功创建扫描模板
#define RESULT_CREATE_MODEL_NOFIND	0x6012					//后端没有创建扫描模板的数据
#define RESULT_CREATE_MODEL_FAIL	0x6013					//服务器获得后端数据，但是创建扫描模板失败
#define RESULT_CREATE_MODEL_NONEED	0x6014					//已经生成了，不需要进行生成操作
#define RESULT_CREATE_MODEL_DOING	0x6015					//正在进行生成操作
#define RESULT_ELECTOMR_MODEL_FAIL	0x6016					//通知后端选做题模板信息失败

#define RESULT_ERROR_FILEIO			0x600B					//文件读写失败
#define RESULT_ERROR_CHECKMD5		0x600C					//MD5校验失败

//字符长度定义
#define VERIFYCODE			0x1122			//包头校验码
#define LEN_NAME			100
#define LEN_MD5				100
#define LEN_IPADDRESS		16
#define LEN_PWD				30
#define LEN_USERINFO		500


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

//上传的文件信息
typedef struct tagFileInfo
{
	unsigned int	dwFileLen;							//文件长度
	char			szFileName[LEN_NAME];				//文件名
	char			szMD5[LEN_MD5];						//校验码
}ST_FILE_INFO;

typedef struct tagElectOmr
{
	int		nExamID;
	int		nSubjectID;
	char	szEzs[LEN_NAME];
}ST_UPLOAD_ELECTOMR, *pST_UPLOAD_ELECTOMR;


