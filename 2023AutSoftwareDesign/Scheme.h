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

	// QQ登录界面
	// void signInMenu();

	// QQ注册界面
	// void signUpMenu();

	// QQ注销界面
	// void logOffMenu();

private:
	QQInteract interact;
};

