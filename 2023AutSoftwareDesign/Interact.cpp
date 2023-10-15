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
            this->QQDataM.setUsingAccountBirth(this->Interact::inputAllInt(8));
            cout << "请输入地址：" << endl;
            this->QQDataM.setUsingAccountLocate(this->Interact::inputEWordAndInt(20));
            this->QQDataM.saveAccountData();
        }
        else
        {
            cout << "注册失败，请重试" << endl;
        }
    }
    
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
        this->QQDataM.updateUsingAccount();
        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "欢迎回来！" << this->QQDataM.getUsingAccountName() << endl;
            cout << "请选择下列服务的序号输入：" << endl;
            cout << "1、好友相关服务" << endl;
            cout << "2、群相关服务" << endl;
            cout << "3、设置" << endl;
            cout << "4、退出" << endl;
            cout << "更多服务，敬请期待" << endl;
            choice = Interact::inputAllInt(1, 1, 4);
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
            this->showQQSettingPage();
            break;
        case 4:
            exitFlag = true;
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
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
        this->QQDataM.updateUsingAccount();
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
            choice = "";
            break;
        case 2:
            choice = this->searchQQFriendPage();
            break;
        case 3:
            choice = this->delQQFriendPage();
            break;
        case 4:
            choice = this->addQQFriendPage();
            break;
        case 5:
            exitFlag = true;
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
            this->QQDataM.addFriend(tempPointer->getName(), tempPointer->getId());
            this->QQDataM.saveAccountData();
            
            tempPointer->addFriendToList(this->QQDataM.getUsingAccountName(), this->QQDataM.getUsingAccountId());
            tempPointer->saveAccountAsFile();
            cout << "添加成功！" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }
;
       
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
            cout << "生日：" << tempPointer->getBirth() << endl;
            cout << "地址：" << tempPointer->getLocate() << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }


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
        this->QQDataM.updateUsingAccount();

        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "请选择下列服务的序号输入：" << endl;
            cout << "1、查看所有加入的群" << endl;
            cout << "2、编辑已加入群" << endl;//查找，删除，邀请
            cout << "3、加入群" << endl;
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
        case 8:
            choice = this->inviteFriendToQQGroupPage();
            break;
        case 9:
            choice = this->delQQGroupPage();
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
    }
    return result;
}

// 这是编辑Q群的界面
std::string QQInteract::editQQGroupPage()
{
    string result = "";
    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入选项：" << endl;
    cout << "1、查询已加入的群的详情" << endl;
    cout << "2、退出已加入的群" << endl;
    cout << "3、邀请好友加入自己已加入的群" << endl;
    cout << "4、删除自己创建的群" << endl;
    cout << "5、返回" << endl;
    result = Interact::inputAllInt(1, 1, 4);
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
        result = "8";
    }
    else if (result == "4")
    {
        result = "9";
    }
    else if (result == "5")
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
    else
    {
        tempPointer->readGroupFromFile();
        if (tempPointer->searchMemberById(this->QQDataM.getUsingAccountId()) != -1)
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
                this->QQDataM.joinGroup(tempPointer->getId());
                this->QQDataM.saveAccountData();

                tempPointer->addMemberToList(this->QQDataM.getUsingAccountName(), this->QQDataM.getUsingAccountId());
                tempPointer->saveGroupAsFile();
                cout << "加入成功！" << endl;
            }
            delete tempPointer;
            tempPointer = nullptr;
        }
    }
    


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
    

    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (tempPointer->searchMemberById(this->QQDataM.getUsingAccountId()) == -1)
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
    

    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (nullptr == this->QQDataM.getGroupById(tempPointer->getId()))
        {
            cout << "尚未加入该群" << endl;
        }
        else
        {
            cout << "群名称：" << tempPointer->getName() << endl;
            cout << "群成员Id    群成员昵称" << endl;
            tempPointer->showMemberList();
            delete tempPointer;
            tempPointer = nullptr;
        }
    }
    


    return result;
}

// 这是给Q群邀请好友的界面
std::string QQInteract::inviteFriendToQQGroupPage()
{
    string result = "";
    string Id = "";
    bool continueFlag = false;


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想邀请进群的好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    QQAccount* tempPointer1 = this->QQDataM.getAccountById(Id);

    // 第一部分先确定要邀请的好友
    if (tempPointer1 == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->QQDataM.getUsingAccountId())
    {
        cout << "自己不能邀请自己" << endl;

    }
    else
    {
        if (tempPointer1->searchFriendById(this->QQDataM.getUsingAccountId()) == -1)
        {
            cout << "对方还不是您的好友" << endl;
        }
        else
        {
            cout << "昵称：" << tempPointer1->getName() << endl;
            cout << "是否邀请？（1为是，0为否）" << endl;
            string isAdd = Interact::inputAllInt(1, 0, 1);
            if (isAdd == "1")
            {
                continueFlag = true;
            }
        }
    }

    // 第二部分确定要邀请的群
    if (continueFlag)
    {

        cout << "--------------------------------------------------------------" << endl;
        cout << "请输入想添加群的Id：" << endl;
        Id = Interact::inputAllInt(6);
        QQGroup* tempPointer2 = this->QQDataM.getGroupById(Id);


        if (tempPointer2 == nullptr)
        {
            cout << "该Id群不存在" << endl;
        }
        else
        {
            tempPointer2->readGroupFromFile();
            if (tempPointer2->searchMemberById(tempPointer1->getId()) != -1)
            {
                cout << "对方已加入该群，无需邀请" << endl;
            }
            else if (tempPointer2->searchMemberById(this->QQDataM.getUsingAccountId()) == -1)
            {
                cout << "您尚未加入该群，无权限邀请" << endl;
            }
            else
            {
                cout << "目标群信息为：" << endl;
                cout << "昵称：" << tempPointer2->getName() << endl;
                cout << "再次确定是否邀请？（1为是，0为否）" << endl;
                string isAdd = Interact::inputAllInt(1, 0, 1);
                if (isAdd == "1")
                {
                    tempPointer1->joinGroupToList(tempPointer2->getName(), tempPointer2->getId());
                    tempPointer1->saveAccountAsFile();

                    tempPointer2->addMemberToList(tempPointer1->getName(), tempPointer1->getId());
                    tempPointer2->saveGroupAsFile();
                    cout << "加入成功！" << endl;
                }
            }
            delete tempPointer2;
            tempPointer2 = nullptr;
        }
    }



    delete tempPointer1;
    tempPointer1 = nullptr;

    

    return result;
}

