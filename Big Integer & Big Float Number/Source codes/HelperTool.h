#pragma once
#ifndef _HELPER_TOOL_H_
#define _HELPER_TOOL_H_

#include "QInt.h"
#include "QFloat.h"

// SO NGUYEN
// Chuyen doi co so
string IntConvertTool(string number, int typeOfNumber, int typeChange);

// Xu li toan tu
// Toan tu >>, <<, rol, ror
string Calculate1_Int(QInt &number, int numberOfBit, int typeNumber, string typeOperator);

// Toan tu 1 ngoi (NOT)
string UnaryOperator(int typeOfNumber, string number);

// Toan tu 2 ngoi(+, -, *, /, AND, OR, XOR, so sanh)
string Calculate2_Int(QInt a, QInt b, int typeNumber, string typeOperator);

// SO CHAM DONG
// Chuyen doi co so
string FloatConvertTool(string number, int typeOfNumber, int typeChange);
string Calculate_Float(QFloat a, QFloat b, int typeNumber, string typeOperator);
#endif
