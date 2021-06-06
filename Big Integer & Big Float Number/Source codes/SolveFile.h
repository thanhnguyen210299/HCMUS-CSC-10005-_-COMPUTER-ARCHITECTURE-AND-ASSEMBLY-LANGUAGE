#pragma once
#ifndef _SOLVEFILE_H_
#define _SOLVEFILE_H_
#include "HelperTool.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

/*
//////////////////////////////// SO NGUYEN //////////////////////
Luu bit nguoc, co dinh mang 128

Vd: 54 => 110110
Mang vector<bool> se la: 0110110....0

5C => 5: 0101 C: 1100
Mang vector<bool> se la: 001110100...0

//////////////////////// SO CHAM DONG ////////////////////////
Thu tu luu vao mang bit: bias = 16383
bit[127] : bit dau
bit[112] -> bit [126] : day bit mu
bit[0] -> bit[111] : day bit dinh tri

Luu vao QFloat: su dung int[4]... day bit vao QFLoat nhu lam voi QInt

**** VIET THEM HAM: string ArrayToDec(vector<bool> trong Function.cpp de tinh toan in ra man hinh

1:True 0:False
*/

// Ham xu li: InputData.cpp
string SolveLine(string line, bool isReal); // Xu li tung dong
void Solve(string fileIn, string fileOut, bool isReal); // Xu li file
#endif