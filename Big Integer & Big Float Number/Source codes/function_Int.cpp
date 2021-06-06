#include "function.h"

/* Tinh toan bu 2 tren he nhi phan
- Dau vao la mang vector<bool> number
- Tinh bu 2 cua number => gan lai cho number
*/
void TwoComplement(vector<bool> &number)
{
	// Bu 1
	for (int i = 0; i < 128; i++)
		number[i] = !number[i]; //dao bit

	int miss = 1;
	// Cong 1 vao bit cuoi
	int i = 0;
	while (miss != 0 && i < 128)
	{
		if (number[i])
			number[i] = 0;
		else
		{
			number[i] = 1;
			miss = 0;
		}
		i++;
	}
}

char* numToStr(int x)
{
	char* s = new char[1];
	switch (x)
	{
	case 0:  strcpy(s, "0"); break;
	case 1:  strcpy(s, "1"); break;
	case 2:  strcpy(s, "2"); break;
	case 3:  strcpy(s, "3"); break;
	case 4:  strcpy(s, "4"); break;
	case 5:  strcpy(s, "5"); break;
	case 6:  strcpy(s, "6"); break;
	case 7:  strcpy(s, "7"); break;
	case 8:  strcpy(s, "8"); break;
	case 9:  strcpy(s, "9"); break;
	case 10: strcpy(s, "A"); break;
	case 11: strcpy(s, "B"); break;
	case 12: strcpy(s, "C"); break;
	case 13: strcpy(s, "D"); break;
	case 14: strcpy(s, "E"); break;
	default:
		strcpy(s, "F");
		break;
	}
	return s;
}

//vector<bool> bit luu nguoc
//string res, k luu ket qua xuoi
string BinToDec(vector<bool> bit)
{
	bool negative = false;
	if (bit.size() == 128 && bit[127] == 1) 
	//TH so am -> chuyen day bit tu bu 2 ve dang so duong
	{
		negative = true;
		int i = 0;
		//tru 1
		if (bit[i] == 1) bit[i] = 0;
		else
		{
			while (bit[i] == 0 && i < 128)
			{
				bit[i] = 1;
				i++;
			}
			if (i < 128) bit[i] = 0;
		}
		//dao bit
		for (int i = 0; i < 128; i++)
			bit[i] = !bit[i];
	}

	//chuyen tu so nhi phan sang thap phan
	string res = "0", k = "1";
	for (int i = 0; i < 128; i++)
	{
		if (bit[i] == 1)
			DecAdd(res, k); //res = res + k
		DecMultiply2(k); // k = k*2
	}

	//neu so am thi them dau vao kq
	if (negative) res = "-" + res;
	return res;
}

// tra ve day bit dung thu tu
string Show(vector<bool> number)
{
	int i = number.size() - 1;
	//Loai bo cac so 0 vo nghia o dau
	while (!number[i] && i > 0) 
		i--;

	string res = "";
	for (i; i >= 0; i--)
		if (number[i] == 1) res = res + "1";
		else res = res + "0";
	return res;
}

//cong hai so thap phan
void DecAdd(string &a, const string &b) //a = a+b
{
	int n = a.length();
	int m = b.length();
	int i = n - 1, j = m - 1, t = 0;
	while (i >= 0 || j >= 0)
	{
		int x, y;
		if (i < 0) x = 0; else x = a[i] - '0';
		if (j < 0) y = 0; else y = b[j] - '0';
		int tmp = x + y + t;
		char c;
		if (tmp < 10) //ko nho
		{
			c = (char)'0' + tmp;
			t = 0;
		}
		else //co nho
		{
			c = (char)'0' + tmp % 10;
			t = 1;
		}
		if (i >= 0) a[i] = c; else a = c + a;
		i--; j--;
	}
	if (t == 1) a = "1" + a;
}

// Chia mot chuoi cho 2
void DecDivide2(string &number)
{
	string result = ""; // Bien luu ket qua
	int miss = 0, i = 0, temp; // miss: bien de nho

	while (i < number.length()) // Xet tung chu so cua chuoi
	{
		temp = (miss * 10) + (number[i] - 48);
		miss = temp % 2; // Lay so du => luu vao miss
		i++;
		if ((result.length() == 0) && ((temp / 2) == 0))
		{
			if (number.length() == 1) // Truong hop number = 0
				result = "0";
			else // Loai bo so 0 vo nghia khi so chia < so bi chia
				continue;
		}
		else
			result += ((temp / 2) + 48); // Lay thuong => chuyen qua ki tu => luu vao phia sau result
	}
	number = result; // number = number / 2
}

//nhan so thap phan voi 2
void DecMultiply2(string &a) //a = a*2
{
	int t = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		int tmp = (a[i] - '0') * 2 + t;
		if (tmp < 10)
		{
			a[i] = (char)'0' + tmp;
			t = 0;
		}
		else
		{
			a[i] = (char)'0' + tmp % 10;
			t = 1;
		}
	}
	if (t == 1) a = "1" + a;
}