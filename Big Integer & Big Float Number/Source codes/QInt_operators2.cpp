#include "QInt.h"

QInt& QInt::operator >> (int numberOfBit)
{
	int temp = numberOfBit / 32;

	// Chuyen bit theo dang nguyen
	/* VD data[0] 10...010  numberbit 65 
	=> temp = 2 => se thanh  data[0] 01...101

	data[1] 00...001	 data[1] 10...001
	data[2] 01...101	 data[2] 00...000
	data[3] 10...001	 data[3] 00...000 (luu nguoc) */

	int tmp;
	for (int j = 0; j < 4 - temp; j++)
		data[j] = data[j + temp];
	if (data[3] < 0)
		tmp = 4294967295;
	else
		tmp = 0;
	for (int j = temp; j > 0; j--)
		data[4 - j] = tmp;

	// Chuyen cac bit con lai
	numberOfBit %= 32;
	vector<bool> bit;
	bool t;

	// neu so am => thi day vao bit 1, nguoc lai bit 0 de giu nguyen dau
	if (data[3] < 0)
	{
		for (int i = 0; i < numberOfBit; i++)
			bit.push_back(1);
	}
	else
	{
		for (int i = 0; i < numberOfBit; i++)
			bit.push_back(0);
	}

	// dich tu data cao den data thap
	for (int i = 3; i >= 0; i--)
	{
		// luu lai gia tri cua cac bit cu 
		// => temp la cac bit bi mat cua i - 1
		vector<bool> temp = bit;

		// luu lai cac bit bi mat khi dich 
		// (vi du data: 11110101 >> 3 => data : 11111110 va bit la 101) 
		// => bit la cac bit bi mat cua i
		for (int j = numberOfBit - 1; j >= 0; j--)
		{
			bit[j] = data[i] & 1;
			data[i] = data[i] >> 1;
		}

		// gan cac bit bi mat cua i - 1 vao bit thu i 
		// (vi du data: 10101011 >> 3 va temp 001 => data: 00110101)
		for (int j = numberOfBit - 1; j >= 0; j--)
		{
			if (temp[j])
				data[i] = (data[i]) | (1 << (31 - j));
			else
				data[i] = (data[i]) & (~(1 << (31 - j)));
		}
	}
	return *this;
}

QInt& QInt::operator<<(int numberOfBit)
{
	// Chuyen bit theo dang nguyen
	/* VD data[0] 10...010  numberbit 65 => temp = 2 => se thanh  data[0] 00...000
	data[1] 00...001  data[1] 00...000
	data[2] 01...101  data[2] 10...010
	data[3] 10...001  data[3] 00...001 (luu nguoc) */

	int temp = numberOfBit / 32, j = 3;
	while (j >= temp)
	{
		data[j] = data[j - temp];
		j--;
	}
	for (j = 0; j < temp; j++)
		data[j] = 0;

	// Chuyen cac bit con lai
	numberOfBit %= 32;
	vector<bool> bit;
	bool t;

	for (int i = 0; i < numberOfBit; i++)
		bit.push_back(0);

	// dich tu data cao den data thap
	for (int i = 3; i > 0; i--)
	{
		// luu lai cac bit bi mat cua i - 1
		for (int j = numberOfBit - 1; j >= 0; j--)
			bit[numberOfBit - j - 1] = (data[i - 1] >> (31 - j)) & 1;

		// dich bit cua i 
		// (vi du data: 11110101 << 3 => data : 10101000)
		data[i] = data[i] << numberOfBit;

		// gan cac bit bi mat cua i - 1 vao bit thu i 
		// (vi du data: 11110101 << 3 va bit: 101 => data : 10101101)
		for (int j = 0; j < numberOfBit; j++)
		{
			if (bit[j])
				data[i] = (data[i]) | (1 << j);
		}
	}
	data[0] = data[0] << numberOfBit; // dich bit cua data[0]

	return *this;
}

void QInt::rol(int bit)
{
	vector<bool>  t = this->QIntToBin();
	int count = t.size() - 1;

//	while (!t[count]) //Loai bo cac so 0 vo nghia
//		count--;

	count++; // So luong bit co nghia

	vector<bool> res = t;
	// Lay do dich chuyen toi thieu
	if (bit > count) bit = bit - (bit / count)*count;
	for (int i = count - 1; i >= 0; i--)
	{
		if (i < bit) res[i] = t[i - bit + count];
		else res[i] = t[i - bit];
	}
	*this = BinToQInt(res);
}

void QInt::ror(int bit)
{
	vector<bool>  t = this->QIntToBin();
	int count = t.size() - 1;

	//while (!t[count]) //Loai bo cac so 0 vo nghia
//		count--;
	count++; // So luong bit co nghia

	vector<bool> res = t;
	// Lay do dich chuyen toi thieu
	if (bit > count) bit = bit - (bit / count)*count;

	for (int i = 0; i < count; i++)
	{
		if (i + bit >= count) res[i] = t[i + bit - count];
		else res[i] = t[i + bit];
	}
	*this = BinToQInt(res);
}

bool QInt::operator<(const QInt &other)
{
	for (int i = 3; i >= 0; i--)
	{
		if (data[i] < other.data[i]) return true;
		if (data[i] > other.data[i]) return false;
	}
	return false;
}

bool QInt::operator>(const QInt &other)
{
	for (int i = 3; i >= 0; i--)
	{
		if (data[i] > other.data[i]) return true;
		if (data[i] < other.data[i]) return false;
	}
	return false;
}

bool QInt::operator==(const QInt &other)
{
	for (int i = 0; i < 4; i++)
		if (data[i] != other.data[i]) return false;
	return true;
}

bool QInt::operator<=(const QInt &other)
{
	for (int i = 3; i >= 0; i--)
	{
		if (data[i] < other.data[i]) return true;
		if (data[i] > other.data[i]) return false;
	}
	return true;
}

bool QInt::operator>=(const QInt &other)
{
	for (int i = 3; i >= 0; i--)
	{
		if (data[i] < other.data[i]) return false;
		if (data[i] > other.data[i]) return true;
	}
	return true;
}

QInt& QInt::operator=(const QInt &other)
{
	for (int i = 0; i < 4; i++)
		data[i] = other.data[i];
	return *this;
}

QInt& QInt::operator&(const QInt &other)
{
	for (int i = 0; i < 4; i++)
		data[i] = data[i] & other.data[i];
	return *this;
}

QInt& QInt::operator|(const QInt &other)
{
	for (int i = 0; i < 4; i++)
		data[i] = data[i] | other.data[i];
	return *this;
}

QInt& QInt::operator^(const QInt &other)
{
	for (int i = 0; i < 4; i++)
		data[i] = data[i] ^ other.data[i];
	return *this;
}

QInt& QInt::operator~()
{
	for (int i = 0; i < 4; i++)
		data[i] = ~data[i];
	return *this;
}