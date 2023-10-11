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
	QQAccount* tempPointer = new QQAccount(Id);
	return *tempPointer;
}


// 注册
bool QQDataManage::signupQQ(std::string Name, std::string Pwd)
{
	string newId = this->IdManage.returnUsableQQId();
	bool result = false;
	if (newId != "-1")
	{
		QQAccount::createOrResetFile(newId);
		QQAccount* p = new QQAccount(newId);
		p->setName(Name);
		p->setId(newId);
		p->setPwd(Pwd);
		p->saveAccountAsFile();
		result = true;
	}
	
	return result;
}

// 登录,包装验证密码与设置当前正使用账号为该账号
bool QQDataManage::signinQQ(std::string Id, std::string Pwd)
{
	bool result = false;
	QQAccount *tempAccountPointer = new QQAccount(Id);
	result = tempAccountPointer->checkPwd(Pwd);

	if (result == true)
	{
		this->usingAccountPointer = tempAccountPointer;
	}

	return result;

}


//清空QQ用户库
void QQDataManage::clearQQAccount()
{
	this->IdManage.resetQQIdBitmap();
}
