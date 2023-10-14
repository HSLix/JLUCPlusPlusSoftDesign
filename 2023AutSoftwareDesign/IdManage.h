#pragma once

#include <bitset>
#include <fstream>
#include <string>

#define maxIdNum 1000000
#define minIdNum 100000
// id范围是包括最小，不包最大的下标bitmap


class QQIdManage
{
public:
	QQIdManage();

	~QQIdManage()
	{
		delete QQIdBitmap;
	}

	// 删除所有qqId记录
	bool resetQQIdBitmap();

	// 查询qqId是否已注册
	bool isQQIdExist(std::string id);


	// 返回一个可用的QQId并将输入id位置设为1，如无符合条件的Id，则返回-1
	std::string returnUsableQQId();

	// 设置输入Id位置为1/0
	void setQQIdIndex(std::string QQId, int num);

private:
	std::string fileName;
	std::bitset<maxIdNum>* QQIdBitmap;
	int latestId;
	
};



// 重置QQ群Id
bool resetQQGroupIdBitmap();

// 查询qq群Id是否已注册
bool isQQGroupIdExist(std::string QQId);