// 这是删除Q群的界面
std::string QQInteract::delQQGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想删除的群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    QQGroup* tempPointer = this->QQDataM.getGroupById(Id);
    

    if (tempPointer == nullptr)
    {
        cout << "您不能删除没有加入的群" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (tempPointer->searchMemberById(this->QQDataM.getUsingAccountId()) != 0)
        {
            cout << "您无权删除该群" << endl;
        }
        else
        {
            cout << "群名称：" << tempPointer->getName() << endl;
            cout << "群成员Id    群成员昵称" << endl;
            tempPointer->showMemberList();
            cout << "是否删除？（1为是，0为否）" << endl;
            string isAdd = Interact::inputAllInt(1, 0, 1);
            if (isAdd == "1")
            {
                this->QQDataM.exitGroup(tempPointer->getId());
                this->QQDataM.delGroupId(tempPointer->getId());
                tempPointer->delFromAllMember();
                
                cout << "删除成功！" << endl;
            }
            delete tempPointer;
            tempPointer = nullptr;
        }
    }
    


    return result;
}

// 这是QQ用户设置界面
std::string QQInteract::showQQSettingPage()
{
    

    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "请输入您想更改信息前的序号：" << endl;
            cout << "1、账户昵称：" << this->QQDataM.getUsingAccountName() << endl;
            cout << "2、账户Id：" << this->QQDataM.getUsingAccountId() << endl;
            cout << "3、账户密码：" << this->QQDataM.getUsingAccountPwd() << endl;
            cout << "4、生日：" << this->QQDataM.getUsingAccountBirth() << endl;
            cout << "5、地址：" << this->QQDataM.getUsingAccountLocate() << endl;
            cout << "6、关联Wechat账号Id：" << this->QQDataM.getUsingAccountBindWechatAccount() << endl;
            cout << "7、关联Weibo账号Id：" << this->QQDataM.getUsingAccountBindWeiboAccount() << endl;
            cout << "8、返回" << endl;
            choice = Interact::inputAllInt(1, 1, 8);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            cout << "请输入您想更改成的昵称：" << endl;
            this->QQDataM.setUsingAccountName(Interact::inputEWordAndInt(10));
            this->QQDataM.saveAccountData();
            choice = "";
            break;
        case 2:
            cout << "QQId不可更改！" << endl;
            choice = "";
            break;
        case 3:
            cout << "请输入您想更改成的密码：" << endl;
            this->QQDataM.setUsingAccountPwd(Interact::inputEWordAndInt(10));
            this->QQDataM.saveAccountData();
            choice = "";
            break;
        case 4:
            cout << "请输入您想更改成的生日：" << endl;
            this->QQDataM.setUsingAccountBirth(Interact::inputAllInt(8));
            this->QQDataM.saveAccountData();
            choice = "";
            break;
        case 5:
            cout << "请输入您想更改成的地址：" << endl;
            this->QQDataM.setUsingAccountLocate(Interact::inputEWordAndInt(20));
            this->QQDataM.saveAccountData();
            choice = "";
            break;
        case 6:
        {
            cout << "请输入您想绑定的Wechat账号Id：" << endl;
            string tempAccountId = Interact::inputAllInt(6);
            WechatDataManage m;
            WechatAccount* tempPointer = m.getAccountById(tempAccountId);
            if (tempPointer == nullptr)
            {
                cout << "不存在该Id的Wechat用户" << endl;
            }
            else
            {
                this->QQDataM.setUsingAccountBindWechatAccount(tempAccountId);
                tempPointer->setBindQQAccountId(this->QQDataM.getUsingAccountId());
                tempPointer->saveAccountAsFile();
                this->QQDataM.saveAccountData();
                cout << "绑定成功" << endl;
            }
            choice = "";
            break;
        }
        case 7:
            cout << "绑定后的Weibo账号不可更改：" << endl;
            choice = "";
            break;
        case 8:
            exitFlag = true;
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
    }
    return result;

}




// 这是Wechat开始界面
string WechatInteract::showStartMenu()
{
    cout << "--------------------------------------------------------------" << endl;
    string text = "您已选择Wechat相关服务，可选择下列服务的序号输入：\n1、登录Wechat\n2、注册Wechat\n3、注销Wechat\n4、返回\n更多服务，敬请期待";
    cout << text << endl;
    return Interact::inputAllInt(1, 1, 4);
}

// 这是Wechat注册界面
string WechatInteract::showSignUpPage()
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

        result = this->WechatDataM.signupWechat(signUpName, signUpPwd);

        if (result)
        {
            cout << "注册成功！\n" << "您的Id是：" << this->WechatDataM.getUsingAccountId() << " 正在进入登陆界面\n" << endl;
            exitFlag = true;
            cout << "请输入生日:" << endl;
            this->WechatDataM.setUsingAccountBirth(this->Interact::inputAllInt(8));
            cout << "请输入地址：" << endl;
            this->WechatDataM.setUsingAccountLocate(this->Interact::inputEWordAndInt(20));
            this->WechatDataM.saveAccountData();
        }
        else
        {
            cout << "注册失败，请重试" << endl;
        }
    }

    return "1";
}

