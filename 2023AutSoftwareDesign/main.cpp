#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <cstdlib>


#include "Account.h"
#include "Login.h"
#include "Friend.h"
#include "Group.h"
#include "IdManage.h"
#include "Interact.h"
#include "AccountGroupDataManage.h"


using namespace std;


int main()
{
    
    system("chcp 65001");
    system("cls");
    

    QQDataManage qqDataM;
    qqDataM.clearQQAccount();
    
    //qqDataM.signupQQ("老王", "123456"); //100001
    //qqDataM.signupQQ("小明", "123456"); //100002
    //qqDataM.signupQQ("小刚", "123456"); //100003

    qqDataM.signinQQ("100001", "123456");

    cout << qqDataM.getUsingAccountName() << endl;
    cout << qqDataM.getUsingAccountId() << endl;
    

    qqDataM.signinQQ("100002", "123456");

    cout << qqDataM.getUsingAccountName() << endl;
    cout << qqDataM.getUsingAccountId() << endl;

    qqDataM.setUsingAccountNULL();

    qqDataM.signinQQ("100003", "123456");

    cout << qqDataM.getUsingAccountName() << endl;
    cout << qqDataM.getUsingAccountId() << endl;
    
    return 0;
}