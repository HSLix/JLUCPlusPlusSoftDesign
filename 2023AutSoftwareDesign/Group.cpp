#define _CRT_SECURE_NO_WARNINGS 1

#include <fstream>
#include <string>

#include "Account.h"
#include "Group.h"


using namespace std;

//初始化QQ群文件储存目录
std::string QQGroup::groupFileAddress = ".\\QQ\\Group\\";


// 将群信息保存为文件
void QQGroup::saveGroupAsFile()
{
    std::ofstream fout;

    // 先是保存群自身信息
    fout.open(this->thisGroupSelfFileAddress, std::ios::out);
    fout << this->getId() << std::endl;
    fout << this->getName() << std::endl;
    fout.close();

    // 然后是保存群成员信息
    fout.open(this->thisGroupMemberFileAddress, std::ios::out);
    for (std::list<QQGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        fout << it->getId() << std::endl;
        fout << it->getName() << std::endl;
    }
    fout.close();

}

// 从文件中读取群信息
bool QQGroup::readGroupFromFile()
{
    std::ifstream fin;
    std::string tempStr1, tempStr2;
    bool result = true;

    // 先是读取群自身信息
    fin.open(this->thisGroupSelfFileAddress, std::ios::in);

    if (!fin.is_open() && result)
    {
        std::cout << "File open error  ----  " << this->thisGroupSelfFileAddress;
        result = false;
    }
    else
    {
        getline(fin, tempStr1);
        this->setId(tempStr1);
        getline(fin, tempStr1);
        this->setName(tempStr1);
        fin.close();
    }

    // 然后是读取群成员信息
    fin.open(this->thisGroupMemberFileAddress, std::ios::in);

    if (!fin.is_open() && result)
    {
        std::cout << "File open error  ----  " << this->thisGroupMemberFileAddress;
        result = false;
    }
    else
    {
        while (getline(fin, tempStr1))
        {
            getline(fin, tempStr2);
            this->addMemberToList(tempStr2, tempStr1);
        }
        fin.close();
    }




    return result;
}

// 创建或重置文件
void QQGroup::createOrResetFile(std::string ID)
{
    std::ofstream fout;

    std::string thisGroupSelfFileAddress = QQGroup::groupFileAddress + ID + "Self" + ".txt";

    std::string thisGroupMemberFileAddress = QQGroup::groupFileAddress + ID + "Member" + ".txt";


    // 先是重置群自身信息
    fout.open(thisGroupSelfFileAddress, std::ios::out);
    fout.close();

    // 再重置群成员信息
    fout.open(thisGroupMemberFileAddress, std::ios::out);
    fout.close();

}


// QQ群添加群成员
void QQGroup::addMemberToList(std::string memberName, std::string memberId) {
    if (this->searchMemberById(memberId) == -1)
    {
        QQGroupMember* tempGroupMember = new QQGroupMember(memberName, memberId);
        this->myGroupMember.push_back(*tempGroupMember);
    }
}


// QQ群输出群成员列表
void QQGroup::showMemberList() {
    for (std::list<QQGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        std::cout << it->getId() << "    " << it->getName() << std::endl;
    }
}


// 遍历群成员并根据名字查找成员，返回其索引，无则返回-1
int QQGroup::searchMemberByName(std::string memberName)
{
    int index = -1;
    int tempNum = 0;
    for (std::list<QQGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        if (memberName == it->getName()) {
            index = tempNum;
            break;
        }
        tempNum += 1;
    }
    return index;
}


// 根据name删除好友，返回是否成功删除
bool QQGroup::delMemberByName(std::string QQName)
{
    bool result = false;
    int index = this->searchMemberByName(QQName);
    if (index != -1)
    {
        std::list<QQGroupMember>::iterator it = this->myGroupMember.begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        this->myGroupMember.erase(it);
        result = true;
    }
    return result;
}


// 根据Id删除好友，返回是否成功删除
bool QQGroup::delMemberById(std::string Id)
{
    bool result = false;
    int index = this->searchMemberById(Id);
    if (index != -1)
    {
        std::list<QQGroupMember>::iterator it = this->myGroupMember.begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        this->myGroupMember.erase(it);
        result = true;
    }
    return result;
}



// 根据Id查找群成员，返回其索引
int QQGroup::searchMemberById(std::string Id)
{
    int index = -1;
    int tempNum = 0;
    for (std::list<QQGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        if (Id == it->getId()) {
            index = tempNum;
            break;
        }
        tempNum += 1;
    }
    return index;
}

// 将成员内部存储的文件中剔除自己
void QQGroup::delFromAllMember()
{
    int tempNum = 0;
    QQAccount* tempPointer;
    for (std::list<QQGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        tempPointer = new QQAccount(it->getId());
        tempPointer->readAccountFromFile();
        tempPointer->delJoinedGroupById(this->getId());
        tempPointer->saveAccountAsFile();
        delete tempPointer;
        tempPointer = nullptr;

    }
    this->createOrResetFile(this->getId());
    this->readGroupFromFile();
    
}



