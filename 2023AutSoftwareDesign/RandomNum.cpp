#define _CRT_SECURE_NO_WARNINGS 1

#include "RandomNum.h"
#include <random>

// 生成两个整数之间,闭区间，的随机数
int randomIntNum(int max, int min) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}