// 这是注销Wechat账户的界面
string WechatInteract::showLogOffMenu()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想注销账号的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WechatAccount* tempPointer = this->WechatDataM.getAccountById(Id);

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
            this->WechatDataM.delAccountId(tempPointer->getId());
            WechatAccount::createOrResetFile(tempPointer->getId());
            cout << "注销成功！" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }


    return result;
}

// 这是Wechat登录界面
string WechatInteract::showSignInPage()
{
    string signInId;
    string signInPwd;
    bool signInResult;
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

        signInResult = this->WechatDataM.signinWechat(signInId, signInPwd);

        if (signInResult)
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

// 这是Wechat登录后的界面
string WechatInteract::showAfterSignInMenu()
{
    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        this->WechatDataM.updateUsingAccount();
        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "欢迎回来！" << this->WechatDataM.getUsingAccountName() << endl;
            cout << "请选择下列服务的序号输入：" << endl;
            cout << "1、好友相关服务" << endl;
            cout << "2、群相关服务" << endl;
            cout << "3、设置" << endl;
            cout << "4、退出" << endl;
            cout << "更多服务，敬请期待" << endl;
            choice = Interact::inputAllInt(1, 1, 4);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            this->showWechatFriendPage();
            break;
        case 2:
            this->showWechatGroupPage();
            break;
        case 3:
            this->showWechatSettingPage();
            break;
        case 4:
            exitFlag = true;
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        choice = "";
    }
    return result;
}

// 这是Wechat好友界面
std::string WechatInteract::showWechatFriendPage()
{
    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        this->WechatDataM.updateUsingAccount();
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
            this->WechatDataM.showAllFriend();
            choice = "";
            break;
        case 2:
            choice = this->searchWechatFriendPage();
            break;
        case 3:
            choice = this->delWechatFriendPage();
            break;
        case 4:
            choice = this->addWechatFriendPage();
            break;
        case 5:
            exitFlag = true;
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
    }
    return result;
}

// 这是添加Wechat好友的界面
std::string WechatInteract::addWechatFriendPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想添加好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WechatAccount* tempPointer = this->WechatDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->WechatDataM.getUsingAccountId())
    {
        cout << "不能添加自己作为好友" << endl;
    }
    else
    {
        cout << "目标用户信息为：" << endl;
        cout << "昵称：" << tempPointer->getName() << endl;
        cout << "是否添加？（1为是，0为否）" << endl;
        string isAdd = Interact::inputAllInt(1, 0, 1);
        if (isAdd == "1")
        {
            this->WechatDataM.addFriend(tempPointer->getName(), tempPointer->getId());
            this->WechatDataM.saveAccountData();

            tempPointer->addFriendToList(this->WechatDataM.getUsingAccountName(), this->WechatDataM.getUsingAccountId());
            tempPointer->saveAccountAsFile();
            cout << "添加成功！" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }
    ;

    return result;
}

// 这是查询Wechat好友的界面
std::string WechatInteract::searchWechatFriendPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想查询好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WechatAccount* tempPointer = this->WechatDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->WechatDataM.getUsingAccountId())
    {
        cout << "自己不算自己的朋友" << endl;

    }
    else
    {
        if (tempPointer->searchFriendById(this->WechatDataM.getUsingAccountId()) == -1)
        {
            cout << "对方还不是您的好友" << endl;
        }
        else
        {
            cout << "昵称：" << tempPointer->getName() << endl;
            cout << "生日：" << tempPointer->getBirth() << endl;
            cout << "地址：" << tempPointer->getLocate() << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }


    return result;
}

// 这是删除Wechat好友的界面
std::string WechatInteract::delWechatFriendPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想删除好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WechatAccount* tempPointer = this->WechatDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->WechatDataM.getUsingAccountId())
    {
        cout << "自己不能删除自己" << endl;

    }
    else
    {
        if (tempPointer->searchFriendById(this->WechatDataM.getUsingAccountId()) == -1)
        {
            cout << "对方还不是您的好友" << endl;
        }
        else
        {
            this->WechatDataM.delFriend(tempPointer->getName(), tempPointer->getId());
            tempPointer->delFriendById(this->WechatDataM.getUsingAccountId());
            cout << "删除成功" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }


    return result;
}


// 这是Wechat群界面
std::string WechatInteract::showWechatGroupPage()
{
    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        this->WechatDataM.updateUsingAccount();

        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "请选择下列服务的序号输入：" << endl;
            cout << "1、查看所有加入的群" << endl;
            cout << "2、编辑已加入群" << endl;//查找，删除，邀请
            cout << "3、加入群" << endl;
            cout << "4、创建群" << endl;
            cout << "5、退出" << endl;
            cout << "更多服务，敬请期待" << endl;
            choice = Interact::inputAllInt(1, 1, 5);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            this->WechatDataM.showAllGroup();
            choice = "";
            break;
        case 2:
            choice = this->editWechatGroupPage();
            break;
        case 3:
            choice = this->joinWechatGroupPage();
            break;
        case 4:
            choice = this->createWechatGroupPage();
            break;
        case 5:
            exitFlag = true;
            break;
        case 6:
            choice = this->searchWechatGroupPage();
            break;
        case 7:
            choice = this->exitWechatGroupPage();
            break;
        case 8:
            choice = this->inviteFriendToWechatGroupPage();
            break;
        case 9:
            choice = this->delWechatGroupPage();
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
    }
    return result;
}

// 这是编辑Wechat群的界面
std::string WechatInteract::editWechatGroupPage()
{
    string result = "";
    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入选项：" << endl;
    cout << "1、查询已加入的群的详情" << endl;
    cout << "2、退出已加入的群" << endl;
    cout << "3、邀请好友加入自己已加入的群" << endl;
    cout << "4、删除自己创建的群" << endl;
    cout << "5、返回" << endl;
    result = Interact::inputAllInt(1, 1, 4);
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
        result = "8";
    }
    else if (result == "4")
    {
        result = "9";
    }
    else if (result == "5")
    {
        result = "";
    }

    return result;
}

