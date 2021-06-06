#include "QFloat.h"

QFloat::QFloat()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}

QFloat& QFloat::operator=(QFloat &other)
{
	for (int i = 0; i < 4; i++)
		data[i] = other.data[i];
	return *this;
}

bool QFloat::operator<(const QFloat &other)
{
	for (int i = 3; i >= 0; i--)
	{
		if (data[i] < other.data[i]) return true;
		if (data[i] > other.data[i]) return false;
	}
	return false;
}

bool QFloat::operator==(const QFloat &other)
{
	for (int i = 0; i < 4; i++)
		if (data[i] != other.data[i]) return false;
	return true;
}

int Check_Specail_Number(vector<bool> bit)
{
	// Kiem tra mu
	bool all_one = true, all_zero = true;
	for (int i = 112; i < 127; i++)
		if (bit[i])
			all_zero = false;
		else
			all_one = false;

	// Kiem tra phan tri
	bool check = true;
	for (int i = 0; i < 112; i++)
		if (bit[i])
			check = false;

	// Tra ket qua
	if (all_zero && !check)
		return 2;
	if (all_one && check)
		return 3;
	if (all_one && !check)
		return 1;
	return 0;
}

string QFloat::toString(int base)
{
	string int_part = "", point_part = "", result ="";
	vector<bool> bit = QFloatToBin();
	if (base == 2)
	{
		for (int i = 127; i >= 0; i--)
			if (bit[i] == 1) result += '1';
			else result += '0';
		return result;
	}
	if (base == 10)
	{
		int flag = Check_Specail_Number(bit);
		switch (flag)
		{
		case 1: //NaN
		{
			result = "NaN";
			return result;
		}
		case 2: //denormalized
		{
			result = "denormalized";
			return result;
		}
		case 3: //
		{
			result = "infinity";
			return result;
		}
		}
	}
	ArrayToBin(bit, int_part, point_part);
	if (base == 10)
		ArrayToDec(bit, int_part, point_part);
	if (point_part.compare("0") == 0 || point_part.compare("") == 0)
		result = int_part;
	else
		result = int_part + "." + point_part;

	if (bit[127])
		result = "-" + result;
	
	return result;
}
