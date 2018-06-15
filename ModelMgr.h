#pragma once
#include <iostream>
#include <fstream>
#include "modelInfo.h"
#include "BasePocoHead.h"
#include "MyCodeConvert.h"

#define USES_FILE_ENC			//�Ƿ���ļ�ʹ�ü���

class CModelMgr
{
public:
	CModelMgr();
	~CModelMgr();

	pMODEL	LoadModelFile(std::string strModelPath);
	bool	SaveModelFile(pMODEL pModel);
	
	std::string GetLog();

	//ģ���ļ��д洢·�����磺E:\myWorkspace\yklx\bin\release\Model\
	//���û�����Ϣ
	void	SetBaseInfo(std::string strModelDirPath, std::string EncPwd);
private:
	bool	encString(std::string& strSrc, std::string& strDst);
	bool	decString(std::string& strSrc, std::string& strDst);
private:
	std::string _strLog;
	std::string _strEncPwd;
	std::string _strModelDirPath;	/*ģ���ļ���·�����磺E:\myWorkspace\yklx\bin\release\Model\*/
};