// 这是加入Wechat群的界面
std::string WechatInteract::joinWechatGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "Wechat只能通过好友邀请进群" << endl;

    return result;
}

// 这是创建Wechat群的界面
std::string WechatInteract::createWechatGroupPage()
{
    string newGroupName;
    bool result = true;
    bool exitFlag = false;

    while (!exitFlag)
    {
        cout << "--------------------------------------------------------------" << endl;
        cout << "请输入想创建群的名字:" << endl;
        newGroupName = Interact::inputEWordAndInt(10);

        this->WechatDataM.createGroup(newGroupName);

        if (result)
        {
            cout << "创建群成功！" << endl;
            exitFlag = true;
        }
        else
        {
            cout << "创建失败，请重试" << endl;
        }
    }

    return "";
}

// 这是退出Wechat群的界面
std::string WechatInteract::exitWechatGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想退出群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WechatGroup* tempPointer = this->WechatDataM.getGroupById(Id);


    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (tempPointer->searchMemberById(this->WechatDataM.getUsingAccountId()) == -1)
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
                this->WechatDataM.exitGroup(tempPointer->getId());
                this->WechatDataM.saveAccountData();

                tempPointer->delMemberById(this->WechatDataM.getUsingAccountId());
                tempPointer->saveGroupAsFile();
                cout << "退出成功！" << endl;
            }
            delete tempPointer;
            tempPointer = nullptr;
        }
    }



    return result;
}

// 这是查询Wechat群的界面
std::string WechatInteract::searchWechatGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想查询已加入群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WechatGroup* tempPointer = this->WechatDataM.getGroupById(Id);
    

    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (nullptr == this->WechatDataM.getGroupById(tempPointer->getId()))
        {
            cout << "尚未加入该群" << endl;
        }
        else
        {
            cout << "群名称：" << tempPointer->getName() << endl;
            cout << "群成员Id    群成员昵称" << endl;
            tempPointer->showMemberList();
            delete tempPointer;
            tempPointer = nullptr;
        }
    }



    return result;
}

// 这是给Wechat群邀请好友的界面
std::string WechatInteract::inviteFriendToWechatGroupPage()
{
    string result = "";
    string Id = "";
    bool continueFlag = false;


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想邀请进群的好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WechatAccount* tempPointer1 = this->WechatDataM.getAccountById(Id);

    // 第一部分先确定要邀请的好友
    if (tempPointer1 == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->WechatDataM.getUsingAccountId())
    {
        cout << "自己不能邀请自己" << endl;

    }
    else
    {
        if (tempPointer1->searchFriendById(this->WechatDataM.getUsingAccountId()) == -1)
        {
            cout << "对方还不是您的好友" << endl;
        }
        else
        {
            cout << "昵称：" << tempPointer1->getName() << endl;
            cout << "是否邀请？（1为是，0为否）" << endl;
            string isAdd = Interact::inputAllInt(1, 0, 1);
            if (isAdd == "1")
            {
                continueFlag = true;
            }
        }
    }

    // 第二部分确定要邀请的群
    if (continueFlag)
    {

        cout << "--------------------------------------------------------------" << endl;
        cout << "请输入想添加群的Id：" << endl;
        Id = Interact::inputAllInt(6);
        WechatGroup* tempPointer2 = this->WechatDataM.getGroupById(Id);


        if (tempPointer2 == nullptr)
        {
            cout << "该Id群不存在" << endl;
        }
        else
        {
            tempPointer2->readGroupFromFile();
            if (tempPointer2->searchMemberById(tempPointer1->getId()) != -1)
            {
                cout << "对方已加入该群，无需邀请" << endl;
            }
            else if (tempPointer2->searchMemberById(this->WechatDataM.getUsingAccountId()) == -1)
            {
                cout << "您尚未加入该群，无权限邀请" << endl;
            }
            else
            {
                cout << "目标群信息为：" << endl;
                cout << "昵称：" << tempPointer2->getName() << endl;
                cout << "再次确定是否邀请？（1为是，0为否）" << endl;
                string isAdd = Interact::inputAllInt(1, 0, 1);
                if (isAdd == "1")
                {
                    tempPointer1->joinGroupToList(tempPointer2->getName(), tempPointer2->getId());
                    tempPointer1->saveAccountAsFile();

                    tempPointer2->addMemberToList(tempPointer1->getName(), tempPointer1->getId());
                    tempPointer2->saveGroupAsFile();
                    cout << "加入成功！" << endl;
                }
            }
            delete tempPointer2;
            tempPointer2 = nullptr;
        }
    }



    delete tempPointer1;
    tempPointer1 = nullptr;



    return result;
}

// 这是删除Wechat群的界面
std::string WechatInteract::delWechatGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想删除的群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WechatGroup* tempPointer = this->WechatDataM.getGroupById(Id);


    if (tempPointer == nullptr)
    {
        cout << "您不能删除没有加入的群" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (tempPointer->searchMemberById(this->WechatDataM.getUsingAccountId()) != 0)
        {
            cout << "您无权删除该群" << endl;
        }
        else
        {
            cout << "群名称：" << tempPointer->getName() << endl;
            cout << "群成员Id    群成员昵称" << endl;
            tempPointer->showMemberList();
            cout << "是否删除？（1为是，0为否）" << endl;
            string isAdd = Interact::inputAllInt(1, 0, 1);
            if (isAdd == "1")
            {
                this->WechatDataM.exitGroup(tempPointer->getId());
                this->WechatDataM.delGroupId(tempPointer->getId());
                tempPointer->delFromAllMember();

                cout << "删除成功！" << endl;
            }
            delete tempPointer;
            tempPointer = nullptr;
        }
    }



    return result;
}

