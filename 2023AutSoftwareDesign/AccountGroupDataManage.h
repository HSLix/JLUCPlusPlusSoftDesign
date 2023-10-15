#pragma once

#include <fstream>
#include <string>
#include <map>

#include "Account.h"
#include "IdManage.h"


class baseDataManage
{
public:
	baseDataManage()
	{
		this->baseAddress = "./";
	}


	// 若正用账号指针非空，则返回名字
	virtual std::string getUsingAccountName() = 0;
	

	// 若正用账号指针非空，则返回Id
	virtual std::string getUsingAccountId() = 0;

	// 若正用账号指针非空，则返回Pwd
	virtual std::string getUsingAccountPwd() = 0;
	

	// 若正用账号指针非空，则返回Birth
	virtual std::string getUsingAccountBirth() = 0;

	// 若正用账号指针非空，则返回Locate
	virtual std::string getUsingAccountLocate() = 0;

	// 若正用账号指针非空，则设置名字
	virtual void setUsingAccountName(std::string Name) = 0;


	// 若正用账号指针非空，则设置Id
	virtual void setUsingAccountId(std::string Id) = 0;


	// 若正用账号指针非空，则设置Birth
	virtual void setUsingAccountBirth(std::string Birth) = 0;

	// 若正用账号指针非空，则设置Locate
	virtual void setUsingAccountLocate(std::string Locate) = 0;

	// 若正用账号指针非空，则设置Pwd
	virtual void setUsingAccountPwd(std::string Pwd) = 0;
	


protected:
	// 所有数据储存在程序根目录
	std::string baseAddress;

};


class QQDataManage : public baseDataManage
{
public:
	QQDataManage()
	{
		// 修改数据保存文件夹为子文件夹
		this->baseAddress += "QQ/";

		this->accountFileAddress = this->baseAddress + "Account/";
		this->groupFileAddress = this->baseAddress + "Group/";
	}

	// 重新读取正使用用户的文件
	void updateUsingAccount();

	// 靠Id获取用户,若不存在，则返回nullptr
	QQAccount* getAccountById(std::string Id);

	// 靠Id获取群,若不存在，则返回nullptr
	QQGroup* getGroupById(std::string Id);

	// 注册	
	bool signupQQ(std::string Name, std::string Pwd);

	// QQ用户库清空
	void clearQQAccount();

	// QQ群库清空
	void clearQQGroup();

	// 登录
	bool signinQQ(std::string Id, std::string Pwd);

	// 遍历并输出好友列表
	void showAllFriend();

	// 遍历并输出群列表
	void showAllGroup();

	// 若正用账号指针非空，则返回Pwd
	std::string getUsingAccountPwd()
	{
		return this->usingAccountPointer->getPwd();
	}

	// 若正用账号指针非空，则设置Pwd
	void setUsingAccountPwd(std::string Pwd)
	{
		this->usingAccountPointer->setPwd(Pwd);
	}

	// 若正用账号指针非空，则返回名字
	std::string getUsingAccountName()
	{
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getName();
		}
		return "";
	}

	// 若正用账号指针非空，则返回Id
	std::string getUsingAccountId()
	{
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getId();
		}
		return "";
	}

	// 若正用账号指针非空，则返回Birth
	std::string getUsingAccountBirth() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getBirth();
		}
		return "";
	}

	// 若正用账号指针非空，则返回Locate
	std::string getUsingAccountLocate() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getLocate();
		}
		return "";
	}

	// 若正用账号指针非空，则返回bindWechatAccount
	std::string getUsingAccountBindWechatAccount() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getBindWechatAccountId();
		}
		return "";
	}

	// 若正用账号指针非空，则返回BindWeiboAccount
	std::string getUsingAccountBindWeiboAccount() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getBindWeiboAccountId();
		}
		return "";
	}

	// 若正用账号指针非空，则设置名字
	void setUsingAccountName(std::string Name)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setName(Name);
		}
	}


	// 若正用账号指针非空，则设置Id
	void setUsingAccountId(std::string Id)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setId(Id);
		}
	}


	// 若正用账号指针非空，则设置Birth
	void setUsingAccountBirth(std::string Birth)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setBirth(Birth);
		}
	}

	// 若正用账号指针非空，则设置Locate
	void setUsingAccountLocate(std::string Locate)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setLocate(Locate);
		}
	}

	// 若正用账号指针非空，则设置bindWechatAccount
	void setUsingAccountBindWechatAccount(std::string Id)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setBindWechatAccountId(Id);
		}
	}

	// 若正用账号指针非空，则设置bindWeiboAccount
	void setUsingAccountBindWeiboAccount(std::string Id)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setBindWeiboAccountId(Id);
		}
	}
	
	// 添加好友
	void addFriend(std::string Name, std::string Id);

	// 删除好友
	void delFriend(std::string Name, std::string Id);

	// 保存正使用用户数据
	void saveAccountData();

	// 设置某个用户Id注销
	void delAccountId(std::string Id);

	// 设置某个群Id注销
	void delGroupId(std::string Id);

	// 创建组
	void createGroup(std::string Name);

	// 退出群
	void exitGroup(std::string Id);

	// 加入群
	bool joinGroup(std::string Id);

