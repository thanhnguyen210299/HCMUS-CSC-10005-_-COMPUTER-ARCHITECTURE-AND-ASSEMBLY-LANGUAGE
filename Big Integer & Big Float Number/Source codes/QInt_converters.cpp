#include "QInt.h"

QInt QInt::BinToQInt(vector<bool> bit)
{
	QInt res;
	int t = 3;
	while (t >= 0)
	{
		//xet day bit tu t*32 -> (t+1)*32 - 1

		//ktra dau cua day bit
		//neu day bit am, chuyen ve day bit duong va doi dau kq
		bool negative = false;
		if (bit[(t + 1) * 32 - 1] == 1)
		{
			//xu ly so am
			negative = true;
			int i = t * 32;
			//tru 1
			if (bit[i] == 1) bit[i] = 0;
			else
			{
				while (bit[i] == 0 && i < (t + 1) * 32)
				{
					bit[i] = 1;
					i++;
				}
				if (i < (t + 1) * 32) bit[i] = 0;
			}
			//dao bit
			for (int i = t * 32; i < (t + 1) * 32; i++)
				bit[i] = !bit[i];
		}

		for (int i = t * 32; i < (t + 1) * 32; i++)
			if (bit[i] == 1)
				res.data[t] = res.data[t] | (1 << (i % 32));
		
		//doi dau kq
		if (negative) res.data[t] *= -1;
		t--;
	}
	return res;
}

vector<bool> QInt::QIntToBin()
{
	vector<bool> bit;
	for (int i = 0; i < 4; i++)
	{
		//data[i] tuong ung day bit tu i*32 toi (i+1)*32-1
		int tmp = data[i];

		//neu data[i] am thi chuyen phan duong truoc
		if (tmp < 0) tmp *= -1; 
		for (int j = 0; j < 32; j++)
			bit.push_back(1 & (tmp >> j));
		
		if (data[i] < 0) //lay bu 2 neu la so am
		{
			//dao bit
			for (int j = i * 32; j < (i + 1) * 32; j++)
				bit[j] = !bit[j];
			//cong 1
			int j = i * 32;
			if (bit[j] == 0) bit[j] = 1;
			else
			{
				while (bit[j] == 1 && j < (i + 1) * 32)
				{
					bit[j] = 0;
					j++;
				}
				if (j < (i + 1) * 32) bit[j] = 1;
			}
		}
	}
	return bit;
}

string QInt::BinToHex(vector<bool> bit)
{
	// Lan luot 4 bits tao thanh 1 ky tu trong chuoi hexa
	string res = "";
	int t;
	int i = 0;
	while (i < bit.size())
	{
		t = 0;
		int sum = 0;
		while (i < bit.size() && t < 4)
		{
			if (bit[i] == 1) sum = sum + pow(2, t);
			i++;
			t++;
		}
		res = numToStr(sum) + res;
	}
	// Xoa ki tu "0" du
	i = 0;
	while (res[i] == '0' && i < res.length() - 1)
		i++;
	res = res.substr(i, res.length() - i);
	return res;
}

string QInt::QIntToHex()
{
	vector<bool> BIN = QIntToBin();
	return BinToHex(BIN);
}