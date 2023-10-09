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
#include "AccountGroupDataManage.h"


using namespace std;


int main()
{
    system("chcp 65001");
    system("cls");





    QQDataManage qqDataM;

    qqDataM.readFileSaveAsMap();

    qqDataM.signupQQ("老王", "123456");


    QQAccount user1("100035");
    user1.readAccountFromFile();
    cout << user1.getId() << endl;
    cout << user1.getName() << endl;
    

    user1.readAccountFromFile();

    user1.addFriendToList("小明", "100013");
    user1.addFriendToList("小红", "100020");

    user1.showFriendList();
    
    cout << endl;

    user1.saveAccountAsFile();

    user1.readAccountFromFile();

    user1.showFriendList();


    
    return 0;
}