//初始化Wechat群文件储存目录
std::string WechatGroup::groupFileAddress = ".\\Wechat\\Group\\";


// 将群信息保存为文件
void WechatGroup::saveGroupAsFile()
{
    std::ofstream fout;

    // 先是保存群自身信息
    fout.open(this->thisGroupSelfFileAddress, std::ios::out);
    fout << this->getId() << std::endl;
    fout << this->getName() << std::endl;
    fout.close();

    // 然后是保存群成员信息
    fout.open(this->thisGroupMemberFileAddress, std::ios::out);
    for (std::list<WechatGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        fout << it->getId() << std::endl;
        fout << it->getName() << std::endl;
    }
    fout.close();

}

// 从文件中读取群信息
bool WechatGroup::readGroupFromFile()
{
    std::ifstream fin;
    std::string tempStr1, tempStr2;
    bool result = true;

    // 先是读取群自身信息
    fin.open(this->thisGroupSelfFileAddress, std::ios::in);

    if (!fin.is_open() && result)
    {
        std::cout << "File open error  ----  " << this->thisGroupSelfFileAddress;
        result = false;
    }
    else
    {
        getline(fin, tempStr1);
        this->setId(tempStr1);
        getline(fin, tempStr1);
        this->setName(tempStr1);
        fin.close();
    }

    // 然后是读取群成员信息
    fin.open(this->thisGroupMemberFileAddress, std::ios::in);

    if (!fin.is_open() && result)
    {
        std::cout << "File open error  ----  " << this->thisGroupMemberFileAddress;
        result = false;
    }
    else
    {
        while (getline(fin, tempStr1))
        {
            getline(fin, tempStr2);
            this->addMemberToList(tempStr2, tempStr1);
        }
        fin.close();
    }




    return result;
}

// 创建或重置文件
void WechatGroup::createOrResetFile(std::string ID)
{
    std::ofstream fout;

    std::string thisGroupSelfFileAddress = WechatGroup::groupFileAddress + ID + "Self" + ".txt";

    std::string thisGroupMemberFileAddress = WechatGroup::groupFileAddress + ID + "Member" + ".txt";


    // 先是重置群自身信息
    fout.open(thisGroupSelfFileAddress, std::ios::out);
    fout.close();

    // 再重置群成员信息
    fout.open(thisGroupMemberFileAddress, std::ios::out);
    fout.close();

}


// Wechat群添加群成员
void WechatGroup::addMemberToList(std::string memberName, std::string memberId) {
    if (this->searchMemberById(memberId) == -1)
    {
        WechatGroupMember* tempGroupMember = new WechatGroupMember(memberName, memberId);
        this->myGroupMember.push_back(*tempGroupMember);
    }
}


// Wechat群输出群成员列表
void WechatGroup::showMemberList() {
    for (std::list<WechatGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        std::cout << it->getId() << "    " << it->getName() << std::endl;
    }
}


// 遍历群成员并根据名字查找成员，返回其索引，无则返回-1
int WechatGroup::searchMemberByName(std::string memberName)
{
    int index = -1;
    int tempNum = 0;
    for (std::list<WechatGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        if (memberName == it->getName()) {
            index = tempNum;
            break;
        }
        tempNum += 1;
    }
    return index;
}


// 根据name删除好友，返回是否成功删除
bool WechatGroup::delMemberByName(std::string WechatName)
{
    bool result = false;
    int index = this->searchMemberByName(WechatName);
    if (index != -1)
    {
        std::list<WechatGroupMember>::iterator it = this->myGroupMember.begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        this->myGroupMember.erase(it);
        result = true;
    }
    return result;
}


// 根据Id删除好友，返回是否成功删除
bool WechatGroup::delMemberById(std::string Id)
{
    bool result = false;
    int index = this->searchMemberById(Id);
    if (index != -1)
    {
        std::list<WechatGroupMember>::iterator it = this->myGroupMember.begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        this->myGroupMember.erase(it);
        result = true;
    }
    return result;
}



// 根据Id查找群成员，返回其索引
int WechatGroup::searchMemberById(std::string Id)
{
    int index = -1;
    int tempNum = 0;
    for (std::list<WechatGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        if (Id == it->getId()) {
            index = tempNum;
            break;
        }
        tempNum += 1;
    }
    return index;
}

// 将成员内部存储的文件中剔除自己
void WechatGroup::delFromAllMember()
{
    int tempNum = 0;
    WechatAccount* tempPointer;
    for (std::list<WechatGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        tempPointer = new WechatAccount(it->getId());
        tempPointer->readAccountFromFile();
        tempPointer->delJoinedGroupById(this->getId());
        tempPointer->saveAccountAsFile();
        delete tempPointer;
        tempPointer = nullptr;

    }
    this->createOrResetFile(this->getId());
    this->readGroupFromFile();

}



