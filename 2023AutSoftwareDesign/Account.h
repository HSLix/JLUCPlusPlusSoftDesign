#ifndef ACCOUNTH
#define ACCOUNTH

#include <string>
#include <list>
#include "Friend.h"


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
        return mId;
    }

    // 返回名字
    std::string getName() {
        return mName;
    }

    // 修改Id
    void setId(std::string Id)
    {
        mId = Id;
    }

    // 修改Name
    void setName(std::string Name)
    {
        mName = Name;
    }

    // 修改Pwd
    void setPwd(std::string Pwd)
    {
        mPwd = Pwd;
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
};


class QQAccount : public baseAccount
{
public:
    // 构造函数
    QQAccount(std::string ID){

        thisAccountSelfFileAddress = QQAccount::accountFileAddress + ID + "Self" + ".txt";

        thisAccountFriendFileAddress = QQAccount::accountFileAddress + ID + "Friend" + ".txt";
    
        thisAccountGroupFileAddress = QQAccount::accountFileAddress + ID + "Group" + ".txt";

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
    
    // 根据name创建Group




private:
    // QQ用户文件所在文件夹地址
    static std::string accountFileAddress;
    
    // 好友表
    std::list<QQFriend> myFriends;

    // QQ用户个人信息文件
    std::string thisAccountSelfFileAddress;

    // QQ用户好友信息文件
    std::string thisAccountFriendFileAddress;

    // QQ用户群信息文件
    std::string thisAccountGroupFileAddress;
};




#endif