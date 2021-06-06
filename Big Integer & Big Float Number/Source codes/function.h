#pragma once
#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

//////////////////// SO NGUYEN ////////////////////
// Bu 2
void TwoComplement(vector<bool> &number);
// chuyen doi trong he hexa
char* numToStr(int x);

// tra ve day bit theo dung thu tu
string Show(vector<bool> number);
// Kiem tra so thuc
bool IsReal(string line);
// Lay co so (he 2, he 10, he 16)
int getRadix(size_t &startPos, size_t &foundPos, string line);

// Tinh toan chuoi thap phan
void DecAdd(string &a, const string &b);
// Chia chuoi cho 2
void DecDivide2(string &number);
// Nhan chuoi cho 2
void DecMultiply2(string &a);

// Chuyen day bit qua chuoi thap phan dung thu tu
string BinToDec(vector<bool> bit);

////////////////// SO CHAM DONG /////////////////////
// Tach so cham dong
void SplitNumber(string &int_part, string &point_part, string number);
// Nhan phan thap phan cho 2
string PointMultiply2(string &a);
// Doi tu thap phan qua nhi phan
void DecToBinFloat(string &int_part, string &point_part, int &exp);
// Chuan hoa so cham dong
void ToNormalize(string &int_part, string &point_part, string number, int typeOfNumber, int &exp);

// Tinh mu cua so cham dong tren cac bit mu
int Exp(vector<bool>);
// Chuyen tu day bit qua so cham dong he nhi phan
void ArrayToBin(vector<bool> bit, string &int_part, string &point_part);
// Chuyen tu day bit qua so cham dong he thap phan
void ArrayToDec(vector<bool> bit, string &int_part, string &point_part);

#endif