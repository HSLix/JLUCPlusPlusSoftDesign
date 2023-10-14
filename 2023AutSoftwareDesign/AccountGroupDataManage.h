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

	// 退出登录，即正用号指针置空
	void setUsingAccountNULL()
	{
		if (this->usingAccountPointer != nullptr)
		{
			delete this->usingAccountPointer;
			this->usingAccountPointer = nullptr;
		}
	}

	// 若正用账号指针非空，则返回名字
	virtual std::string getUsingAccountName() { return ""; }
	

	// 若正用账号指针非空，则返回Id
	virtual std::string getUsingAccountId() { return ""; }
	



protected:
	// 所有数据储存在程序根目录
	std::string baseAddress;

	// 正在使用的账号
	baseAccount * usingAccountPointer = nullptr;
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



	// 靠Id获取用户,若不存在，则返回nullptr
	QQAccount* getAccountById(std::string Id);

	// 注册	
	bool signupQQ(std::string Name, std::string Pwd);

	// 清库
	void clearQQAccount();

	// 登录
	bool signinQQ(std::string Id, std::string Pwd);

	// 遍历并输出好友列表
	void showAllFriend();

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
	
	// 添加好友
	void addFriend(std::string Name, std::string Id);

	// 删除好友
	void delFriend(std::string Name, std::string Id);

	// 保存正使用用户数据
	void saveAccountData();

	// 设置某个Id注销
	void delId(std::string Id);


private:
	// 用户数据地址
	std::string accountFileAddress;

	// 群数组地址
	std::string groupFileAddress;

	// 用户map
	// std::map<std::string, QQAccount>* QQAccountPointer;

	// Id管理
	QQIdManage IdManage;

	// 正在使用的账号
	QQAccount* usingAccountPointer;
};


