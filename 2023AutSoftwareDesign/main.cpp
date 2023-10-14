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
    std::system("chcp 65001");
    std::system("cls");



    program* TecSys = new program();
    while (true)
    {
        TecSys->rootPage();
        TecSys->branchPage();
    }



    return 0;
}