private:
	// 用户数据地址
	std::string accountFileAddress;

	// 群数据地址
	std::string groupFileAddress;


	// QQ用户Id管理
	QQIdManage IdManage;

	// QQ群Id管理
	QQGIdManage GIdManage;

	// 正在使用的账号
	QQAccount* usingAccountPointer;

	// 用户等级
	int level = 1;
};



class WechatDataManage : public baseDataManage
{
public:
	WechatDataManage()
	{
		// 修改数据保存文件夹为子文件夹
		this->baseAddress += "Wechat/";

		this->accountFileAddress = this->baseAddress + "Account/";
		this->groupFileAddress = this->baseAddress + "Group/";
	}

	// 重新读取正使用用户的文件
	void updateUsingAccount();

	// 靠Id获取用户,若不存在，则返回nullptr
	WechatAccount* getAccountById(std::string Id);

	// 靠Id获取群,若不存在，则返回nullptr
	WechatGroup* getGroupById(std::string Id);

	// 注册	
	bool signupWechat(std::string Name, std::string Pwd);

	// Wechat用户库清空
	void clearWechatAccount();

	// Wechat群库清空
	void clearWechatGroup();

	// 登录
	bool signinWechat(std::string Id, std::string Pwd);

	// 遍历并输出好友列表
	void showAllFriend();

	// 遍历并输出群列表
	void showAllGroup();

	// 若正用账号指针非空，则返回Pwd
	std::string getUsingAccountPwd()
	{
		return this->usingAccountPointer->getPwd();
	}

	// 若正用账号指针非空，则设置Pwd
	void setUsingAccountPwd(std::string Pwd)
	{
		this->usingAccountPointer->setPwd(Pwd);
	}

	// 若正用账号指针非空，则返回名字
	std::string getUsingAccountName()
	{
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getName();
		}
		return "";
	}

	// 若正用账号指针非空，则返回Id
	std::string getUsingAccountId()
	{
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getId();
		}
		return "";
	}

	// 若正用账号指针非空，则返回Birth
	std::string getUsingAccountBirth() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getBirth();
		}
		return "";
	}

	// 若正用账号指针非空，则返回Locate
	std::string getUsingAccountLocate() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getLocate();
		}
		return "";
	}

	// 若正用账号指针非空，则返回bindQQAccount
	std::string getUsingAccountBindQQAccountId() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getBindQQAccountId();
		}
		return "";
	}

	// 若正用账号指针非空，则返回BindWeiboAccount
	std::string getUsingAccountBindWeiboAccountId() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getBindWeiboAccountId();
		}
		return "";
	}

	// 若正用账号指针非空，则设置名字
	void setUsingAccountName(std::string Name)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setName(Name);
		}
	}


	// 若正用账号指针非空，则设置Id
	void setUsingAccountId(std::string Id)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setId(Id);
		}
	}


	// 若正用账号指针非空，则设置Birth
	void setUsingAccountBirth(std::string Birth)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setBirth(Birth);
		}
	}

	// 若正用账号指针非空，则设置Locate
	void setUsingAccountLocate(std::string Locate)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setLocate(Locate);
		}
	}

	// 若正用账号指针非空，则设置bindQQAccount
	void setUsingAccountBindQQAccountId(std::string Id)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setBindQQAccountId(Id);
		}
	}

	// 若正用账号指针非空，则设置bindWeiboAccount
	void setUsingAccountBindWeiboAccountId(std::string Id)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setBindWeiboAccountId(Id);
		}
	}


	// 添加好友
	void addFriend(std::string Name, std::string Id);

	// 删除好友
	void delFriend(std::string Name, std::string Id);

	// 保存正使用用户数据
	void saveAccountData();

	// 设置某个用户Id注销
	void delAccountId(std::string Id);

	// 设置某个群Id注销
	void delGroupId(std::string Id);

	// 创建组
	void createGroup(std::string Name);

	// 退出群
	void exitGroup(std::string Id);

	// 加入群
	bool joinGroup(std::string Id);

