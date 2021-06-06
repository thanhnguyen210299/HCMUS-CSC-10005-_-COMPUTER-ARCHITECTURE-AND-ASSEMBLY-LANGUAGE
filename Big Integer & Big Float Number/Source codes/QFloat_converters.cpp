#include "QFloat.h"

QFloat QFloat::BinToQFloat(vector<bool> bit)
{
	QFloat res;
	int t = 3;
	while (t >= 0)
	{
		for (int i = t * 32; i < (t + 1) * 32; i++)
			if (bit[i] == 1) res.data[t] = res.data[t] | (1 << (i % 32));
		t--;
	}
	return res;
}

vector<bool> QFloat::QFloatToBin()
{
	vector<bool> bit;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 32; j++)
			bit.push_back(1 & (data[i] >> j));
	return bit;
}