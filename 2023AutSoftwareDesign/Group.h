#pragma once

#include <iostream>
#include "GroupMember.h"
#include <list>


class baseGroup 
{
public:
    baseGroup() {
        groupName = "";
        groupId = "";
    }

    virtual ~baseGroup() {};


    std::string getName() {
        return this->groupName;
    }

    std::string getId() {
        return this->groupId;
    }

    void setName(std::string Name) {
        this->groupName = Name;
    }

    void setId(std::string Id) {
        this->groupId = Id;
    }


protected:
	std::string groupName;
    std::string groupId;
    
    

};

class QQGroup : public baseGroup
{
public:
    QQGroup(std::string ID) {

        thisGroupSelfFileAddress = QQGroup::groupFileAddress + ID + "Self" + ".txt";

        thisGroupMemberFileAddress = QQGroup::groupFileAddress + ID + "Member" + ".txt";
    }

    virtual ~QQGroup() {};

    // QQ群添加群成员
    void addMemberToList(std::string memberName, std::string memberId);

    // QQ群输出群成员列表
    void showMemberList();

    // 根据name删除群成员，返回是否成功删除
    bool delMemberByName(std::string memberName);

    // 遍历群成员并根据名字查找成员，返回其索引，无则返回-1
    int searchMemberByName(std::string memberName);

    // 根据Id查找群成员，返回其索引
    int searchMemberById(std::string Id);


    // 根据Id删除群成员，返回是否成功删除
    bool delMemberById(std::string Id);

    // 将用户信息保存为文件
    void saveGroupAsFile();

    // 从文件中读取用户信息
    bool readGroupFromFile();

    // 创建或重置文件
    static void createOrResetFile(std::string Id);

    // 将成员内部存储的文件中剔除自己
    void delFromAllMember();


protected:
    // QQ群成员链表
    std::list<QQGroupMember> myGroupMember;

    // QQ群文件储存的目录
    static std::string groupFileAddress;

    // QQ群自身信息的文件
    std::string thisGroupSelfFileAddress;

    // QQ群成员信息的文件
    std::string thisGroupMemberFileAddress;
};


class WechatGroup : public baseGroup
{
public:
    WechatGroup(std::string ID) {

        thisGroupSelfFileAddress = WechatGroup::groupFileAddress + ID + "Self" + ".txt";

        thisGroupMemberFileAddress = WechatGroup::groupFileAddress + ID + "Member" + ".txt";
    }

    virtual ~WechatGroup() {};

    // Wechat群添加群成员
    void addMemberToList(std::string memberName, std::string memberId);

    // Wechat群输出群成员列表
    void showMemberList();

    // 根据name删除群成员，返回是否成功删除
    bool delMemberByName(std::string memberName);

    // 遍历群成员并根据名字查找成员，返回其索引，无则返回-1
    int searchMemberByName(std::string memberName);

    // 根据Id查找群成员，返回其索引
    int searchMemberById(std::string Id);


    // 根据Id删除群成员，返回是否成功删除
    bool delMemberById(std::string Id);

    // 将用户信息保存为文件
    void saveGroupAsFile();

    // 从文件中读取用户信息
    bool readGroupFromFile();

    // 创建或重置文件
    static void createOrResetFile(std::string Id);

    // 将成员内部存储的文件中剔除自己
    void delFromAllMember();


protected:
    // Wechat群成员链表
    std::list<WechatGroupMember> myGroupMember;

    // Wechat群文件储存的目录
    static std::string groupFileAddress;

    // Wechat群自身信息的文件
    std::string thisGroupSelfFileAddress;

    // Wechat群成员信息的文件
    std::string thisGroupMemberFileAddress;
};


class WeiboGroup : public baseGroup
{
public:
    WeiboGroup(std::string ID) {

        thisGroupSelfFileAddress = WeiboGroup::groupFileAddress + ID + "Self" + ".txt";

        thisGroupMemberFileAddress = WeiboGroup::groupFileAddress + ID + "Member" + ".txt";
    }

    virtual ~WeiboGroup() {};

    // Weibo群添加群成员
    void addMemberToList(std::string memberName, std::string memberId);

    // Weibo群输出群成员列表
    void showMemberList();

    // 根据name删除群成员，返回是否成功删除
    bool delMemberByName(std::string memberName);

    // 遍历群成员并根据名字查找成员，返回其索引，无则返回-1
    int searchMemberByName(std::string memberName);

    // 根据Id查找群成员，返回其索引
    int searchMemberById(std::string Id);


    // 根据Id删除群成员，返回是否成功删除
    bool delMemberById(std::string Id);

    // 将用户信息保存为文件
    void saveGroupAsFile();

    // 从文件中读取用户信息
    bool readGroupFromFile();

    // 创建或重置文件
    static void createOrResetFile(std::string Id);

    // 将成员内部存储的文件中剔除自己
    void delFromAllMember();


protected:
    // Weibo群成员链表
    std::list<WeiboGroupMember> myGroupMember;

    // Weibo群文件储存的目录
    static std::string groupFileAddress;

    // Weibo群自身信息的文件
    std::string thisGroupSelfFileAddress;

    // Weibo群成员信息的文件
    std::string thisGroupMemberFileAddress;
};


