#pragma once
#ifndef _QINT_H_
#define _QINT_H_

#include <fstream>
#include "function.h"

class QInt
{
private:
	int data[4];
public:
	//QInt.cpp
	QInt();
	QInt(const QInt&);
	int getData(int);
	void setData(int, int);
	int MSBpos();
	bool getBit(int);
	void setBit(int, bool);
	string toString(int);

	//QInt_converters.cpp
	static QInt BinToQInt(vector<bool> bit);
	vector<bool> QIntToBin();
	static string BinToHex(vector<bool> bit);
	string QIntToHex();

	//QInt_operators1.cpp
	static 	QInt BitAdd(QInt a, QInt b, int numberOfBit);
	static QInt BitSub(QInt a, QInt b, int numberOfBit);
	QInt operator+(QInt &other);
	QInt operator-(QInt &other);
	QInt operator*(QInt &other);
	QInt UnsignedMultiply(QInt &other);
	QInt SignedMultiply(QInt &other);
	QInt operator/(QInt &other);

	//QInt_operators2.cpp
	QInt& operator<<(int);
	QInt& operator >> (int);
	void rol(int);
	void ror(int);

	bool operator<(const QInt &other);
	bool operator>(const QInt &other);
	bool operator==(const QInt &other);
	bool operator<=(const QInt &other);
	bool operator>=(const QInt &other); 
	QInt& operator=(const QInt &other);

	QInt& operator&(const QInt &other);
	QInt& operator|(const QInt &other);
	QInt& operator^(const QInt &other);
	QInt& operator~();
};
#endif