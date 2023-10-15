#pragma once

#include <iostream>
#include "Interact.h"

// 基础事件流程
class baseScheme
{
public:
	baseScheme()
	{
		// 清除置空
		if (this->menuPointer != nullptr)
		{
			delete this->menuPointer;
			this->menuPointer = nullptr;
		}
		this->menuPointer = new Interact();
	}


	
	// 起始界面
	virtual std::string startMenu();

	// 主动设置互动指针为空
	void setMenuPointerNull()
	{
		if (this->menuPointer != nullptr)
		{
			delete this->menuPointer;
			this->menuPointer = nullptr;
		}
	}

protected:
	Interact* menuPointer;
};


// QQ事件流程
class QQScheme : public baseScheme
{
public:
	QQScheme()
	{
		// 清除置空
		if (this->menuPointer != nullptr)
		{
			delete this->menuPointer;
			this->menuPointer = nullptr;
		}
		this->menuPointer = &interact;
	}

	// QQ起始界面
	std::string startMenu();

private:
	QQInteract interact;
};

// Wechat事件流程
class WechatScheme : public baseScheme
{
public:
	WechatScheme()
	{
		// 清除置空
		if (this->menuPointer != nullptr)
		{
			delete this->menuPointer;
			this->menuPointer = nullptr;
		}
		this->menuPointer = &interact;
	}

	// Wechat起始界面
	std::string startMenu();

private:
	WechatInteract interact;
};

// Weibo事件流程
class WeiboScheme : public baseScheme
{
public:
	WeiboScheme()
	{
		// 清除置空
		if (this->menuPointer != nullptr)
		{
			delete this->menuPointer;
			this->menuPointer = nullptr;
		}
		this->menuPointer = &interact;
	}

	// Weibo起始界面
	std::string startMenu();

private:
	WeiboInteract interact;
};

