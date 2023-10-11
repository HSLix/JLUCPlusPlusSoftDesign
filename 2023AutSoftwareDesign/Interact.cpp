#define _CRT_SECURE_NO_WARNINGS 1


#include <iostream>
#include <conio.h>

#include "Interact.h"


using namespace std;

// 这是起始菜单
void Interact::showStartMenu()
{
	cout << "欢迎使用本软件，请选择下列服务的序号输入：" << endl;
	cout << "1、QQ相关服务" << endl;
	cout << "2、微信相关服务" << endl;
	cout << "3、微博相关服务" << endl;
	cout << "4、退出" << endl;
	cout << "更多服务，敬请期待" << endl;
}

// 输入检测与限制
// 纯数字
string Interact::inputAllInt(int maxNum)
{
    string result = "";
    int inputWord;
    if (maxNum > 0)
    {
        inputWord = _getch();
        while (inputWord != 13 || result.empty())
        {
            if (inputWord == 8 && !result.empty())
            {
                result.pop_back();
                cout << "\b";
            }
            if (inputWord >= 48 && inputWord <= 57 && result.size() < maxNum)
            {
                result += (char)inputWord;
            }
            cout << "\r                                                                                                    ";
            cout << "\r" + result;
        
            inputWord = _getch();
        }
    }
    

    cout << "\n" << result << endl;
    return result;
}

// 数字与英文字母
string Interact::inputEWordAndInt(int maxNum)
{
    string result = "";
    int inputWord;
    if (maxNum > 0)
    {
        inputWord = _getch();
        while (inputWord != 13 || result.empty())
        {
            if (inputWord == 8 && !result.empty())
            {
                result.pop_back();
                cout << "\b";
            }
            if (((inputWord >= 48 && inputWord <= 57)
                ||(inputWord >= 97 && inputWord <= 122)
                ||(inputWord >= 65 && inputWord <= 90))
                && result.size() < maxNum)
            {
                result += (char)inputWord;
            }
            cout << "\r                                                                                                    ";
            cout << "\r" + result;

            inputWord = _getch();
        }
    }
    

    cout << "\n" << result << endl;
    return result;
}

// 所有字符
string Interact::inputNormal()
{
    string result = "";
    cin >> result;
    // _getch();
    return result;
}

// 这是注册界面
void QQInteract::showSignUpPage()
{

}

// 这是登录界面
void QQInteract::showSignInPage()
{

}

// 这是QQ登录后的界面
void QQInteract::showMainMenu()
{

}
