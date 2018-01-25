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
//#define USER_ELECTOMR_MODEL		0x2008			//上传模板中的选做题信息
#define USER_LOGIN_4TY			0x2008			//登录天喻平台信息，天喻专用
#define USER_GET_BMK			0x2009			//客户端获取报名库信息(科目报名库)
#define USER_GET_EXAM_BMK		0x2010			//客户端获取报名库信息(整个考试的报名库)
#define USER_GET_FILE_UPLOAD_ADDR	0x2011		//客户端请求文件上传地址
#define USER_NEED_UP_MODEL_PIC	0x2012			//客户端请求上传模板图片
//#define USER_MODEL_PIC_SEND		0x2013			//模板图片开始发送
#define USER_GET_MODEL_PIC		0x2013			//客户端请求下载模板图片
#define USER_CHK_NEW_GUARDEXE	0x2014			//检查是否有新的守护进程

//守护进程
#define GET_VERSERVER_ADDR		0x3001			//获取版本控制服务器的地址信息

#define RESPONSE_GET_VERSERVER_ADDR 0x3501		//应答版本服务器地址信息

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
#define USER_RESPONSE_GET_BMK		0x4010		//应答客户端获取报名库请求(科目报名库)
#define USER_RESPONSE_GET_EXAM_BMK	0x4011		//应答客户端获取报名库请求(整个考试的报名库)
#define USER_RESPONSE_GET_FILE_UPLOAD_ADDR	0x4012	//应答客户端请求文件上传地址
#define USER_RESPONSE_NEED_UP_MODEL_PIC		0x4013	//应答客户端请求上传模板图片
#define USER_RESPONSE_GET_MODEL_PIC	0x4014			//应答客户端请求下载模板图片
#define USER_RESPONSE_CHK_NEW_GUARDEXE		0x4015	//应答客户端检查是否有新的守护进程

//!通知消息
#define NOTIFY_RECVANSWERFIN		0x5001		//文件接收完成的通知

#define KEEPALIVE_PKG				0x5050		//心跳包

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
#define RESULT_LOGIN_PLATFORM_TY	0x6017					//登录平台选择，天喻专用
#define RESULT_GET_BMK_SUCCESS		0x6018					//获取报名库成功
#define RESULT_GET_BMK_FAIL			0x6019					//获取报名库失败
#define RESULT_GET_FILE_ADDR_SUCCESS 0x6020					//获取文件服务器地址成功
#define RESULT_GET_FILE_ADDR_FAIL	0x6021					//获取文件服务器地址失败
#define RESULT_UP_MODEL_PIC_SEND	0x6022					//可以上传模板图像
#define RESULT_UP_MODEL_PIC_NONEED	0x6023					//可以上传模板图像
#define RESULT_UP_MODEL_PIC_SUCCESS	0x6024					//上传模板图像成功
#define RESULT_GET_MODEL_PIC_SUCCESS	0x6025				//下载模板图像成功
#define RESULT_GET_MODEL_PIC_NOPIC	0x6026					//模板图像不存在
#define RESULT_GET_NEW_GUARDEXE_NOFILE	0x6027				//服务器上新守护进程不存在
#define RESULT_GET_NEW_GUARDEXE_NONEED	0x6028				//客户端上的守护进程和服务器一致，不需要下载
#define RESULT_GET_NEW_GUARDEXE_SUCCESS 0x6029				//发送新守护进程数据成功

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

typedef struct	tagLoginInfo4TY				//天喻多平台登录
{
	char		szUserNo[LEN_NAME];			//用户账号、身份证
	char		szPWD[LEN_PWD];				//登陆密码
	char		szPlatformCode[30];			//平台代码
	char		szEncryption[30];			//平台加密方式
	char		szPlatformUrl[200];			//平台url

	tagLoginInfo4TY()
	{
	}
}ST_LOGIN_INFO4TY, *pStLoginInfo4TY;

typedef struct tagGetExamInfo
{
	char	szEzs[LEN_NAME];
	tagGetExamInfo()
	{
	}
}ST_EXAM_INFO, *pStExamInfo;

typedef struct tagGetBmkInfo
{
	int		nExamID;
	int		nSubjectID;
	char	szEzs[LEN_NAME];
	tagGetBmkInfo()
	{
	}
}ST_GET_BMK_INFO, *pStGetBmkInfo;

typedef struct tagModelInfo
{
	int		nExamID;
	int		nSubjectID;
	char	szUserNo[LEN_NAME];
	char	szMD5[LEN_MD5];
	char	szModelName[LEN_NAME];
	char	szEzs[LEN_NAME];
	char	szElectOmr[2000];
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
	char	szSubjectName[50];
	char	szExamName[LEN_NAME];
}ST_CREATE_MODEL, *pST_CREATE_MODEL;

//模板图片上传请求
typedef struct tagModelPic
{
	int		nIndex;
	int		nExamID;
	int		nSubjectID;
	char	szExtName[20];
	char	szPicName[50];
	char	szMD5[LEN_MD5];
	char	szPicPath[260];	//透传
}ST_MODELPIC, *pST_MODELPIC;

//模板图片下载请求


//模板图片发送
typedef struct tagModelPicSend
{
	int		nExamID;
	int		nSubjectID;
	int		nPicLen;
	char	szMD5[LEN_MD5];
	char	szFileName[LEN_NAME];				//文件名
}ST_SENDMODELPIC, *pST_SENDMODELPIC;

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


