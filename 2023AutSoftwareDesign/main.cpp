#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
#include <cstdlib>


#include "AccountGroupDataManage.h"
#include "Program.h"



using namespace std;

// 清库
void clearDataBase()
{
    
    QQDataManage m;
    m.clearQQAccount();
    m.clearQQGroup();
    WechatDataManage n;
    n.clearWechatAccount();
    n.clearWechatGroup();
    WeiboDataManage p;
    p.clearWeiboAccount();
    p.clearWeiboGroup();
}



int main()
{
    std::system("chcp 65001");
    std::system("cls");

    //clearDataBase();

    /*
    已初始化可用账号如下：
    QQId：100000
    QQ密码：123
    WechatId：100001
    Wechat密码：123
    WeiboId：100000
    QQ密码：123
    */

    program* TecSys = new program();
    
    while (true)
    {
        TecSys->rootPage();
        TecSys->branchPage();
    }



    return 0;
}