// 这是Wechat用户设置界面
std::string WechatInteract::showWechatSettingPage()
{


    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "请输入您想更改信息前的序号：" << endl;
            cout << "1、账户昵称：" << this->WechatDataM.getUsingAccountName() << endl;
            cout << "2、账户Id：" << this->WechatDataM.getUsingAccountId() << endl;
            cout << "3、账户密码：" << this->WechatDataM.getUsingAccountPwd() << endl;
            cout << "4、生日：" << this->WechatDataM.getUsingAccountBirth() << endl;
            cout << "5、地址：" << this->WechatDataM.getUsingAccountLocate() << endl;
            cout << "6、关联QQ账号：" << this->WechatDataM.getUsingAccountBindQQAccountId() << endl;
            cout << "7、关联Weibo账号：" << this->WechatDataM.getUsingAccountBindWeiboAccountId() << endl;
            cout << "8、返回" << endl;
            choice = Interact::inputAllInt(1, 1, 8);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            cout << "请输入您想更改成的昵称：" << endl;
            this->WechatDataM.setUsingAccountName(Interact::inputEWordAndInt(10));
            this->WechatDataM.saveAccountData();
            choice = "";
            break;
        case 2:
            cout << "WechatId不可更改！" << endl;
            choice = "";
            break;
        case 3:
            cout << "请输入您想更改成的密码：" << endl;
            this->WechatDataM.setUsingAccountPwd(Interact::inputEWordAndInt(10));
            this->WechatDataM.saveAccountData();
            choice = "";
            break;
        case 4:
            cout << "请输入您想更改成的生日：" << endl;
            this->WechatDataM.setUsingAccountBirth(Interact::inputAllInt(8));
            this->WechatDataM.saveAccountData();
            choice = "";
            break;
        case 5:
            cout << "请输入您想更改成的地址：" << endl;
            this->WechatDataM.setUsingAccountLocate(Interact::inputEWordAndInt(20));
            this->WechatDataM.saveAccountData();
            choice = "";
            break;
        case 6:
        {
            cout << "请输入您想绑定的QQ账号Id：" << endl;
            string tempAccountId = Interact::inputAllInt(6);
            QQDataManage m;
            QQAccount* tempPointer = m.getAccountById(tempAccountId);
            if (tempPointer == nullptr)
            {
                cout << "不存在该Id的QQ用户" << endl;
            }
            else
            {
                this->WechatDataM.setUsingAccountBindQQAccountId(tempAccountId);
                tempPointer->setBindWechatAccountId(this->WechatDataM.getUsingAccountId());
                tempPointer->saveAccountAsFile();
                this->WechatDataM.saveAccountData();
                cout << "绑定成功" << endl;

                if (tempPointer->getBindWeiboAccountId() == "")
                {
                    cout << "该QQ没有绑定Weibo账号，请在QQ绑定Weibo后，点击WeiboId处刷新" << endl;
                }
                else
                {
                    WeiboDataManage m;
                    WeiboAccount* tempPointer = m.getAccountById(this->WechatDataM.getUsingAccountBindQQAccountId());
                    this->WechatDataM.setUsingAccountBindWeiboAccountId(this->WechatDataM.getUsingAccountBindQQAccountId());
                    tempPointer->setBindWechatAccountId(this->WechatDataM.getUsingAccountId());
                    tempPointer->saveAccountAsFile();
                    this->WechatDataM.saveAccountData();
                }

            }

            
            choice = "";
            break;
        }
        case 7:
        {
            cout << "绑定后的Weibo账号不可更改：" << endl;
            WeiboDataManage m;
            if (this->WechatDataM.getUsingAccountBindQQAccountId() != "")
            {
                WeiboAccount* tempPointer = m.getAccountById(this->WechatDataM.getUsingAccountBindQQAccountId());
                this->WechatDataM.setUsingAccountBindWeiboAccountId(this->WechatDataM.getUsingAccountBindQQAccountId());
                tempPointer->setBindWechatAccountId(this->WechatDataM.getUsingAccountId());
                tempPointer->saveAccountAsFile();
                this->WechatDataM.saveAccountData();
                cout << "刷新绑定成功" << endl;
            }
            choice = "";
            break;
        }
        case 8:
            exitFlag = true;
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
    }
    return result;

}




// 这是Weibo开始界面
string WeiboInteract::showStartMenu()
{
    cout << "--------------------------------------------------------------" << endl;
    string text = "您已选择Weibo相关服务，可选择下列服务的序号输入：\n1、登录Weibo\n2、注册Weibo\n3、注销Weibo\n4、返回\n更多服务，敬请期待";
    cout << text << endl;
    return Interact::inputAllInt(1, 1, 4);
}

// 这是Weibo注册界面
string WeiboInteract::showSignUpPage()
{
    string signUpName;
    string signUpPwd;
    string bindId;

    bool result;
    bool exitFlag = false;

    while (!exitFlag)
    {
        cout << "--------------------------------------------------------------" << endl;
        cout << "请输入要绑定的QQId:" << endl;
        bindId = Interact::inputAllInt(6);
        

        QQDataManage m;
        QQAccount* tempPointer = m.getAccountById(bindId);

        if (tempPointer == nullptr)
        {
            cout << "该Id用户不存在" << endl;
            return "";
        }
        else if (tempPointer->getBindWeiboAccountId() != "")
        {
            cout << "该Id用户已绑定Weibo账号" << endl;
            return "";
        }
        else
        {
            cout << "目标用户信息为：" << endl;
            cout << "昵称：" << tempPointer->getName() << endl;
            cout << "是否绑定？（1为是，0为否）" << endl;
            string isAdd = Interact::inputAllInt(1, 0, 1);
            if (isAdd == "1")
            {
                tempPointer->setBindWeiboAccountId(bindId);
                tempPointer->saveAccountAsFile();
                cout << "绑定成功！" << endl;
                
            }
            else
            {
                return "";
            }
            delete tempPointer;
            tempPointer = nullptr;
        }

       
        cout << "请输入用户名:" << endl;
        signUpName = Interact::inputEWordAndInt(10);
        cout << "请输入密码:" << endl;
        signUpPwd = Interact::inputEWordAndInt(10);

        result = this->WeiboDataM.signupWeibo(signUpName, signUpPwd, bindId);

        this->WeiboDataM.setUsingAccountBindQQAccountId(bindId);

        if (result)
        {
            cout << "注册成功！\n" << "您的Id是：" << this->WeiboDataM.getUsingAccountId() << " 正在进入登陆界面\n" << endl;
            exitFlag = true;
            cout << "请输入生日:" << endl;
            this->WeiboDataM.setUsingAccountBirth(this->Interact::inputAllInt(8));
            cout << "请输入地址：" << endl;
            this->WeiboDataM.setUsingAccountLocate(this->Interact::inputEWordAndInt(20));
            this->WeiboDataM.saveAccountData();
        }
        else
        {
            cout << "注册失败，请重试" << endl;
        }
    }

    return "1";
}

