#ifndef ACCOUNTH
#define ACCOUNTH

#include <string>
#include <list>
#include "Friend.h"
#include "Group.h"
#include "JoinedGroup.h"


class baseAccount
{
public:
    //构造函数
    baseAccount(){
        mId = "";
        mPwd = "";
        mName = "";
    }

    // 简单核对密码是否一样
    bool checkPwd(std::string inputPwd);

    // 析构函数
    ~baseAccount() {}

    // 返回Id
    std::string getId() {
        return this->mId;
    }

    // 返回名字
    std::string getName() {
        return this->mName;
    }

    // 返回密码
    std::string getPwd() {
        return this->mPwd;
    }

    // 返回生日
    std::string getBirth() {
        return this->mBirth;
    }

    // 返回地址
    std::string getLocate() {
        return this->mLocate;
    }

    // 修改Id
    void setId(std::string Id)
    {
        this->mId = Id;
    }

    // 修改Name
    void setName(std::string Name)
    {
        this->mName = Name;
    }

    // 修改Pwd
    void setPwd(std::string Pwd)
    {
        this->mPwd = Pwd;
    }

    // 修改Birth
    void setBirth(std::string Birth)
    {
        this->mBirth = Birth;
    }

    // 修改Locate
    void setLocate(std::string Locate)
    {
        this->mLocate = Locate;
    }


    // 将用户信息保存为文件
    virtual void saveAccountAsFile() = 0;

    // 从文件中读取用户信息
    virtual bool readAccountFromFile() = 0;




protected:
    //id考虑到微信号有英文混合,故采用string类型
    std::string mId;
    std::string mPwd;
    std::string mName;
    std::string mBirth;
    std::string mLocate;
};


class QQAccount : public baseAccount
{
public:
    // 构造函数
    QQAccount(std::string ID){

        thisAccountSelfFileAddress = QQAccount::accountFileAddress + ID + "Self" + ".txt";

        thisAccountFriendFileAddress = QQAccount::accountFileAddress + ID + "Friend" + ".txt";
    
        thisAccountGroupFileAddress = QQAccount::accountFileAddress + ID + "Group" + ".txt";

        this->readAccountFromFile();
    }



    // 添加好友至好友列表，返回是否成功添加
    bool addFriendToList(std::string QQName, std::string QQId);

    // 遍历并输出好友列表，无返回
    void showFriendList();

    // 根据Id查找好友，返回其索引
    int searchFriendById(std::string QQId);

    // 根据名字查找好友，返回其索引
    int searchFriendByName(std::string QQName);

    // 根据Id删除好友，返回是否成功删除
    bool delFriendById(std::string QQId);

    // 根据name删除好友，返回是否成功删除
    bool delFriendByName(std::string QQName);


    // 将用户信息保存为文件
    void saveAccountAsFile();

    // 从文件中读取用户信息
    bool readAccountFromFile();
    
    // 创建或重置文件
    static void createOrResetFile(std::string Id);

    // 加入群
    bool joinGroupToList(std::string Name, std::string Id);

    // 遍历并输出已加入群列表，无返回
    void showJoinedGroupList();

    // 根据Id查找已加入的群，返回其索引
    int searchJoinedGroupById(std::string Id);

    // 根据Id退出已加入的群，返回是否成功删除
    bool delJoinedGroupById(std::string Id);


    // 设置绑定的Wechat账号Id
    void setBindWechatAccountId(std::string Id)
    {
        this->bindWechatAccountId = Id;
    }

    // 设置绑定的Weibo账号
    void setBindWeiboAccountId(std::string Id)
    {
        this->bindWeiboAccountId = Id;
    }


    // 获取绑定的Wechat账号
    std::string getBindWechatAccountId()
    {
        return this->bindWechatAccountId;
    }

    // 获取绑定的Weibo账号
    std::string getBindWeiboAccountId()
    {
        return this->bindWeiboAccountId;
    }


private:
    // QQ用户文件所在文件夹地址
    static std::string accountFileAddress;
    
    // 好友表
    std::list<QQFriend> myFriends;

    // 群表
    std::list<QQJoinedGroup> myGroups;

    // QQ用户个人信息文件
    std::string thisAccountSelfFileAddress;

    // QQ用户好友信息文件
    std::string thisAccountFriendFileAddress;

    // QQ用户群信息文件
    std::string thisAccountGroupFileAddress;

    // Wechat绑定的Id
    std::string bindWechatAccountId;

    // Weibo绑定的Id
    std::string bindWeiboAccountId;

};



class WechatAccount : public baseAccount
{
public:
    // 构造函数
    WechatAccount(std::string ID) {

        thisAccountSelfFileAddress = WechatAccount::accountFileAddress + ID + "Self" + ".txt";

        thisAccountFriendFileAddress = WechatAccount::accountFileAddress + ID + "Friend" + ".txt";

        thisAccountGroupFileAddress = WechatAccount::accountFileAddress + ID + "Group" + ".txt";

        this->readAccountFromFile();
    }



    // 添加好友至好友列表，返回是否成功添加
    bool addFriendToList(std::string WechatName, std::string WechatId);

