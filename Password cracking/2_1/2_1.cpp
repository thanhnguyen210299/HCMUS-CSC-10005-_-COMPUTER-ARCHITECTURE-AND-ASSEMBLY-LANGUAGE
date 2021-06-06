#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstdint>

using namespace std;

string ASCIItoHEX(int data)
{
	string result = "";
	int temp = 0;
	if (!data)
	{
		return "00";
	}
	while (data != 0)
	{
		temp = data % 16;
		data = data / 16;
		switch (temp)
		{
		case 0:
			result = "0" + result; break;
		case 1:
			result = "1" + result; break;
		case 2:
			result = "2" + result; break;
		case 3:
			result = "3" + result; break;
		case 4:
			result = "4" + result; break;
		case 5:
			result = "5" + result; break;
		case 6:
			result = "6" + result; break;
		case 7:
			result = "7" + result; break;
		case 8:
			result = "8" + result; break;
		case 9:
			result = "9" + result; break;
		case 10:
			result = "A" + result; break;
		case 11:
			result = "B" + result; break;
		case 12:
			result = "C" + result; break;
		case 13:
			result = "D" + result; break;
		case 14:
			result = "E" + result; break;
		case 15:
			result = "F" + result; break;
		}
	}
	if (result.length() == 1)
		result = "0" + result;
	return result;
}


unsigned long ASCIItoDEC(int data[])
{
	unsigned long result = 0;
	string str = "";
	for (int i = 0; i < 4; i++)
		str += ASCIItoHEX(data[i]);

	int count = 0;
	unsigned long temp = 1;
	for (int i = str.length() - 1; i >= 0; i--)
	{
		switch (str[i])
		{
		case '1':
			result += temp; break;
		case '2':
			result += 2 * temp; break;
		case '3':
			result += 3 * temp; break;
		case '4':
			result += 4 * temp; break;
		case '5':
			result += 5 * temp; break;
		case '6':
			result += 6 * temp; break;
		case '7':
			result += 7 * temp; break;
		case '8':
			result += 8 * temp; break;
		case '9':
			result += 9 * temp; break;
		case 'A':
			result += 10 * temp; break;
		case 'B':
			result += 11 * temp; break;
		case 'C':
			result += 12 * temp; break;
		case 'D':
			result += 13 * temp; break;
		case 'E':
			result += 14 * temp; break;
		case 'F':
			result += 15 * temp; break;
		}
		temp *= 16;
	}

	return result;
}

void main()
{
	string tname;
	cout << "Name: ";
	cin >> tname;

	if ((tname.length() < 5) || (tname.length() > 8))
	{
		cout << "Name must have 5 - 8 characters.\n";
		system("pause");
		return;
	}

	char name[9];
	unsigned long serial;
	unsigned long local = 0xDEADBEEF ^ 0x44;
	char str[] = "This pro";
	int i;

	for (i = 0; i < tname.length(); i++)
		name[i] = tname[i];
	for (i = tname.length(); i < 8; i++)
		name[i] = 0;

	// Xu ly phan Name
	// 1. Name Xor "This pro"
	for (i = 0; i<8; i++)
		name[i] ^= str[i];

	// 2. Serial = Trich 4 ki tu dau, ghi nguoc
	int temp[4];
	for (i = 0; i < 4; i++)
	{
		temp[i] = (int)name[4 - i - 1];
	}
	// 3. Serial = Serial * 0xD * (0x44 ^ 0xDEADBEEF)
	serial = ASCIItoDEC(temp);
	serial *= 0xD;
	serial *= local;
	// 4. Serial = (Serial % 0xFF9D) * 2
	serial = serial % 0xFF9D;
	serial *= 2;


	// Xu ly nguoc phan Serial
	// serial = ((serial >> 1) ^ 1 - 0xD) << 2
	serial >>= 1;
	serial ^= 1;
	serial -= 0xD;
	serial = (uint32_t)(serial << 2);
	// serial = serial * 0x100000000 / 0x92492492
	serial = serial * 0x100000000 / 0x92492492;
	cout << "Serial: " << serial << endl;

	system("pause");
}