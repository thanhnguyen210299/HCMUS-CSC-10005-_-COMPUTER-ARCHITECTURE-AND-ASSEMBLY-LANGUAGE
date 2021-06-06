#pragma once
#ifndef _QFLOAT_H_
#define _QFLOAT_H_

#include "StringToBitArray.h"
#include "QInt.h"

class QFloat
{
private:
	int data[4];
	vector<bool> add(vector<bool> bit1, vector<bool> bit2);
	vector<bool> convert_sign(vector<bool> bit);

public:
	//QFloat.cpp
	QFloat();
	string toString(int);

	QFloat& operator=(QFloat &other);
	bool operator<(const QFloat &other);
	bool operator==(const QFloat &other);

	//QFloat_converters.cpp
	static QFloat BinToQFloat(vector<bool> bit);
	vector<bool> QFloatToBin();

	//QFloat_operators.cpp
	QFloat operator+(QFloat &other);
	QFloat operator-(QFloat &other);
	QFloat operator*(QFloat &other);
	QFloat operator/(QFloat &other);
};

#endif

