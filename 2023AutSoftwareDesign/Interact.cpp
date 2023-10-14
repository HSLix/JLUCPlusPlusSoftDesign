#define _CRT_SECURE_NO_WARNINGS 1


#include <iostream>
#include <conio.h>

#include "Interact.h"



using namespace std;

// 这是起始菜单
string Interact::showStartMenu()
{
    cout << "--------------------------------------------------------------" << endl;
    cout << "欢迎使用本软件，请选择下列服务的序号输入：" << endl;
	cout << "1、QQ相关服务" << endl;
	cout << "2、微信相关服务" << endl;
	cout << "3、微博相关服务" << endl;
	cout << "4、退出" << endl;
	cout << "更多服务，敬请期待" << endl;
    return Interact::inputAllInt(1, 1, 4);
}

// 输入检测与限制
// 纯数字
string Interact::inputAllInt(int maxLen, int minNum, int maxNum)
{
    string result = "";
    int inputWord;
    if (maxLen > 0)
    {
        inputWord = _getch();
        while (inputWord != 13 || result.empty())
        {
            if (inputWord == 8 && !result.empty())
            {
                result.pop_back();
                cout << "\b";
            }
            if (inputWord >= (minNum + 48) && inputWord <= (maxNum + 48) && result.size() < maxLen)
            {
                result += (char)inputWord;
            }
            cout << "\r                                                                                                    ";
            cout << "\r" + result;
        
            inputWord = _getch();
        }
    }
    

    cout << endl;
    return result;
}

// 数字与英文字母
string Interact::inputEWordAndInt(int maxLen, bool pwdSwitch)
{
    string result = "";
    string pwdResult = "";
    int inputWord;
    if (maxLen > 0)
    {
        inputWord = _getch();
        while (inputWord != 13 || result.empty())
        {
            if (inputWord == 8 && !result.empty())
            {
                result.pop_back();
                pwdResult.pop_back();
                cout << "\b";
            }
            if (((inputWord >= 48 && inputWord <= 57)
                ||(inputWord >= 97 && inputWord <= 122)
                ||(inputWord >= 65 && inputWord <= 90))
                && result.size() < maxLen)
            {
                result += (char)inputWord;
                pwdResult += "*";
            }
            cout << "\r                                                                                                    ";
            if (pwdSwitch)
            {
                cout << "\r" + pwdResult;
            }
            else
            {
                cout << "\r" + result;
            }
            

            inputWord = _getch();
        }
    }
    

    cout << endl;
    return result;
}

// 所有字符
/*
string Interact::inputNormal()
{
    string result;
    wstring s;
    wcin >> s;
    wcout << s << endl;
    cin >> result;
    cout << result << endl;

    return result;
}
*/

//任意键继续然后清屏
void Interact::pauseAndClearScreen()
{
    std::system("pause");
    std::system("cls");
}


// 这是QQ开始界面
string QQInteract::showStartMenu()
{
    cout << "--------------------------------------------------------------" << endl;
    string text = "您已选择QQ相关服务，可选择下列服务的序号输入：\n1、登录QQ\n2、注册QQ\n3、注销QQ\n4、返回\n更多服务，敬请期待";
    cout << text << endl;
    return Interact::inputAllInt(1, 1, 4);
}

// 这是QQ注册界面
string QQInteract::showSignUpPage()
{
    string signUpName;
    string signUpPwd;
    bool result;
    bool exitFlag = false;

    while (!exitFlag)
    {
        cout << "--------------------------------------------------------------" << endl;
        cout << "请输入用户名:" << endl;
        signUpName = Interact::inputEWordAndInt(10);
        cout << "请输入密码:" << endl;
        signUpPwd = Interact::inputEWordAndInt(10);

        result = this->QQDataM.signupQQ(signUpName, signUpPwd);

        if (result)
        {
            cout << "注册成功！\n" << "您的Id是：" << this->QQDataM.getUsingAccountId() << " 正在进入登陆界面\n" << endl;
            exitFlag = true;
            cout << "请输入生日:" << endl;
            this->QQDataM.setBirth(this->Interact::inputAllInt(8));
            cout << "请输入地址：" << endl;
            this->QQDataM.setLocate(this->Interact::inputEWordAndInt(20));
            this->QQDataM.saveAccountData();
        }
        else
        {
            cout << "注册失败，请重试" << endl;
        }
    }
    this->QQDataM.setUsingAccountNULL();
    return "1";
}


// 这是注销QQ账户的界面
string QQInteract::showLogOffMenu()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想注销账号的Id：" << endl;
    Id = Interact::inputAllInt(6);
    QQAccount* tempPointer = this->QQDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else
    {
        cout << "目标用户信息为：" << endl;
        cout << "昵称：" << tempPointer->getName() << endl;
        cout << "是否注销？（1为是，0为否）" << endl;
        string isAdd = Interact::inputAllInt(1, 0, 1);
        if (isAdd == "1")
        {
            this->QQDataM.delAccountId(tempPointer->getId());
            QQAccount::createOrResetFile(tempPointer->getId());
            cout << "注销成功！" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }


    return result;
}


