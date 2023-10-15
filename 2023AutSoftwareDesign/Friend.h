#pragma once

#include <iostream>


class baseFriend
{
public:
    baseFriend(){
        mId = "";
        mName = "";
    }

    baseFriend(std::string Name, std::string Id) {
        mId = Id;
        mName = Name;
    }

    virtual ~baseFriend() {};

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


class QQFriend : public baseFriend
{
public:
    QQFriend(std::string Name, std::string Id) {
        mId = Id;
        mName = Name;
    }

    ~QQFriend() {};


};



class WechatFriend : public baseFriend
{
public:
    WechatFriend(std::string Name, std::string Id) {
        mId = Id;
        mName = Name;
    }

    ~WechatFriend() {};


};


class WeiboFriend : public baseFriend
{
public:
    WeiboFriend(std::string Name, std::string Id) {
        mId = Id;
        mName = Name;
    }

    ~WeiboFriend() {};


};


