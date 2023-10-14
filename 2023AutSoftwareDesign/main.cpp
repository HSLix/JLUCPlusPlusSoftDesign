#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
#include <cstdlib>


#include "Group.h"
#include "Interact.h"
#include "AccountGroupDataManage.h"
#include "Program.h"



using namespace std;



int main()
{
    system("chcp 65001");
    system("cls");

    QQGroup testGroup();
    
    Interact::pauseAndClearScreen();


    program* TecSys = new program();
    while (true)
    {
        TecSys->rootPage();
        TecSys->branchPage();
    }



    return 0;
}