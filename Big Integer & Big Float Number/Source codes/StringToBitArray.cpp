#include "StringToBitArray.h"

vector<bool> ChangeStrToArray(string number, int type)
{
	if (type == 16)
		return HexStrToArray(number);
	if (type == 2)
		return BinStrToArray(number);
	if (type == 10)
		return DecStrToArray(number);
}

//chuyen chuoi bit -> vector bit
vector<bool> BinStrToArray(string number)
{
	vector<bool> num_bit;
	for (int i = 0; i < 128; i++)
		num_bit.push_back(0);
	for (int i = number.length() - 1, j = 0; i >= 0; i--, j++)
		num_bit[j] = (number[i] == '1');
	return num_bit;
}

//chuyen so thap phan -> vector bit
vector<bool> DecStrToArray(string number)
{
	vector<bool> num_bit;
	int i;
	bool negative = false;

	for (i = 0; i < 128; i++)
		num_bit.push_back(0);

	// Xet dau so thap phan
	if (number[0] == '-')
	{
		negative = true;
		number = number.substr(1, number.length() - 1);
	}

	// Chuyen tu so nguyen khong dau => bit
	i = 0;
	while (number.compare("0") != 0)
	{
		if ((number[number.length() - 1] - 48) % 2 == 0)
			num_bit[i] = 0;
		else
			num_bit[i] = 1;
		i++;
		DecDivide2(number);
	}

	// Lay bu 2 cua bit khong dau
	if (negative)
		TwoComplement(num_bit);
	return num_bit;
}

//chuyen so thap luc phan -> vector bit
vector<bool> HexStrToArray(string number)
{
	vector<bool> num_bit;
	int i, n = number.length();

	for (i = 0; i < 128; i++)
		num_bit.push_back(0);

	i = 0;
	//xet tung ky tu xau ban dau va cap nhat tung nhom 4 bit
	while (i < n) 
	{
		switch (number[n - i - 1])
		{
		case '1': //'0001'
			num_bit[4 * i] = 1;
			break;
		case '2': //'0010'
			num_bit[4 * i + 1] = 1;
			break;
		case '3': //'0011'
			num_bit[4 * i + 1] = 1;
			num_bit[4 * i] = 1;
			break;
		case '4': //'0100'
			num_bit[4 * i + 2] = 1;
			break;
		case '5': //'0101'
			num_bit[4 * i + 2] = 1;
			num_bit[4 * i] = 1;
			break;
		case '6': //'0110'
			num_bit[4 * i + 1] = 1;
			num_bit[4 * i + 2] = 1;
			break;
		case '7': //'0111'
			num_bit[4 * i + 1] = 1;
			num_bit[4 * i] = 1;
			num_bit[4 * i + 2] = 1;
			break;
		case '8': //'1000'
			num_bit[4 * i + 3] = 1;
			break;
		case '9': //'1001'
			num_bit[4 * i + 3] = 1;
			num_bit[4 * i] = 1;
			break;
		case 'A': //'1010'
			num_bit[4 * i + 1] = 1;
			num_bit[4 * i + 3] = 1;
			break;
		case 'B': //'1011'
			num_bit[4 * i + 1] = 1;
			num_bit[4 * i] = 1;
			num_bit[4 * i + 3] = 1;
			break;
		case 'C': //'1100'
			num_bit[4 * i + 3] = 1;
			num_bit[4 * i + 2] = 1;
			break;
		case 'D': //'1101'
			num_bit[4 * i + 3] = 1;
			num_bit[4 * i + 2] = 1;
			num_bit[4 * i] = 1;
			break;
		case 'E': //'1110'
			num_bit[4 * i + 3] = 1;
			num_bit[4 * i + 2] = 1;
			num_bit[4 * i + 1] = 1;
			break;
		case 'F': //'1111'
			for (int j = 0; j < 4; j++)
				num_bit[4 * i + j] = 1;
			break;
		}
		i++;
	}
	return num_bit;
}

// Chuyen chuoi thap phan => so nguyen <= 128
// su dung de lay so bit can dich/ xoay cua phep >>,<<,ror,rol
int DecStrToDec(string number)
{
	int temp = 0;
	for (int i = 0; i < number.length(); i++)
		temp = temp * 10 + (number[i] - 48);
	return temp;
}

//chuyen so cham dong -> vector bit
vector<bool> FloatStrToArray(string number, int typeOfNumber)
{
	vector<bool> num_bit;
	string int_part, point_part;
	int exp = 0;

	for (int i = 0; i < 128; i++)
		num_bit.push_back(0);

	if (number.compare("0") == 0 || number.compare("0.0") == 0) return num_bit;

	// Dua bit dau vao mang bit
	if (number[0] == '-')
	{
		num_bit[127] = 1;
		number = number.substr(1, number.length() - 1);
	}

	// Chuan hoa du lieu vao
	ToNormalize(int_part, point_part, number, typeOfNumber, exp);

	// Dua phan dinh tri vao mang bit
	int pos = 111;
	for (int i = 0; i < point_part.length(); i++)
	{
		if (point_part[i] == '1')
			num_bit[pos] = 1;
		pos--;
	}

	// Dua phan mu vao mang bit
	if (exp != -16382)
	{
		exp += 16383;
		pos = 112;
		// Chuyen tu so nguyen sang day bit
		while (exp != 0)
		{
			num_bit[pos] = exp % 2;
			exp /= 2;
			pos++;
		}
	}

	return num_bit;
}