// 这是QQ登录界面
string QQInteract::showSignInPage()
{
    string signInId;
    string signInPwd;
    bool signUpResult;
    string result = "";
    bool exitFlag = false;
    int failTime = 3;
    
    while (!exitFlag)
    {
        cout << "--------------------------------------------------------------" << endl;
        cout << "请输入Id:" << endl;
        signInId = Interact::inputAllInt(6);
        cout << "请输入密码:" << endl;
        signInPwd = Interact::inputEWordAndInt(10, true);
    
        signUpResult = this->QQDataM.signinQQ(signInId, signInPwd);
    
        if (signUpResult)
        {
            cout << "登录成功！\n" << endl;
            exitFlag = true;
            result = "5";
        }
        else
        {
            failTime--;
            cout << "账号Id不存在或密码错误，请重试，您还有" << failTime << "次机会" << endl;
            if (failTime < 1)
            {
                cout << "正在返回主界面" << endl;
                break;
            }
            
        }
    }
    return result;
    
    
}

// 这是QQ登录后的界面
string QQInteract::showAfterSignInMenu()
{
    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "欢迎回来！" << this->QQDataM.getUsingAccountName() << endl;
            cout << "请选择下列服务的序号输入：" << endl;
            cout << "1、好友相关服务" << endl;
            cout << "2、群相关服务" << endl;
            cout << "3、退出" << endl;
            cout << "更多服务，敬请期待" << endl;
            choice = Interact::inputAllInt(1, 1, 3);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            this->showQQFriendPage();
            break;
        case 2:
            this->showQQGroupPage();
            break;
        case 3:
            exitFlag = true;
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
            std::system("pause");
        }
        choice = "";
    }
    return result;
}


// 这是QQ好友界面
std::string QQInteract::showQQFriendPage()
{
    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "请选择下列服务的序号输入：" << endl;
            cout << "1、查看所有好友" << endl;
            cout << "2、查询好友" << endl;
            cout << "3、删除好友" << endl;
            cout << "4、添加好友" << endl;
            cout << "5、退出" << endl;
            cout << "更多服务，敬请期待" << endl;
            choice = Interact::inputAllInt(1, 1, 5);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            this->QQDataM.showAllFriend();
            break;
        case 2:
            this->searchQQFriendPage();
            break;
        case 3:
            this->delQQFriendPage();
            break;
        case 4:
            this->addQQFriendPage();
            break;
        case 5:
            exitFlag = true;
            Interact::pauseAndClearScreen();
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
            std::system("pause");
        }
        choice = "";
    }
    return result;
}


// 这是QQ群界面
std::string QQInteract::showQQGroupPage()
{
    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "请选择下列服务的序号输入：" << endl;
            cout << "1、查看所有加入的群" << endl;
            cout << "2、编辑已加入群" << endl;//查找，删除，邀请
            cout << "3、添加群" << endl;
            cout << "4、创建群" << endl;
            cout << "5、退出" << endl;
            cout << "更多服务，敬请期待" << endl;
            choice = Interact::inputAllInt(1, 1, 5);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            this->QQDataM.showAllGroup();
            choice = "";
            break;
        case 2:
            choice = this->editQQGroupPage();
            break;
        case 3:
            choice = this->joinQQGroupPage();
            break;
        case 4:
            choice = this->createQQGroupPage();
            break;
        case 5:
            exitFlag = true;
            break;
        case 6:
            choice = this->searchQQGroupPage();
            break;
        case 7:
            choice = this->exitQQGroupPage();
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
    }
    return result;
}


// 这是添加QQ好友的界面
std::string QQInteract::addQQFriendPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想添加好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    QQAccount* tempPointer = this->QQDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->QQDataM.getUsingAccountId())
    {
        cout << "不能添加自己作为好友" << endl;
    }
    else
    {
        cout << "目标用户信息为：" << endl;
        cout << "昵称：" << tempPointer->getName() << endl;
        cout << "是否添加？（1为是，0为否）"  << endl;
        string isAdd = Interact::inputAllInt(1, 0, 1);
        if (isAdd == "1")
        {
            result = true;
            this->QQDataM.addFriend(tempPointer->getName(), tempPointer->getId());
            this->QQDataM.saveAccountData();
            
            tempPointer->addFriendToList(this->QQDataM.getUsingAccountName(), this->QQDataM.getUsingAccountId());
            tempPointer->saveAccountAsFile();
            cout << "添加成功！" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }

    std::system("pause");
    std::system("cls");
       
    return result;
}

