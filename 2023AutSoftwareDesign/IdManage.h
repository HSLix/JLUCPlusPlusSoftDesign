#pragma once

#include <bitset>
#include <fstream>
#include <string>

#define maxIdNum 1000000
#define minIdNum 100000
// id范围是包括最小，不包最大的下标bitmap

class baseIdManage
{
public:
	baseIdManage() {}

	virtual ~baseIdManage()
	{
		delete IdBitmap;
	}

	// 删除所有qqId记录
	bool resetIdBitmap();

	// 查询qqId是否已注册
	bool isIdExist(std::string id);


	// 返回一个可用的QQId并将输入id位置设为1，如无符合条件的Id，则返回-1
	std::string returnUsableId();

	// 设置输入Id位置为1/0
	void setIdIndex(std::string QQId, int num);

protected:
	std::string fileName = "";
	std::bitset<maxIdNum>* IdBitmap;
	int latestId = -1;
};

class QQIdManage :public baseIdManage
{
public:
	QQIdManage();

};

class QQGIdManage : public baseIdManage
{
public:
	QQGIdManage();
};

