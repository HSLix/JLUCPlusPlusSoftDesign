#define _CRT_SECURE_NO_WARNINGS 1

#include <fstream>

#include "AccountGroupDataManage.h"


using namespace std;

// 读取数据并保存为map
bool QQDataManage::readFileSaveAsMap()
{
	bool result = false;
	
	
	return result;
}


// 靠Id获取用户
QQAccount QQDataManage::getAccountById(string Id)
{
	return this->QQAccountPointer->at(Id);
}


// 注册
bool QQDataManage::signupQQ(std::string Name, std::string Pwd)
{
	string tempStr = this->IdManage.returnUsableQQId();
	bool result = false;
	if (tempStr != "-1")
	{
		QQAccount* p = new QQAccount(tempStr);
		p->setName(Name);
		p->setId(tempStr);
		p->setPwd(Pwd);
		p->saveAccountAsFile();
		result = true;
	}
	
	return result;
}