// 这是查询QQ好友的界面
std::string QQInteract::searchQQFriendPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想查询好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    QQAccount* tempPointer = this->QQDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->QQDataM.getUsingAccountId())
    {
        cout << "自己不算自己的朋友" << endl;
        
    }
    else
    {
        if (tempPointer->searchFriendById(this->QQDataM.getUsingAccountId()) == -1)
        {
            cout << "对方还不是您的好友" << endl;
        }
        else
        {
            cout << "昵称：" << tempPointer->getName() << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }

    std::system("pause");
    std::system("cls");

    return result;
}

// 这是删除QQ好友的界面
std::string QQInteract::delQQFriendPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想删除好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    QQAccount* tempPointer = this->QQDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->QQDataM.getUsingAccountId())
    {
        cout << "自己不能删除自己" << endl;

    }
    else
    {
        if (tempPointer->searchFriendById(this->QQDataM.getUsingAccountId()) == -1)
        {
            cout << "对方还不是您的好友" << endl;
        }
        else
        {
            this->QQDataM.delFriend(tempPointer->getName(), tempPointer->getId());
            tempPointer->delFriendById(this->QQDataM.getUsingAccountId());
            cout << "删除成功" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }

    std::system("pause");
    std::system("cls");

    return result;
}

// 这是编辑Q群的界面
std::string QQInteract::editQQGroupPage()
{
    string result = "";
    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入选项：" << endl;
    cout << "1、查找已加入的群" << endl;
    cout << "2、退出已加入的群" << endl;
    cout << "3、返回" << endl;
    result = Interact::inputAllInt(1, 1, 3);
    if (result == "1")
    {
        result = "6";
    }
    else if (result == "2")
    {
        result = "7";
    }
    else if (result == "3")
    {
        result = "";
    }

    return result;
}

// 这是加入Q群的界面
std::string QQInteract::joinQQGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想添加群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    QQGroup* tempPointer = this->QQDataM.getGroupById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else if (tempPointer->searchMemberById(this->QQDataM.getUsingAccountId()) != -1)
    {
        cout << "不能重复加入一个群" << endl;
    }
    else
    {
        cout << "目标群信息为：" << endl;
        cout << "昵称：" << tempPointer->getName() << endl;
        cout << "是否加入？（1为是，0为否）" << endl;
        string isAdd = Interact::inputAllInt(1, 0, 1);
        if (isAdd == "1")
        {
            result = true;
            this->QQDataM.joinGroup(tempPointer->getId());
            this->QQDataM.saveAccountData();

            tempPointer->addMemberToList(this->QQDataM.getUsingAccountName(), this->QQDataM.getUsingAccountId());
            tempPointer->saveGroupAsFile();
            cout << "加入成功！" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }

    std::system("pause");
    std::system("cls");

    return result;
}

// 这是创建Q群的界面
std::string QQInteract::createQQGroupPage()
{
    string newGroupName;
    bool result = true;
    bool exitFlag = false;

    while (!exitFlag)
    {
        cout << "--------------------------------------------------------------" << endl;
        cout << "请输入想创建群的名字:" << endl;
        newGroupName = Interact::inputEWordAndInt(10);

        this->QQDataM.createGroup(newGroupName);

        if (result)
        {
            cout << "创建群成功！"<< endl;
            exitFlag = true;
        }
        else
        {
            cout << "创建失败，请重试" << endl;
        }
    }
    
    return "";
}


// 这是退出Q群的界面
std::string QQInteract::exitQQGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想退出群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    QQGroup* tempPointer = this->QQDataM.getGroupById(Id);
    tempPointer->readGroupFromFile();

    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else if (tempPointer->searchMemberById(this->QQDataM.getUsingAccountId()) == -1)
    {
        cout << "不能退出一个没有加入的群" << endl;
    }
    else
    {
        cout << "目标群信息为：" << endl;
        cout << "昵称：" << tempPointer->getName() << endl;
        cout << "是否退出？（1为是，0为否）" << endl;
        string isAdd = Interact::inputAllInt(1, 0, 1);
        if (isAdd == "1")
        {
            this->QQDataM.exitGroup(tempPointer->getId());
            this->QQDataM.saveAccountData();

            tempPointer->delMemberById(this->QQDataM.getUsingAccountId());
            tempPointer->saveGroupAsFile();
            cout << "退出成功！" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }


    return result;
}

// 这是查询Q群的界面
std::string QQInteract::searchQQGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想查询已加入群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    QQGroup* tempPointer = this->QQDataM.getGroupById(Id);
    tempPointer->readGroupFromFile();

    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else if (nullptr == tempPointer)
    {
        cout << "尚未加入该群" << endl;
    }
    else
    {
        cout << "群名称：" << tempPointer->getName() << endl;
        delete tempPointer;
        tempPointer = nullptr;
    }


    return result;
}