// 这是注销Weibo账户的界面
string WeiboInteract::showLogOffMenu()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想注销账号的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WeiboAccount* tempPointer = this->WeiboDataM.getAccountById(Id);

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
            this->WeiboDataM.delAccountId(tempPointer->getId());
            WeiboAccount::createOrResetFile(tempPointer->getId());
            cout << "注销成功！" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }


    return result;
}

// 这是Weibo登录界面
string WeiboInteract::showSignInPage()
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

        signUpResult = this->WeiboDataM.signinWeibo(signInId, signInPwd);

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

// 这是Weibo登录后的界面
string WeiboInteract::showAfterSignInMenu()
{
    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        this->WeiboDataM.updateUsingAccount();
        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "欢迎回来！" << this->WeiboDataM.getUsingAccountName() << endl;
            cout << "请选择下列服务的序号输入：" << endl;
            cout << "1、好友相关服务" << endl;
            cout << "2、群相关服务" << endl;
            cout << "3、设置" << endl;
            cout << "4、退出" << endl;
            cout << "更多服务，敬请期待" << endl;
            choice = Interact::inputAllInt(1, 1, 4);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            this->showWeiboFriendPage();
            break;
        case 2:
            this->showWeiboGroupPage();
            break;
        case 3:
            this->showWeiboSettingPage();
            break;
        case 4:
            exitFlag = true;
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        choice = "";
    }
    return result;
}

// 这是Weibo好友界面
std::string WeiboInteract::showWeiboFriendPage()
{
    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        this->WeiboDataM.updateUsingAccount();
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
            this->WeiboDataM.showAllFriend();
            choice = "";
            break;
        case 2:
            choice = this->searchWeiboFriendPage();
            break;
        case 3:
            choice = this->delWeiboFriendPage();
            break;
        case 4:
            choice = this->addWeiboFriendPage();
            break;
        case 5:
            exitFlag = true;
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
    }
    return result;
}

// 这是添加Weibo好友的界面
std::string WeiboInteract::addWeiboFriendPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想添加好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WeiboAccount* tempPointer = this->WeiboDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->WeiboDataM.getUsingAccountId())
    {
        cout << "不能添加自己作为好友" << endl;
    }
    else
    {
        cout << "目标用户信息为：" << endl;
        cout << "昵称：" << tempPointer->getName() << endl;
        cout << "是否添加？（1为是，0为否）" << endl;
        string isAdd = Interact::inputAllInt(1, 0, 1);
        if (isAdd == "1")
        {
            this->WeiboDataM.addFriend(tempPointer->getName(), tempPointer->getId());
            this->WeiboDataM.saveAccountData();

            //tempPointer->addFriendToList(this->WeiboDataM.getUsingAccountName(), this->WeiboDataM.getUsingAccountId());
            //tempPointer->saveAccountAsFile();
            cout << "添加成功！" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }
    ;

    return result;
}

// 这是查询Weibo好友的界面
std::string WeiboInteract::searchWeiboFriendPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想查询好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WeiboAccount* tempPointer = this->WeiboDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->WeiboDataM.getUsingAccountId())
    {
        cout << "自己不算自己的朋友" << endl;

    }
    else
    {
        if (tempPointer->searchFriendById(this->WeiboDataM.getUsingAccountId()) == -1)
        {
            cout << "对方还不是您的好友" << endl;
        }
        else
        {
            cout << "昵称：" << tempPointer->getName() << endl;
            cout << "生日：" << tempPointer->getBirth() << endl;
            cout << "地址：" << tempPointer->getLocate() << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }


    return result;
}

// 这是删除Weibo好友的界面
std::string WeiboInteract::delWeiboFriendPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想删除好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WeiboAccount* tempPointer = this->WeiboDataM.getAccountById(Id);

    if (tempPointer == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->WeiboDataM.getUsingAccountId())
    {
        cout << "自己不能删除自己" << endl;

    }
    else
    {
        if (tempPointer->searchFriendById(this->WeiboDataM.getUsingAccountId()) == -1)
        {
            cout << "对方还不是您的好友" << endl;
        }
        else
        {
            this->WeiboDataM.delFriend(tempPointer->getName(), tempPointer->getId());
            //tempPointer->delFriendById(this->WeiboDataM.getUsingAccountId());
            cout << "删除成功" << endl;
        }
        delete tempPointer;
        tempPointer = nullptr;
    }


    return result;
}


