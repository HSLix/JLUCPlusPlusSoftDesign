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
		this->usingAccountPointer = nullptr;
	}

	// 若正用账号指针非空，则返回名字
	std::string getUsingAccountName()
	{
		if (usingAccountPointer != nullptr)
		{
			return usingAccountPointer->getName();
		}
	}

	// 若正用账号指针非空，则返回Id
	std::string getUsingAccountId()
	{
		if (usingAccountPointer != nullptr)
		{
			return usingAccountPointer->getId();
		}
	}



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

		this->QQAccountPointer = new std::map<std::string, QQAccount>;

		this->accountFileAddress = this->baseAddress + "Account/";
		this->groupFileAddress = this->baseAddress + "Group/";
	}



	// 靠Id获取用户
	QQAccount getAccountById(std::string Id);

	// 注册	
	bool signupQQ(std::string Name, std::string Pwd);

	// 清库
	void clearQQAccount();

	// 登录
	bool signinQQ(std::string Id, std::string Pwd);


	


private:
	// 用户数据地址
	std::string accountFileAddress;

	// 群数组地址
	std::string groupFileAddress;

	// 用户map
	std::map<std::string, QQAccount>* QQAccountPointer;

	// Id管理
	QQIdManage IdManage;

	
};


