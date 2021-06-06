#include "QInt.h"

QInt::QInt()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}

QInt::QInt(const QInt &other)
{
	for (int i = 0; i < 4; i++)
		data[i] = other.data[i];
}

int QInt::getData(int i)
{
	return data[i];
}

void QInt::setData(int i, int value)
{
	data[i] = value;
}

int QInt::MSBpos()
{
	QInt zero;
	if (*this == zero) return 0;
	int i;
	int MSB = 127;
	if (getBit(127) == 1)
	{
		for (i = 3; i >= 0; i--)
			if (data[i] == -1) MSB -= 32;
			else
			{
				for (int j = 31; j >= 0; j--)
				{
					if ((1 & (data[i] >> j)) == 0)
						return MSB + 1;
					else MSB--;
				}
			}
	}
	for (i = 3; i >= 0; i--)
		if (data[i] == 0) MSB -= 32;
		else
		{
			for (int j = 31; j >= 0; j--)
			{
				if ((1 & (data[i] >> j)) == 1)
					return MSB;
				else MSB--;
			}
		}
}

bool QInt::getBit(int i)
{
	return 1 & (data[i / 32] >> (i % 32));
}

void QInt::setBit(int i, bool value)
{
	int t = i / 32;
	int j = i % 32;
	if (value == 1)
		data[t] = data[t] | (1 << j);
	else data[t] = data[t] & ~(1 << j);
}

string QInt::toString(int base)
{
	if (base == 2) return Show(QIntToBin());
	else if (base == 10)
	{
		vector<bool> bit = QIntToBin();
		return BinToDec(bit);
	}
	else if (base == 16)
	{
		return QIntToHex();
	}
}