//初始化Weibo群文件储存目录
std::string WeiboGroup::groupFileAddress = ".\\Weibo\\Group\\";


// 将群信息保存为文件
void WeiboGroup::saveGroupAsFile()
{
    std::ofstream fout;

    // 先是保存群自身信息
    fout.open(this->thisGroupSelfFileAddress, std::ios::out);
    fout << this->getId() << std::endl;
    fout << this->getName() << std::endl;
    fout.close();

    // 然后是保存群成员信息
    fout.open(this->thisGroupMemberFileAddress, std::ios::out);
    for (std::list<WeiboGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        fout << it->getId() << std::endl;
        fout << it->getName() << std::endl;
    }
    fout.close();

}

// 从文件中读取群信息
bool WeiboGroup::readGroupFromFile()
{
    std::ifstream fin;
    std::string tempStr1, tempStr2;
    bool result = true;

    // 先是读取群自身信息
    fin.open(this->thisGroupSelfFileAddress, std::ios::in);

    if (!fin.is_open() && result)
    {
        std::cout << "File open error  ----  " << this->thisGroupSelfFileAddress;
        result = false;
    }
    else
    {
        getline(fin, tempStr1);
        this->setId(tempStr1);
        getline(fin, tempStr1);
        this->setName(tempStr1);
        fin.close();
    }

    // 然后是读取群成员信息
    fin.open(this->thisGroupMemberFileAddress, std::ios::in);

    if (!fin.is_open() && result)
    {
        std::cout << "File open error  ----  " << this->thisGroupMemberFileAddress;
        result = false;
    }
    else
    {
        while (getline(fin, tempStr1))
        {
            getline(fin, tempStr2);
            this->addMemberToList(tempStr2, tempStr1);
        }
        fin.close();
    }




    return result;
}

// 创建或重置文件
void WeiboGroup::createOrResetFile(std::string ID)
{
    std::ofstream fout;

    std::string thisGroupSelfFileAddress = WeiboGroup::groupFileAddress + ID + "Self" + ".txt";

    std::string thisGroupMemberFileAddress = WeiboGroup::groupFileAddress + ID + "Member" + ".txt";


    // 先是重置群自身信息
    fout.open(thisGroupSelfFileAddress, std::ios::out);
    fout.close();

    // 再重置群成员信息
    fout.open(thisGroupMemberFileAddress, std::ios::out);
    fout.close();

}


// Weibo群添加群成员
void WeiboGroup::addMemberToList(std::string memberName, std::string memberId) {
    if (this->searchMemberById(memberId) == -1)
    {
        WeiboGroupMember* tempGroupMember = new WeiboGroupMember(memberName, memberId);
        this->myGroupMember.push_back(*tempGroupMember);
    }
}


// Weibo群输出群成员列表
void WeiboGroup::showMemberList() {
    for (std::list<WeiboGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        std::cout << it->getId() << "    " << it->getName() << std::endl;
    }
}


// 遍历群成员并根据名字查找成员，返回其索引，无则返回-1
int WeiboGroup::searchMemberByName(std::string memberName)
{
    int index = -1;
    int tempNum = 0;
    for (std::list<WeiboGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        if (memberName == it->getName()) {
            index = tempNum;
            break;
        }
        tempNum += 1;
    }
    return index;
}


// 根据name删除好友，返回是否成功删除
bool WeiboGroup::delMemberByName(std::string WeiboName)
{
    bool result = false;
    int index = this->searchMemberByName(WeiboName);
    if (index != -1)
    {
        std::list<WeiboGroupMember>::iterator it = this->myGroupMember.begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        this->myGroupMember.erase(it);
        result = true;
    }
    return result;
}


// 根据Id删除好友，返回是否成功删除
bool WeiboGroup::delMemberById(std::string Id)
{
    bool result = false;
    int index = this->searchMemberById(Id);
    if (index != -1)
    {
        std::list<WeiboGroupMember>::iterator it = this->myGroupMember.begin();
        for (int i = 0; i < index; i++)
        {
            it++;
        }
        this->myGroupMember.erase(it);
        result = true;
    }
    return result;
}



// 根据Id查找群成员，返回其索引
int WeiboGroup::searchMemberById(std::string Id)
{
    int index = -1;
    int tempNum = 0;
    for (std::list<WeiboGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        if (Id == it->getId()) {
            index = tempNum;
            break;
        }
        tempNum += 1;
    }
    return index;
}

// 将成员内部存储的文件中剔除自己
void WeiboGroup::delFromAllMember()
{
    int tempNum = 0;
    WeiboAccount* tempPointer;
    for (std::list<WeiboGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        tempPointer = new WeiboAccount(it->getId());
        tempPointer->readAccountFromFile();
        tempPointer->delJoinedGroupById(this->getId());
        tempPointer->saveAccountAsFile();
        delete tempPointer;
        tempPointer = nullptr;

    }
    this->createOrResetFile(this->getId());
    this->readGroupFromFile();

}


