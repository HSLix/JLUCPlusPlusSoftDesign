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
        return groupName;
    }

    std::string getId() {
        return groupId;
    }


protected:
	std::string groupName;
    std::string groupId;
    


};

class QQGroup : public baseGroup
{
public:
    QQGroup(std::string name, std::string id) {
        groupName = name;
        groupId = id;
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


    // 根据Id删除好友，返回是否成功删除
    bool delMemberById(std::string Id);




protected:
    std::list<QQGroupMember> myGroupMember;

};


