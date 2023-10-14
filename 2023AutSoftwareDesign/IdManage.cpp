#define _CRT_SECURE_NO_WARNINGS 1

#include <bitset>
#include <fstream>
#include <iostream>
#include <string>

#include "IdManage.h"
#include "RandomNum.h"




using namespace std;






// 重置Id
bool baseIdManage::resetIdBitmap()
{
    (this->IdBitmap)->reset();

    ofstream fout;
    bool result = false;
    fout.open(this->fileName, ios::out);
    if (!fout.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fout << *(this->IdBitmap);
        this->latestId = minIdNum;
        result = true;
        fout.close();
    }

    return result;
}


// 查询Id是否已注册
bool baseIdManage::isIdExist(string Id)
{
    bitset<maxIdNum>* IdBitmap = new bitset<maxIdNum>;

    ifstream fin;
    bool result = false;
    fin.open(this->fileName, ios::in);
    if (!fin.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fin >> *(this->IdBitmap);
        int idIndex = stoi(Id);
        if ((1 == (*(this->IdBitmap))[idIndex]))
        {
            result = true;
        }
        fin.close();
    }

    return result;
}


// 设置输入Id位置为1或0
void baseIdManage::setIdIndex(string Id, int num)
{
    ifstream fin;
    ofstream fout;

    bool result = false;
    fin.open(this->fileName, ios::in);
    if (!fin.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fin >> *(this->IdBitmap);
        int idIndex = stoi(Id);
        (*(this->IdBitmap))[idIndex] = num;
        fin.close();
    }

    fout.open(this->fileName, ios::out);
    if (!fout.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fout << *(this->IdBitmap);
        fout.close();
    }

}


// 返回一个可用的Id并将输入id位置设为1，如无符合条件的Id，则返回-1
string baseIdManage::returnUsableId()
{
    bitset<maxIdNum>* QQIdBitmap = new bitset<maxIdNum>;

    ifstream fin;
    int result = -1;
    fin.open(this->fileName, ios::in);
    if (!fin.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fin >> *(this->IdBitmap);
        if (((maxIdNum - minIdNum) > (*(this->IdBitmap)).count()))
        {
            while (result == -1)
            {
                result = ++this->latestId;
                this->setIdIndex(to_string(result), 1);
            }
        }
        fin.close();
    }

    return to_string(result);
}



QQIdManage::QQIdManage()
{
    this->fileName = "./QQ/QQIdBitmap.txt";
    this->IdBitmap = new bitset<maxIdNum>;
    

    ifstream fin;
    fin.open(this->fileName, ios::in);
    if (!fin.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fin >> *(this->IdBitmap);
        fin.close();
    }

    this->latestId = minIdNum + (int)this->IdBitmap->count();
}

QQGIdManage::QQGIdManage()
{
    this->fileName = "./QQ/QQGIdBitmap.txt";
    this->IdBitmap = new bitset<maxIdNum>;


    ifstream fin;
    fin.open(this->fileName, ios::in);
    if (!fin.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fin >> *(this->IdBitmap);
        fin.close();
    }

    this->latestId = minIdNum + (int)this->IdBitmap->count();
}

/*
// 重置qqId
bool QQIdManage::resetQQIdBitmap()
{
    (this->QQIdBitmap)->reset();

    ofstream fout;
    bool result = false;
    fout.open(this->fileName, ios::out);
    if (!fout.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fout << *(this->QQIdBitmap);
        this->latestId = minIdNum;
        result = true;
        fout.close();
    }

    return result;
}


// 查询qqId是否已注册
bool QQIdManage::isQQIdExist(string QQId)
{
    bitset<maxIdNum>* QQIdBitmap = new bitset<maxIdNum>;

    ifstream fin;
    bool result = false;
    fin.open(this->fileName,  ios::in);
    if (!fin.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fin >> *(this->QQIdBitmap);
        int idIndex = stoi(QQId);
        if ((1 == (*(this->QQIdBitmap))[idIndex]))
        {
            result = true;
        }
        fin.close();
    }

    return result;
}


// 设置输入Id位置为1或0
void QQIdManage::setQQIdIndex(string QQId, int num)
{
    ifstream fin;
    ofstream fout;

    bool result = false;
    fin.open(this->fileName, ios::in);
    if (!fin.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fin >> *(this->QQIdBitmap);
        int idIndex = stoi(QQId);
        (*(this->QQIdBitmap))[idIndex] = num;
        fin.close();
    }

    fout.open(this->fileName, ios::out);
    if (!fout.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fout << *(this->QQIdBitmap);
        fout.close();
    }

}


// 返回一个可用的QQId并将输入id位置设为1，如无符合条件的Id，则返回-1
string QQIdManage::returnUsableQQId()
{
    bitset<maxIdNum>* QQIdBitmap = new bitset<maxIdNum>;

    ifstream fin;
    int result = -1;
    fin.open(this->fileName, ios::in);
    if (!fin.is_open())
    {
        cout << "File open error  ----  " << this->fileName;
    }
    else
    {
        fin >> *(this->QQIdBitmap);
        if (((maxIdNum - minIdNum) > (*(this->QQIdBitmap)).count()))
        {
            while (result == -1)
            {
                result = ++this->latestId;
                this->setQQIdIndex(to_string(result), 1);
            }
        }
        fin.close();
    }

    return to_string(result);
}
*/



