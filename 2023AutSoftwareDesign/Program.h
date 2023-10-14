#pragma once

#include <iostream>
#include "Scheme.h"


class program
{
public:
	program()
	{
		this-> schemePointer = new baseScheme();
	}


	~program()
	{
		if (this->schemePointer != nullptr)
		{
			delete this->schemePointer;
		}
			
	}

	// 程序开始
	void rootPage();

	// 进入分支界面
	void branchPage();

protected:
	baseScheme* schemePointer;
	// 根据这个选择切换事件流程
	std::string choice;

	
	
};



