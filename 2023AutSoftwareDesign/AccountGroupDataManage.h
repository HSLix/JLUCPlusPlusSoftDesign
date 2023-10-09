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

	// 读取数据并保存为map
	virtual bool readFileSaveAsMap() = 0;



protected:
	std::string baseAddress;
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

	// 读取数据并保存为map
	bool readFileSaveAsMap();

	// 靠Id获取用户
	QQAccount getAccountById(std::string Id);

	// 注册	
	bool signupQQ(std::string Name, std::string Pwd);


	


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


