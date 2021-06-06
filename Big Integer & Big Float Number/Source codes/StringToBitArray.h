#pragma once
#ifndef _STR_TO_ARRAY_H_
#define _STR_TO_ARRAY_H_

#include "Function.h"

// SO NGUYEN  
// Chuyen chuoi input => mang bit
vector<bool> BinStrToArray(string number);
vector<bool> DecStrToArray(string number);
vector<bool> HexStrToArray(string number);
vector<bool> ChangeStrToArray(string number, int type);

// Chuyen chuoi thap phan => so nguyen
int DecStrToDec(string number);

// SO CHAM DONG
// chuyen chuoi so cham dong -> mang bit 
vector<bool> FloatStrToArray(string number, int typeOfNumber);

#endif