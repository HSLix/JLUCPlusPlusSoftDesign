#define _CRT_SECURE_NO_WARNINGS 1


#include <iostream>
#include <string>

#include "Scheme.h"


using namespace std;


// 程序的第一个界面展示与处理
std::string baseScheme::startMenu()
{
    string choice;
    bool exitFlag = false;
    

    while (!exitFlag)
    {
        exitFlag = true;
        choice = (this->menuPointer)->showStartMenu();

        // 清除上一循环可能残留的界面对象
        if (this->menuPointer != nullptr)
        {
            delete this->menuPointer;
            this->menuPointer = nullptr;
        }

        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
        {
            break;
        }
        case 2:
            break;
        case 3:
            break;
        case 4:
            choice = "";
            break;
        default:
            exitFlag = false;
            cout << "baseScheme::startMenu()发生选择溢值错误" << endl;
            choice = "-1";
            std::system("pause");
        }
    }

    return choice;
}


// QQ起始界面
std::string QQScheme::startMenu()
{
    string choice;
    bool exitFlag = false;
    /*
    * showStartMenu()
    cout << "您已选择QQ相关服务，可选择下列服务的序号输入：" << endl;
    cout << "1、登录QQ" << endl;
    cout << "2、注册QQ" << endl;
    cout << "3、注销QQ" << endl;
    cout << "4、返回" << endl;
    cout << "更多服务，敬请期待" << endl;
    */
    while (!exitFlag)
    {
        if (choice == "")
        {
            choice = this->menuPointer->showStartMenu();
        }
            


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            choice = this->menuPointer->showSignInPage();
            break;
        case 2:
            choice = this->menuPointer->showSignUpPage();
            break;
        case 3:
            choice = this->menuPointer->showLogOffMenu();
            break;
        case 4:
            choice = "";
            exitFlag = true;
            break;
        case 5:
            choice = this->menuPointer->showAfterSignInMenu();
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
        
    }

    return choice;
}




