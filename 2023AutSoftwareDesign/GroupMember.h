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


class WechatGroupMember : public baseGroupMember
{
public:
    WechatGroupMember(std::string Name, std::string Id) {
        mName = Name;
        mId = Id;
    }

    ~WechatGroupMember() {};


private:

};


class WeiboGroupMember : public baseGroupMember
{
public:
    WeiboGroupMember(std::string Name, std::string Id) {
        mName = Name;
        mId = Id;
    }

    ~WeiboGroupMember() {};


private:

};

