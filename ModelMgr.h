#pragma once
#include <iostream>
#include <fstream>
#include "modelInfo.h"
#include "BasePocoHead.h"
#include "MyCodeConvert.h"

#define USES_FILE_ENC			//是否对文件使用加密

class CModelMgr
{
public:
	CModelMgr();
	~CModelMgr();

	pMODEL	LoadModelFile(std::string strModelPath);
	bool	SaveModelFile(pMODEL pModel);
	
	std::string GetLog();

	//模板文件夹存储路径，如：E:\myWorkspace\yklx\bin\release\Model\
	//设置基本信息
	void	SetBaseInfo(std::string strModelDirPath, std::string EncPwd);
private:
	bool	encString(std::string& strSrc, std::string& strDst);
	bool	decString(std::string& strSrc, std::string& strDst);
private:
	std::string _strLog;
	std::string _strEncPwd;
	std::string _strModelDirPath;	/*模板文件夹路径，如：E:\myWorkspace\yklx\bin\release\Model\*/
};

