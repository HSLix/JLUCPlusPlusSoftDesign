#define _CRT_SECURE_NO_WARNINGS 1

#include"Group.h"


// QQ群添加群成员
void QQGroup::addMemberToList(std::string memberName, std::string memberId) {
    QQGroupMember *tempGroupMember = new QQGroupMember(memberName, memberId);
    this->myGroupMember.push_back(*tempGroupMember);
}


// QQ群输出群成员列表
void QQGroup::showMemberList() {
    for (std::list<QQGroupMember>::iterator it = this->myGroupMember.begin(); it != myGroupMember.end(); ++it) {
        std::cout << it->getName() << std::endl;
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