// 这是Weibo群界面
std::string WeiboInteract::showWeiboGroupPage()
{
    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        this->WeiboDataM.updateUsingAccount();

        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "请选择下列服务的序号输入：" << endl;
            cout << "1、查看所有加入的群" << endl;
            cout << "2、编辑已加入群" << endl;//查找，删除，邀请
            cout << "3、加入群" << endl;
            cout << "4、创建群" << endl;
            cout << "5、退出" << endl;
            cout << "更多服务，敬请期待" << endl;
            choice = Interact::inputAllInt(1, 1, 5);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            this->WeiboDataM.showAllGroup();
            choice = "";
            break;
        case 2:
            choice = this->editWeiboGroupPage();
            break;
        case 3:
            choice = this->joinWeiboGroupPage();
            break;
        case 4:
            choice = this->createWeiboGroupPage();
            break;
        case 5:
            exitFlag = true;
            break;
        case 6:
            choice = this->searchWeiboGroupPage();
            break;
        case 7:
            choice = this->exitWeiboGroupPage();
            break;
        case 8:
            choice = this->inviteFriendToWeiboGroupPage();
            break;
        case 9:
            choice = this->delWeiboGroupPage();
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
    }
    return result;
}

// 这是编辑Weibo群的界面
std::string WeiboInteract::editWeiboGroupPage()
{
    string result = "";
    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入选项：" << endl;
    cout << "1、查询已加入的群的详情" << endl;
    cout << "2、退出已加入的群" << endl;
    cout << "3、邀请好友加入自己已加入的群" << endl;
    cout << "4、删除自己创建的群" << endl;
    cout << "5、返回" << endl;
    result = Interact::inputAllInt(1, 1, 4);
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
        result = "8";
    }
    else if (result == "4")
    {
        result = "9";
    }
    else if (result == "5")
    {
        result = "";
    }

    return result;
}

// 这是加入Weibo群的界面
std::string WeiboInteract::joinWeiboGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想添加群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WeiboGroup* tempPointer = this->WeiboDataM.getGroupById(Id);


    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (tempPointer->searchMemberById(this->WeiboDataM.getUsingAccountId()) != -1)
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
                this->WeiboDataM.joinGroup(tempPointer->getId());
                this->WeiboDataM.saveAccountData();

                tempPointer->addMemberToList(this->WeiboDataM.getUsingAccountName(), this->WeiboDataM.getUsingAccountId());
                tempPointer->saveGroupAsFile();
                cout << "加入成功！" << endl;
            }
            delete tempPointer;
            tempPointer = nullptr;
        }
    }



    return result;
}

// 这是创建Weibo群的界面
std::string WeiboInteract::createWeiboGroupPage()
{
    string newGroupName;
    bool result = true;
    bool exitFlag = false;

    while (!exitFlag)
    {
        cout << "--------------------------------------------------------------" << endl;
        cout << "请输入想创建群的名字:" << endl;
        newGroupName = Interact::inputEWordAndInt(10);

        this->WeiboDataM.createGroup(newGroupName);

        if (result)
        {
            cout << "创建群成功！" << endl;
            exitFlag = true;
        }
        else
        {
            cout << "创建失败，请重试" << endl;
        }
    }

    return "";
}

// 这是退出Weibo群的界面
std::string WeiboInteract::exitWeiboGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想退出群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WeiboGroup* tempPointer = this->WeiboDataM.getGroupById(Id);


    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (tempPointer->searchMemberById(this->WeiboDataM.getUsingAccountId()) == -1)
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
                this->WeiboDataM.exitGroup(tempPointer->getId());
                this->WeiboDataM.saveAccountData();

                tempPointer->delMemberById(this->WeiboDataM.getUsingAccountId());
                tempPointer->saveGroupAsFile();
                cout << "退出成功！" << endl;
            }
            delete tempPointer;
            tempPointer = nullptr;
        }
    }



    return result;
}

// 这是查询Weibo群的界面
std::string WeiboInteract::searchWeiboGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想查询已加入群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WeiboGroup* tempPointer = this->WeiboDataM.getGroupById(Id);
    

    if (tempPointer == nullptr)
    {
        cout << "该Id群不存在" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (nullptr == this->WeiboDataM.getGroupById(tempPointer->getId()))
        {
            cout << "尚未加入该群" << endl;
        }
        else
        {
            cout << "群名称：" << tempPointer->getName() << endl;
            cout << "群成员Id    群成员昵称" << endl;
            tempPointer->showMemberList();
            delete tempPointer;
            tempPointer = nullptr;
        }
    }



    return result;
}

// 这是给Weibo群邀请好友的界面
std::string WeiboInteract::inviteFriendToWeiboGroupPage()
{
    string result = "";
    string Id = "";
    bool continueFlag = false;


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想邀请进群的好友的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WeiboAccount* tempPointer1 = this->WeiboDataM.getAccountById(Id);

    // 第一部分先确定要邀请的好友
    if (tempPointer1 == nullptr)
    {
        cout << "该Id用户不存在" << endl;
    }
    else if (Id == this->WeiboDataM.getUsingAccountId())
    {
        cout << "自己不能邀请自己" << endl;

    }
    else
    {
        if (tempPointer1->searchFriendById(this->WeiboDataM.getUsingAccountId()) == -1)
        {
            cout << "对方还不是您的好友" << endl;
        }
        else
        {
            cout << "昵称：" << tempPointer1->getName() << endl;
            cout << "是否邀请？（1为是，0为否）" << endl;
            string isAdd = Interact::inputAllInt(1, 0, 1);
            if (isAdd == "1")
            {
                continueFlag = true;
            }
        }
    }

    // 第二部分确定要邀请的群
    if (continueFlag)
    {

        cout << "--------------------------------------------------------------" << endl;
        cout << "请输入想添加群的Id：" << endl;
        Id = Interact::inputAllInt(6);
        WeiboGroup* tempPointer2 = this->WeiboDataM.getGroupById(Id);


        if (tempPointer2 == nullptr)
        {
            cout << "该Id群不存在" << endl;
        }
        else
        {
            tempPointer2->readGroupFromFile();
            if (tempPointer2->searchMemberById(tempPointer1->getId()) != -1)
            {
                cout << "对方已加入该群，无需邀请" << endl;
            }
            else if (tempPointer2->searchMemberById(this->WeiboDataM.getUsingAccountId()) == -1)
            {
                cout << "您尚未加入该群，无权限邀请" << endl;
            }
            else
            {
                cout << "目标群信息为：" << endl;
                cout << "昵称：" << tempPointer2->getName() << endl;
                cout << "再次确定是否邀请？（1为是，0为否）" << endl;
                string isAdd = Interact::inputAllInt(1, 0, 1);
                if (isAdd == "1")
                {
                    tempPointer1->joinGroupToList(tempPointer2->getName(), tempPointer2->getId());
                    tempPointer1->saveAccountAsFile();

                    tempPointer2->addMemberToList(tempPointer1->getName(), tempPointer1->getId());
                    tempPointer2->saveGroupAsFile();
                    cout << "加入成功！" << endl;
                }
            }
            delete tempPointer2;
            tempPointer2 = nullptr;
        }
    }



    delete tempPointer1;
    tempPointer1 = nullptr;



    return result;
}

