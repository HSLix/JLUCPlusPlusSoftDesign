#define _CRT_SECURE_NO_WARNINGS 1

#include <fstream>

#include "AccountGroupDataManage.h"


using namespace std;




// 靠Id获取用户
QQAccount* QQDataManage::getAccountById(string Id)
{
	QQAccount* tempPointer = nullptr;

	if (this->IdManage.isIdExist(Id))
	{
		tempPointer = new QQAccount(Id);
	}
	
	return tempPointer;
}

// 靠Id获取群,若不存在，则返回nullptr
QQGroup* QQDataManage::getGroupById(std::string Id)
{
	QQGroup* tempPointer = nullptr;

	if (this->GIdManage.isIdExist(Id))
	{
		tempPointer = new QQGroup(Id);
	}

	return tempPointer;
}

// 注册
bool QQDataManage::signupQQ(std::string Name, std::string Pwd)
{
	string newId = this->IdManage.returnUsableId();
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
	this->IdManage.resetIdBitmap();
}

// QQ群库清空
void QQDataManage::clearQQGroup()
{
	this->GIdManage.resetIdBitmap();
}

// 设置某个Id注销
void QQDataManage::delAccountId(std::string Id)
{
	this->IdManage.setIdIndex(Id, 0);
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
	this->usingAccountPointer->saveAccountAsFile();
}


// 删除好友
void QQDataManage::delFriend(std::string Name = "", std::string Id = "")
{
	this->usingAccountPointer->delFriendById(Id);
	this->usingAccountPointer->saveAccountAsFile();
}

// 创建群
void QQDataManage::createGroup(std::string Name)
{
	string Id = this->GIdManage.returnUsableId();
	QQGroup tempGroup(Id);
	tempGroup.createOrResetFile(Id);
	tempGroup.setName(Name);
	tempGroup.setId(Id);
	tempGroup.addMemberToList(this->usingAccountPointer->getName(), this->usingAccountPointer->getId());
	this->usingAccountPointer->joinGroupToList(Name, Id);
	this->usingAccountPointer->saveAccountAsFile();
	tempGroup.saveGroupAsFile();
}

// 退出群
void QQDataManage::exitGroup(std::string Id)
{
	QQGroup tempGroup(Id);
	tempGroup.readGroupFromFile();
	tempGroup.delMemberById(this->usingAccountPointer->getId());
	this->usingAccountPointer->delJoinedGroupById(Id);
	this->usingAccountPointer->saveAccountAsFile();
	tempGroup.saveGroupAsFile();
}

// 遍历并输出群列表
void QQDataManage::showAllGroup()
{
	cout << "--------------------------------------------------------------" << endl;
	this->usingAccountPointer->showJoinedGroupList();
	cout << "以上为所有加入的群\n" << endl;
}

// 加入群
bool QQDataManage::joinGroup(std::string Id)
{
	bool result = true;
	QQGroup tempGroup(Id);
	tempGroup.readGroupFromFile();
	tempGroup.addMemberToList(this->usingAccountPointer->getName(), this->usingAccountPointer->getId());
	this->usingAccountPointer->joinGroupToList(tempGroup.getName(), Id);
	this->usingAccountPointer->saveAccountAsFile();
	tempGroup.saveGroupAsFile();
	return result;
}

// 设置某个群Id注销
void QQDataManage::delGroupId(std::string Id)
{
	this->GIdManage.setIdIndex(Id, 0);
}


// 重新读取正使用用户的文件
void QQDataManage::updateUsingAccount()
{
	this->usingAccountPointer->readAccountFromFile();
}





// 靠Id获取用户
WechatAccount* WechatDataManage::getAccountById(string Id)
{
	WechatAccount* tempPointer = nullptr;

	if (this->IdManage.isIdExist(Id))
	{
		tempPointer = new WechatAccount(Id);
	}

	return tempPointer;
}

// 靠Id获取群,若不存在，则返回nullptr
WechatGroup* WechatDataManage::getGroupById(std::string Id)
{
	WechatGroup* tempPointer = nullptr;

	if (this->GIdManage.isIdExist(Id))
	{
		tempPointer = new WechatGroup(Id);
	}

	return tempPointer;
}

// 注册
bool WechatDataManage::signupWechat(std::string Name, std::string Pwd)
{
	string newId = this->IdManage.returnUsableId();
	bool result = false;
	if (newId != "-1")
	{
		WechatAccount::createOrResetFile(newId);
		//WechatAccount tempAccount(newId);
		this->usingAccountPointer = new WechatAccount(newId);

		usingAccountPointer->setName(Name);
		usingAccountPointer->setId(newId);
		usingAccountPointer->setPwd(Pwd);
		usingAccountPointer->saveAccountAsFile();

		result = true;
	}

	return result;
}