private:
	// 用户数据地址
	std::string accountFileAddress;

	// 群数据地址
	std::string groupFileAddress;


	// Wechat用户Id管理
	WechatIdManage IdManage;

	// Wechat群Id管理
	WechatGIdManage GIdManage;

	// 正在使用的账号
	WechatAccount* usingAccountPointer;

	// 用户等级
	int level = 1;
};



class WeiboDataManage : public baseDataManage
{
public:
	WeiboDataManage()
	{
		// 修改数据保存文件夹为子文件夹
		this->baseAddress += "Weibo/";

		this->accountFileAddress = this->baseAddress + "Account/";
		this->groupFileAddress = this->baseAddress + "Group/";
	}

	// 重新读取正使用用户的文件
	void updateUsingAccount();

	// 靠Id获取用户,若不存在，则返回nullptr
	WeiboAccount* getAccountById(std::string Id);

	// 靠Id获取群,若不存在，则返回nullptr
	WeiboGroup* getGroupById(std::string Id);

	// 注册	
	bool signupWeibo(std::string Name, std::string Pwd, std::string newId);

	// Weibo用户库清空
	void clearWeiboAccount();

	// Weibo群库清空
	void clearWeiboGroup();

	// 登录
	bool signinWeibo(std::string Id, std::string Pwd);

	// 遍历并输出好友列表
	void showAllFriend();

	// 遍历并输出群列表
	void showAllGroup();

	// 若正用账号指针非空，则返回Pwd
	std::string getUsingAccountPwd()
	{
		return this->usingAccountPointer->getPwd();
	}

	// 若正用账号指针非空，则设置Pwd
	void setUsingAccountPwd(std::string Pwd)
	{
		this->usingAccountPointer->setPwd(Pwd);
	}

	// 若正用账号指针非空，则返回名字
	std::string getUsingAccountName()
	{
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getName();
		}
		return "";
	}

	// 若正用账号指针非空，则返回Id
	std::string getUsingAccountId()
	{
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getId();
		}
		return "";
	}

	// 若正用账号指针非空，则返回Birth
	std::string getUsingAccountBirth() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getBirth();
		}
		return "";
	}

	// 若正用账号指针非空，则返回Locate
	std::string getUsingAccountLocate() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getLocate();
		}
		return "";
	}

	// 若正用账号指针非空，则返回bindWechatAccount
	std::string getUsingAccountBindWechatAccountId() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getBindWechatAccountId();
		}
		return "";
	}

	// 若正用账号指针非空，则返回BindQQAccount
	std::string getUsingAccountBindQQAccountId() {
		if (this->usingAccountPointer != nullptr)
		{
			return this->usingAccountPointer->getBindQQAccountId();
		}
		return "";
	}


	// 若正用账号指针非空，则设置名字
	void setUsingAccountName(std::string Name)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setName(Name);
		}
	}


	// 若正用账号指针非空，则设置Id
	void setUsingAccountId(std::string Id)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setId(Id);
		}
	}


	// 若正用账号指针非空，则设置Birth
	void setUsingAccountBirth(std::string Birth)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setBirth(Birth);
		}
	}

	// 若正用账号指针非空，则设置Locate
	void setUsingAccountLocate(std::string Locate)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setLocate(Locate);
		}
	}

	// 若正用账号指针非空，则设置bindWechatAccount
	void setUsingAccountBindWechatAccountId(std::string Id)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setBindWechatAccountId(Id);
		}
	}

	// 若正用账号指针非空，则设置bindQQAccount
	void setUsingAccountBindQQAccountId(std::string Id)
	{
		if (this->usingAccountPointer != nullptr)
		{
			this->usingAccountPointer->setBindQQAccountId(Id);
		}
	}


	// 添加好友
	void addFriend(std::string Name, std::string Id);

	// 删除好友
	void delFriend(std::string Name, std::string Id);

	// 保存正使用用户数据
	void saveAccountData();

	// 设置某个用户Id注销
	void delAccountId(std::string Id);

	// 设置某个群Id注销
	void delGroupId(std::string Id);

	// 创建组
	void createGroup(std::string Name);

	// 退出群
	void exitGroup(std::string Id);

	// 加入群
	bool joinGroup(std::string Id);

private:
	// 用户数据地址
	std::string accountFileAddress;

	// 群数据地址
	std::string groupFileAddress;


	// Weibo用户Id管理
	WeiboIdManage IdManage;

	// Weibo群Id管理
	WeiboGIdManage GIdManage;

	// 正在使用的账号
	WeiboAccount* usingAccountPointer;

	// 用户等级
	int level = 1;
};


