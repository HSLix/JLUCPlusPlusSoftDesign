#pragma once

#include<iostream>


class baseGroupMember
{
public:
    baseGroupMember() {
        mName = "";
        mId = "";
    }

    virtual ~baseGroupMember() {};


    std::string getName() {
        return mName;
    }

    std::string getId() {
        return mId;
    }



protected:
    std::string mName;
    std::string mId;
};


class QQGroupMember : public baseGroupMember
{
public:
    QQGroupMember(std::string Name, std::string Id) {
        mName = Name;
        mId = Id;
    }

    ~QQGroupMember() {};


private:

};