// 登录,包装验证密码与设置当前正使用账号为该账号
bool WechatDataManage::signinWechat(std::string Id, std::string Pwd)
{
	bool result = false;
	if (this->getAccountById(Id) != nullptr)
	{
		WechatAccount* tempAccountPointer = this->getAccountById(Id);
		tempAccountPointer->readAccountFromFile();
		result = tempAccountPointer->checkPwd(Pwd);

		if (result == true)
		{
			this->usingAccountPointer = tempAccountPointer;
		}
	}


	return result;

}


//清空Wechat用户库
void WechatDataManage::clearWechatAccount()
{
	this->IdManage.resetIdBitmap();
}

// Wechat群库清空
void WechatDataManage::clearWechatGroup()
{
	this->GIdManage.resetIdBitmap();
}

// 设置某个Id注销
void WechatDataManage::delAccountId(std::string Id)
{
	this->IdManage.setIdIndex(Id, 0);
}

// 保存正使用用户数据
void WechatDataManage::saveAccountData()
{
	this->usingAccountPointer->saveAccountAsFile();
}

// 遍历并输出好友列表
void WechatDataManage::showAllFriend()
{
	cout << "--------------------------------------------------------------" << endl;
	this->usingAccountPointer->showFriendList();
	cout << "以上为所有好友\n" << endl;
}


// 添加好友
void WechatDataManage::addFriend(std::string Name, std::string Id)
{
	this->usingAccountPointer->addFriendToList(Name, Id);
	this->usingAccountPointer->saveAccountAsFile();
}


// 删除好友
void WechatDataManage::delFriend(std::string Name = "", std::string Id = "")
{
	this->usingAccountPointer->delFriendById(Id);
	this->usingAccountPointer->saveAccountAsFile();
}

// 创建群
void WechatDataManage::createGroup(std::string Name)
{
	string Id = this->GIdManage.returnUsableId();
	WechatGroup tempGroup(Id);
	tempGroup.createOrResetFile(Id);
	tempGroup.setName(Name);
	tempGroup.setId(Id);
	tempGroup.addMemberToList(this->usingAccountPointer->getName(), this->usingAccountPointer->getId());
	this->usingAccountPointer->joinGroupToList(Name, Id);
	this->usingAccountPointer->saveAccountAsFile();
	tempGroup.saveGroupAsFile();
}

// 退出群
void WechatDataManage::exitGroup(std::string Id)
{
	WechatGroup tempGroup(Id);
	tempGroup.readGroupFromFile();
	tempGroup.delMemberById(this->usingAccountPointer->getId());
	this->usingAccountPointer->delJoinedGroupById(Id);
	this->usingAccountPointer->saveAccountAsFile();
	tempGroup.saveGroupAsFile();
}

// 遍历并输出群列表
void WechatDataManage::showAllGroup()
{
	cout << "--------------------------------------------------------------" << endl;
	this->usingAccountPointer->showJoinedGroupList();
	cout << "以上为所有加入的群\n" << endl;
}

// 加入群
bool WechatDataManage::joinGroup(std::string Id)
{
	bool result = true;
	WechatGroup tempGroup(Id);
	tempGroup.readGroupFromFile();
	tempGroup.addMemberToList(this->usingAccountPointer->getName(), this->usingAccountPointer->getId());
	this->usingAccountPointer->joinGroupToList(tempGroup.getName(), Id);
	this->usingAccountPointer->saveAccountAsFile();
	tempGroup.saveGroupAsFile();
	return result;
}

// 设置某个群Id注销
void WechatDataManage::delGroupId(std::string Id)
{
	this->GIdManage.setIdIndex(Id, 0);
}


// 重新读取正使用用户的文件
void WechatDataManage::updateUsingAccount()
{
	this->usingAccountPointer->readAccountFromFile();
}



// 靠Id获取用户
WeiboAccount* WeiboDataManage::getAccountById(string Id)
{
	WeiboAccount* tempPointer = nullptr;

	if (this->IdManage.isIdExist(Id))
	{
		tempPointer = new WeiboAccount(Id);
	}

	return tempPointer;
}

// 靠Id获取群,若不存在，则返回nullptr
WeiboGroup* WeiboDataManage::getGroupById(std::string Id)
{
	WeiboGroup* tempPointer = nullptr;

	if (this->GIdManage.isIdExist(Id))
	{
		tempPointer = new WeiboGroup(Id);
	}

	return tempPointer;
}