    // 遍历并输出好友列表，无返回
    void showFriendList();

    // 根据Id查找好友，返回其索引
    int searchFriendById(std::string WechatId);

    // 根据名字查找好友，返回其索引
    int searchFriendByName(std::string WechatName);

    // 根据Id删除好友，返回是否成功删除
    bool delFriendById(std::string WechatId);

    // 根据name删除好友，返回是否成功删除
    bool delFriendByName(std::string WechatName);


    // 将用户信息保存为文件
    void saveAccountAsFile();

    // 从文件中读取用户信息
    bool readAccountFromFile();

    // 创建或重置文件
    static void createOrResetFile(std::string Id);

    // 加入群
    bool joinGroupToList(std::string Name, std::string Id);

    // 遍历并输出已加入群列表，无返回
    void showJoinedGroupList();

    // 根据Id查找已加入的群，返回其索引
    int searchJoinedGroupById(std::string Id);

    // 根据Id退出已加入的群，返回是否成功删除
    bool delJoinedGroupById(std::string Id);

    // 设置绑定的QQ账号Id
    void setBindQQAccountId(std::string Id)
    {
        this->bindQQAccountId = Id;
    }

    // 设置绑定的Weibo账号
    void setBindWeiboAccountId(std::string Id)
    {
        this->bindWeiboAccountId = Id;
    }


    // 获取绑定的QQ账号
    std::string getBindQQAccountId()
    {
        return this->bindQQAccountId;
    }

    // 获取绑定的Weibo账号
    std::string getBindWeiboAccountId()
    {
        return this->bindWeiboAccountId;
    }



private:
    // Wechat用户文件所在文件夹地址
    static std::string accountFileAddress;

    // 好友表
    std::list<WechatFriend> myFriends;

    // 群表
    std::list<WechatJoinedGroup> myGroups;

    // Wechat用户个人信息文件
    std::string thisAccountSelfFileAddress;

    // Wechat用户好友信息文件
    std::string thisAccountFriendFileAddress;

    // Wechat用户群信息文件
    std::string thisAccountGroupFileAddress;

    // QQ绑定的Id
    std::string bindQQAccountId;

    // Weibo绑定的Id
    std::string bindWeiboAccountId;
};




class WeiboAccount : public baseAccount
{
public:
    // 构造函数
    WeiboAccount(std::string ID) {

        thisAccountSelfFileAddress = WeiboAccount::accountFileAddress + ID + "Self" + ".txt";

        thisAccountFriendFileAddress = WeiboAccount::accountFileAddress + ID + "Friend" + ".txt";

        thisAccountGroupFileAddress = WeiboAccount::accountFileAddress + ID + "Group" + ".txt";

        this->readAccountFromFile();
    }



    // 添加好友至好友列表，返回是否成功添加
    bool addFriendToList(std::string WeiboName, std::string WeiboId);

    // 遍历并输出好友列表，无返回
    void showFriendList();

    // 根据Id查找好友，返回其索引
    int searchFriendById(std::string WeiboId);

    // 根据名字查找好友，返回其索引
    int searchFriendByName(std::string WeiboName);

    // 根据Id删除好友，返回是否成功删除
    bool delFriendById(std::string WeiboId);

    // 根据name删除好友，返回是否成功删除
    bool delFriendByName(std::string WeiboName);


    // 将用户信息保存为文件
    void saveAccountAsFile();

    // 从文件中读取用户信息
    bool readAccountFromFile();

    // 创建或重置文件
    static void createOrResetFile(std::string Id);

    // 加入群
    bool joinGroupToList(std::string Name, std::string Id);

    // 遍历并输出已加入群列表，无返回
    void showJoinedGroupList();

    // 根据Id查找已加入的群，返回其索引
    int searchJoinedGroupById(std::string Id);

    // 根据Id退出已加入的群，返回是否成功删除
    bool delJoinedGroupById(std::string Id);

    // 设置绑定的QQ账号Id
    void setBindQQAccountId(std::string Id)
    {
        this->bindQQAccountId = Id;
    }

    // 设置绑定的Wechat账号
    void setBindWechatAccountId(std::string Id)
    {
        this->bindWechatAccountId = Id;
    }


    // 获取绑定的QQ账号
    std::string getBindQQAccountId()
    {
        return this->bindQQAccountId;
    }

    // 获取绑定的Wechat账号
    std::string getBindWechatAccountId()
    {
        return this->bindWechatAccountId;
    }

private:
    // Weibo用户文件所在文件夹地址
    static std::string accountFileAddress;

    // 好友表
    std::list<WeiboFriend> myFriends;

    // 群表
    std::list<WeiboJoinedGroup> myGroups;

    // Weibo用户个人信息文件
    std::string thisAccountSelfFileAddress;

    // Weibo用户好友信息文件
    std::string thisAccountFriendFileAddress;

    // Weibo用户群信息文件
    std::string thisAccountGroupFileAddress;

    // QQ绑定的Id
    std::string bindQQAccountId;

    // Wechat绑定的Id
    std::string bindWechatAccountId;
};




#endif