// 这是删除Weibo群的界面
std::string WeiboInteract::delWeiboGroupPage()
{
    string result = "";
    string Id = "";


    cout << "--------------------------------------------------------------" << endl;
    cout << "请输入想删除的群的Id：" << endl;
    Id = Interact::inputAllInt(6);
    WeiboGroup* tempPointer = this->WeiboDataM.getGroupById(Id);


    if (tempPointer == nullptr)
    {
        cout << "您不能删除没有加入的群" << endl;
    }
    else
    {
        tempPointer->readGroupFromFile();
        if (tempPointer->searchMemberById(this->WeiboDataM.getUsingAccountId()) != 0)
        {
            cout << "您无权删除该群" << endl;
        }
        else
        {
            cout << "群名称：" << tempPointer->getName() << endl;
            cout << "群成员Id    群成员昵称" << endl;
            tempPointer->showMemberList();
            cout << "是否删除？（1为是，0为否）" << endl;
            string isAdd = Interact::inputAllInt(1, 0, 1);
            if (isAdd == "1")
            {
                this->WeiboDataM.exitGroup(tempPointer->getId());
                this->WeiboDataM.delGroupId(tempPointer->getId());
                tempPointer->delFromAllMember();

                cout << "删除成功！" << endl;
            }
            delete tempPointer;
            tempPointer = nullptr;
        }
    }



    return result;
}

// 这是Weibo用户设置界面
std::string WeiboInteract::showWeiboSettingPage()
{


    string result = "";
    bool exitFlag = false;
    string choice = "";


    while (!exitFlag)
    {
        if (choice == "")
        {
            cout << "--------------------------------------------------------------" << endl;
            cout << "请输入您想更改信息前的序号：" << endl;
            cout << "1、账户昵称：" << this->WeiboDataM.getUsingAccountName() << endl;
            cout << "2、账户Id：" << this->WeiboDataM.getUsingAccountId() << endl;
            cout << "3、账户密码：" << this->WeiboDataM.getUsingAccountPwd() << endl;
            cout << "4、生日：" << this->WeiboDataM.getUsingAccountBirth() << endl;
            cout << "5、地址：" << this->WeiboDataM.getUsingAccountLocate() << endl;
            cout << "6、关联Wechat账号Id：" << this->WeiboDataM.getUsingAccountBindWechatAccountId() << endl;
            cout << "7、关联QQ账号Id：" << this->WeiboDataM.getUsingAccountBindQQAccountId() << endl;
            cout << "8、返回" << endl;
            choice = Interact::inputAllInt(1, 1, 8);
        }


        // 根据输入来走后续流程
        switch (stoi(choice))
        {
        case 1:
            cout << "请输入您想更改成的昵称：" << endl;
            this->WeiboDataM.setUsingAccountName(Interact::inputEWordAndInt(10));
            this->WeiboDataM.saveAccountData();
            choice = "";
            break;
        case 2:
            cout << "WeiboId不可更改！" << endl;
            choice = "";
            break;
        case 3:
            cout << "请输入您想更改成的密码：" << endl;
            this->WeiboDataM.setUsingAccountPwd(Interact::inputEWordAndInt(10));
            this->WeiboDataM.saveAccountData();
            choice = "";
            break;
        case 4:
            cout << "请输入您想更改成的生日：" << endl;
            this->WeiboDataM.setUsingAccountBirth(Interact::inputAllInt(8));
            this->WeiboDataM.saveAccountData();
            choice = "";
            break;
        case 5:
            cout << "请输入您想更改成的地址：" << endl;
            this->WeiboDataM.setUsingAccountLocate(Interact::inputEWordAndInt(20));
            this->WeiboDataM.saveAccountData();
            choice = "";
            break;
        case 6:
        {
            cout << "请输入您想绑定的Wechat账号Id：" << endl;
            string tempAccountId = Interact::inputAllInt(6);
            WechatDataManage m;
            WechatAccount* tempPointer = m.getAccountById(tempAccountId);
            if (tempPointer == nullptr)
            {
                cout << "不存在该Id的Wechat用户" << endl;
            }
            else
            {
                this->WeiboDataM.setUsingAccountBindQQAccountId(tempAccountId);
                tempPointer->setBindWeiboAccountId(this->WeiboDataM.getUsingAccountId());
                tempPointer->saveAccountAsFile();
                this->WeiboDataM.saveAccountData();
                cout << "绑定成功" << endl;
            }
            choice = "";
            break;
        }
        case 7:
            cout << "绑定后的QQ账号不可更改：" << endl;
            choice = "";
            break;
        case 8:
            exitFlag = true;
            break;
        default:
            cout << "您所选择的序号尚未安排服务，请重新选择" << endl;
        }
        Interact::pauseAndClearScreen();
    }
    return result;

}

