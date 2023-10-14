#define _CRT_SECURE_NO_WARNINGS 1

#include <string>
#include "Program.h"



// 程序开始
void program::rootPage()
{
	this->schemePointer = new baseScheme();
	system("cls");
	// choice默认空为返回,-1为异常
	this->choice = this->schemePointer->startMenu();
	if (this->choice == "-1")
	{
		exit(1);
	}
	else if (this->choice == "")
	{
		exit(0);
	}
}


// 进入分支界面
void program::branchPage()
{
	/*
	* Interact::showStartMenu()
	cout << "欢迎使用本软件，请选择下列服务的序号输入：" << endl;
	cout << "1、QQ相关服务" << endl;
	cout << "2、微信相关服务" << endl;
	cout << "3、微博相关服务" << endl;
	cout << "4、退出" << endl;
	cout << "更多服务，敬请期待" << endl;
	*/
	system("cls");
	switch (stoi(this->choice))
	{
	case 1:
	{
		QQScheme tempScheme = QQScheme();
		this->schemePointer = &tempScheme;
		this->schemePointer->startMenu();
	}
	
		
	}
}

