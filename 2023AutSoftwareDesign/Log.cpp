#define _CRT_SECURE_NO_WARNINGS 1

#include "Account.h"

#include <iostream>

bool checkPwd(baseAccount * a1, std::string inputPwd)
{
    bool result;

    result = a1->checkPwd(inputPwd);

    return result;

}

