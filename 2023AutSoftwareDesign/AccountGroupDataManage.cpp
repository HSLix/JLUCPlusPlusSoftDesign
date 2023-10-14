#define _CRT_SECURE_NO_WARNINGS 1

#include <fstream>

#include "AccountGroupDataManage.h"


using namespace std;




// 靠Id获取用户
QQAccount* QQDataManage::getAccountById(string Id)
{
	QQAccount* tempPointer = nullptr;

	if (this->IdManage.isQQIdExist(Id))
	{
		tempPointer = new QQAccount(Id);
	}
	
	return tempPointer;
}


// 注册
bool QQDataManage::signupQQ(std::string Name, std::string Pwd)
{
	string newId = this->IdManage.returnUsableQQId();
	bool result = false;
	if (newId != "-1")
	{
		QQAccount::createOrResetFile(newId);
		//QQAccount tempAccount(newId);
		this->usingAccountPointer = new QQAccount(newId);

		usingAccountPointer->setName(Name);
		usingAccountPointer->setId(newId);
		usingAccountPointer->setPwd(Pwd);
		usingAccountPointer->saveAccountAsFile();

		result = true;
	}
	
	return result;
}

// 登录,包装验证密码与设置当前正使用账号为该账号
bool QQDataManage::signinQQ(std::string Id, std::string Pwd)
{
	bool result = false;
	if (this->getAccountById(Id) != nullptr)
	{
		QQAccount *tempAccountPointer = this->getAccountById(Id);
		tempAccountPointer->readAccountFromFile();
		result = tempAccountPointer->checkPwd(Pwd);

		if (result == true)
		{
			this->usingAccountPointer = tempAccountPointer;
		}
	}
	

	return result;

}


//清空QQ用户库
void QQDataManage::clearQQAccount()
{
	this->IdManage.resetQQIdBitmap();
}

// 设置某个Id注销
void QQDataManage::delId(std::string Id)
{
	this->IdManage.setQQIdIndex(Id, 0);
}

// 保存正使用用户数据
void QQDataManage::saveAccountData()
{
	this->usingAccountPointer->saveAccountAsFile();
}

// 遍历并输出好友列表
void QQDataManage::showAllFriend()
{
	cout << "--------------------------------------------------------------" << endl;
	this->usingAccountPointer->showFriendList();
	cout << "以上为所有好友\n" << endl;
}


// 添加好友
void QQDataManage::addFriend(std::string Name, std::string Id)
{
	this->usingAccountPointer->addFriendToList(Name, Id);
}


// 删除好友
void QQDataManage::delFriend(std::string Name = "", std::string Id = "")
{
	this->usingAccountPointer->delFriendById(Id);
	this->usingAccountPointer->delFriendById(Id);
}