// 注册
bool WeiboDataManage::signupWeibo(std::string Name, std::string Pwd, std::string newId)
{
	//string newId = this->IdManage.returnUsableId();
	bool result = false;
	if (newId != "-1")
	{
		WeiboAccount::createOrResetFile(newId);
		//WeiboAccount tempAccount(newId);
		this->IdManage.setIdIndex(newId, 1);
		this->usingAccountPointer = new WeiboAccount(newId);

		usingAccountPointer->setName(Name);
		usingAccountPointer->setId(newId);
		usingAccountPointer->setPwd(Pwd);
		usingAccountPointer->saveAccountAsFile();

		result = true;
	}

	return result;
}

// 登录,包装验证密码与设置当前正使用账号为该账号
bool WeiboDataManage::signinWeibo(std::string Id, std::string Pwd)
{
	bool result = false;
	if (this->getAccountById(Id) != nullptr)
	{
		WeiboAccount* tempAccountPointer = this->getAccountById(Id);
		tempAccountPointer->readAccountFromFile();
		result = tempAccountPointer->checkPwd(Pwd);

		if (result == true)
		{
			this->usingAccountPointer = tempAccountPointer;
		}
	}


	return result;

}


//清空Weibo用户库
void WeiboDataManage::clearWeiboAccount()
{
	this->IdManage.resetIdBitmap();
}

// Weibo群库清空
void WeiboDataManage::clearWeiboGroup()
{
	this->GIdManage.resetIdBitmap();
}

// 设置某个Id注销
void WeiboDataManage::delAccountId(std::string Id)
{
	this->IdManage.setIdIndex(Id, 0);
}

// 保存正使用用户数据
void WeiboDataManage::saveAccountData()
{
	this->usingAccountPointer->saveAccountAsFile();
}

// 遍历并输出好友列表
void WeiboDataManage::showAllFriend()
{
	cout << "--------------------------------------------------------------" << endl;
	this->usingAccountPointer->showFriendList();
	cout << "以上为所有好友\n" << endl;
}


// 添加好友
void WeiboDataManage::addFriend(std::string Name, std::string Id)
{
	this->usingAccountPointer->addFriendToList(Name, Id);
	this->usingAccountPointer->saveAccountAsFile();
}


// 删除好友
void WeiboDataManage::delFriend(std::string Name = "", std::string Id = "")
{
	this->usingAccountPointer->delFriendById(Id);
	this->usingAccountPointer->saveAccountAsFile();
}

// 创建群
void WeiboDataManage::createGroup(std::string Name)
{
	string Id = this->GIdManage.returnUsableId();
	WeiboGroup tempGroup(Id);
	tempGroup.createOrResetFile(Id);
	tempGroup.setName(Name);
	tempGroup.setId(Id);
	tempGroup.addMemberToList(this->usingAccountPointer->getName(), this->usingAccountPointer->getId());
	this->usingAccountPointer->joinGroupToList(Name, Id);
	this->usingAccountPointer->saveAccountAsFile();
	tempGroup.saveGroupAsFile();
}

// 退出群
void WeiboDataManage::exitGroup(std::string Id)
{
	WeiboGroup tempGroup(Id);
	tempGroup.readGroupFromFile();
	tempGroup.delMemberById(this->usingAccountPointer->getId());
	this->usingAccountPointer->delJoinedGroupById(Id);
	this->usingAccountPointer->saveAccountAsFile();
	tempGroup.saveGroupAsFile();
}

// 遍历并输出群列表
void WeiboDataManage::showAllGroup()
{
	cout << "--------------------------------------------------------------" << endl;
	this->usingAccountPointer->showJoinedGroupList();
	cout << "以上为所有加入的群\n" << endl;
}

// 加入群
bool WeiboDataManage::joinGroup(std::string Id)
{
	bool result = true;
	WeiboGroup tempGroup(Id);
	tempGroup.readGroupFromFile();
	tempGroup.addMemberToList(this->usingAccountPointer->getName(), this->usingAccountPointer->getId());
	this->usingAccountPointer->joinGroupToList(tempGroup.getName(), Id);
	this->usingAccountPointer->saveAccountAsFile();
	tempGroup.saveGroupAsFile();
	return result;
}

// 设置某个群Id注销
void WeiboDataManage::delGroupId(std::string Id)
{
	this->GIdManage.setIdIndex(Id, 0);
}


// 重新读取正使用用户的文件
void WeiboDataManage::updateUsingAccount()
{
	this->usingAccountPointer->readAccountFromFile();
}


