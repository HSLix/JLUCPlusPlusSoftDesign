#define _CRT_SECURE_NO_WARNINGS 1

#include "Account.h"
#include <string>
#include "Friend.h"
#include <fstream>
#include "JoinedGroup.h"



// 基本用户功能，简单核对密码
bool baseAccount::checkPwd(std::string inputPwd){
    bool result = false;
    if(inputPwd == mPwd){
        result = true;
    }
    return result;
}

// 创建或重置文件
void QQAccount::createOrResetFile(std::string ID)
{
    std::ofstream fout;
    
    std::string thisAccountSelfFileAddress = QQAccount::accountFileAddress + ID + "Self" + ".txt";

    std::string thisAccountFriendFileAddress = QQAccount::accountFileAddress + ID + "Friend" + ".txt";

    std::string thisAccountGroupFileAddress = QQAccount::accountFileAddress + ID + "Group" + ".txt";

    // 先是重置个人信息
    fout.open(thisAccountSelfFileAddress, std::ios::out);
    fout.close();

    fout.open(thisAccountFriendFileAddress, std::ios::out);
    fout.close();

    fout.open(thisAccountGroupFileAddress, std::ios::out);
    fout.close();
}


//初始化QQ用户文件储存目录
std::string QQAccount::accountFileAddress = ".\\QQ\\Account\\";

// QQ添加好友
bool QQAccount::addFriendToList(std::string QQName, std::string QQId) {
    bool result = false;
    if (this->searchFriendById(QQId) == -1)
    {
        QQFriend *tempFriend = new QQFriend(QQName, QQId);
        this->myFriends.push_back(*tempFriend);
        result = true;
    }
    
    return result;
}


// QQ输出好友列表
void QQAccount::showFriendList() {
    for (std::list<QQFriend>::iterator it = this->myFriends.begin(); it != myFriends.end(); ++it) {
        std::cout << it->getId() << " " << it->getName() << std::endl;
    }
}



// 遍历好友列表并根据Id查找好友，返回其索引
int QQAccount::searchFriendById(std::string QQId)
{
    int index = -1;
    int tempNum = 0;
    for (std::list<QQFriend>::iterator it = this->myFriends.begin(); it != myFriends.end(); ++it) {
        if (QQId == it->getId()) {
            index = tempNum;
            break;
        }
        tempNum += 1;
    }
    return index;
}


// 遍历好友列表并根据名字查找好友，返回其索引
int QQAccount::searchFriendByName(std::string QQName)
{
    int index = -1;
    int tempNum = 0;
    for (std::list<QQFriend>::iterator it = this->myFriends.begin(); it != myFriends.end(); ++it) {
        if (QQName == it->getName()) {
            index = tempNum;
            break;
        }
        tempNum += 1;
    }
    return index;
}


// 根据Id删除好友，返回是否成功删除
bool QQAccount::delFriendById(std::string QQId)
{
    bool result = false;
    int index = this->searchFriendById(QQId);
    if (index != -1)
    {
        std::list<QQFriend>::iterator it = this->myFriends.begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        this->myFriends.erase(it);
        result = true;
    }
    return result;
}


// 根据name删除好友，返回是否成功删除
bool QQAccount::delFriendByName(std::string QQName)
{
    bool result = false;
    int index = this->searchFriendByName(QQName);
    if (index != -1)
    {
        std::list<QQFriend>::iterator it = this->myFriends.begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        this->myFriends.erase(it);
        result = true;
    }
    return result;
}


// 将用户信息保存为文件
void QQAccount::saveAccountAsFile()
{
    std::ofstream fout;

    // 先是保存个人信息
    fout.open(this->thisAccountSelfFileAddress, std::ios::out);
    fout << this->getId() << std::endl;
    fout << this->getName() << std::endl;
    fout << this->getPwd() << std::endl;
    fout.close();

    // 然后是保存好友信息
    fout.open(this->thisAccountFriendFileAddress, std::ios::out);
    for (std::list<QQFriend>::iterator it = this->myFriends.begin(); it != myFriends.end(); ++it) {
        fout << it->getId() << std::endl;
        fout << it->getName() << std::endl;
    }
    fout.close();

    // 接着是保存群信息
    fout.open(this->thisAccountGroupFileAddress, std::ios::out);
    for (std::list<QQJoinedGroup>::iterator it = this->myGroups.begin(); it != myGroups.end(); ++it) {
        fout << it->getId() << std::endl;
        fout << it->getName() << std::endl;
    }
    fout.close();

}

// 从文件中读取用户信息
bool QQAccount::readAccountFromFile()
{
    std::ifstream fin;
    std::string tempStr1, tempStr2;
    bool result = true;

    // 先是读取个人信息
    fin.open(this->thisAccountSelfFileAddress, std::ios::in);

    if (!fin.is_open() && result)
    {
        std::cout << "File open error  ----  " << this->thisAccountSelfFileAddress;
        result = false;
    }
    else
    {
        getline(fin, tempStr1);
        this->setId(tempStr1);
        getline(fin, tempStr1);
        this->setName(tempStr1);
        getline(fin, tempStr1);
        this->setPwd(tempStr1);
        fin.close();
    }

    // 然后是读取好友信息
    fin.open(this->thisAccountFriendFileAddress, std::ios::in);

    if (!fin.is_open() && result)
    {
        std::cout << "File open error  ----  " << this->thisAccountFriendFileAddress;
        result = false;
    }
    else
    {
        while (getline(fin, tempStr1))
        {
            getline(fin, tempStr2);
            this->addFriendToList(tempStr2, tempStr1);
        }
        fin.close();
    }

    // 然后是读取群信息
    fin.open(this->thisAccountGroupFileAddress, std::ios::in);

    if (!fin.is_open() && result)
    {
        std::cout << "File open error  ----  " << this->thisAccountGroupFileAddress;
        result = false;
    }
    else
    {
        while (getline(fin, tempStr1))
        {
            getline(fin, tempStr2);
            this->joinGroupToList(tempStr2, tempStr1);
        }
        fin.close();
    }
    
    
    return result;
}

// 加入群
bool QQAccount::joinGroupToList(std::string Name, std::string Id)
{
    bool result = false;
    if (this->searchJoinedGroupById(Id) == -1)
    {
        QQJoinedGroup* tempJoinedGroup = new QQJoinedGroup(Name, Id);
        this->myGroups.push_back(*tempJoinedGroup);
        result = true;
    }

    return result;
}

// 遍历并输出已加入群列表，无返回
void QQAccount::showJoinedGroupList()
{
    for (std::list<QQJoinedGroup>::iterator it = this->myGroups.begin(); it != myGroups.end(); ++it) {
        std::cout << it->getId() << " " << it->getName() << std::endl;
    }
}

// 根据Id查找已加入的群，返回其索引
int QQAccount::searchJoinedGroupById(std::string Id)
{
    int index = -1;
    int tempNum = 0;
    for (std::list<QQJoinedGroup>::iterator it = this->myGroups.begin(); it != myGroups.end(); ++it) {
        if (Id == it->getId()) {
            index = tempNum;
            break;
        }
        tempNum += 1;
    }
    return index;
}

// 根据Id退出已加入的群，返回是否成功删除
bool QQAccount::delJoinedGroupById(std::string Id)
{
    bool result = false;
    int index = this->searchJoinedGroupById(Id);
    if (index != -1)
    {
        std::list<QQJoinedGroup>::iterator it = this->myGroups.begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        this->myGroups.erase(it);
        result = true;
    }
    return result;
}

