#pragma once

#include <iostream>


class baseJoinedGroup
{
public:
    baseJoinedGroup() {
        mId = "";
        mName = "";
    }

    baseJoinedGroup(std::string Name, std::string Id) {
        mId = Id;
        mName = Name;
    }

    virtual ~baseJoinedGroup() {};

    std::string getId() {
        return mId;
    }

    std::string getName() {
        return mName;
    }


protected:
    //id考虑到微信号有英文混合,故采用string类型
    std::string mId;
    std::string mName;
};


class QQJoinedGroup : public baseJoinedGroup
{
public:
    QQJoinedGroup(std::string Name, std::string Id) {
        mId = Id;
        mName = Name;
    }

    ~QQJoinedGroup() {};


};



