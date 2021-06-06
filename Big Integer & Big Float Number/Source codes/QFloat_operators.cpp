#include "QFloat.h"

// Cong 2 day bit co chieu dai bang nhau
vector<bool> QFloat::add(vector<bool> bit1, vector<bool> bit2)
{
	vector<bool> res;
	int i = 0, t = 0;
	while (i < bit1.size())
	{
		int tmp = bit1[i] + bit2[i] + t;
		if (tmp > 1)
		{
			res.push_back(tmp % 2);
			t = 1;
		}
		else
		{
			res.push_back(tmp);
			t = 0;
		}
		i++;
	}
	if (t == 1) res.push_back(1);
	return res;
}

vector<bool> QFloat::convert_sign(vector<bool> bit) // bit: co the chua nhung bit vo nghia
{
	vector<bool> res;
	for (int i = 0; i < bit.size(); i++)
	{
		res.push_back(0);
	}
	int j;
	for (int i = 0; i < bit.size(); i++)
	{
		if (bit[i] == 1)
		{
			j = i;
			break;
		}
	}

	// Dao bit
	for (int i = j; i < bit.size(); i++)
	{
		bit[i] = !bit[i];
	}

	// Cong voi bit 1
	for (int i = 0; i < res.size(); i++)
	{
		if (i == j) res[i] = 1;
	}
	vector<bool> sum;
	sum = add(bit, res);
	return sum;
}

QFloat QFloat::operator+(QFloat &other)
{
	vector<bool> bit1 = QFloatToBin(), bit2 = other.QFloatToBin();
	vector<bool> res, tmp;
	vector<bool> s1, s2; // Luu phan dinh tri
	vector<bool> res_0; // Luu so 0
	for (int i = 0; i < 128; i++)
	{
		res_0.push_back(0);
	}
	int e1, e2, e; // Tinh so mu cua hai so
	e1 = Exp(bit1);
	e2 = Exp(bit2);

	bool sign; // Luu dau cua ket qua
	int diff_e = abs(e1 - e2); // Do chenh lech hai so mu

	// Dich day bit phan tri sang phai tuong ung voi do lech hai so mu
	if (e1 < e2)
	{
		e = e2;
		for (int i = 0; i < diff_e; i++)
			s1.push_back(0);
	}
	else
	{
		e = e1;
		for (int i = 0; i < diff_e; i++)
			s2.push_back(0);
	}

	if (e1 == -16382) s1.push_back(0); // So khong chuan
	else s1.push_back(1); // So chuan

	if (e2 == -16382) s2.push_back(0); // So khong chuan
	else s2.push_back(1); // So chuan

	for (int i = 111; i >= 0; i--)
	{
		if (s1.size() < 112) s1.push_back(bit1[i]);
		if (s2.size() < 112) s2.push_back(bit2[i]);
	}
	for (int i = 0; i < s1.size() / 2; i++)
	{
		swap(s1[i], s1[111 - i]);
		swap(s2[i], s2[111 - i]);
	}

	if (bit1[127] == bit2[127]) // cong cung dau
	{
		sign = bit1[127];
		// Cong phan dinh tri cua hai so & xac dinh qua cua ket qua
		tmp = add(s1, s2);
	}
	else // cong khac dau
	{
		// Lay dau cho ket qua
		bit1[127] = !bit1[127];
		QFloat k = BinToQFloat(bit1);
		if (k < other) sign = bit2[127];
		else if (k == other) return BinToQFloat(res_0); // Truong hop hai toan hang khac dau va tri tuyet doi hai toan hang bang nhau 
		else sign = !bit1[127];

		vector<bool> s1_new, s2_new, t, count, temp;
		// Lua chon so hang de thuc hien phep bu 2
		if (e1 == e2)
		{
			if (k < other)
			{
				count = s1;
				s2_new = s2;
			}
			else
			{
				count = s2;
				s2_new = s1;
			}
		}
		else if (e1 > e2)
		{
			count = s2;
			s2_new = s1;
		}
		else
		{
			count = s1;
			s2_new = s2;
		}
		temp = convert_sign(count);

		// Xu ly hai day bit phan dinh tri -> cung chieu dai
		int j = temp.size() - s1.size();
		for (int i = j; i < temp.size(); i++)
			s1_new.push_back(temp[i]);
		// Cong hai day bit cung chieu dai
		t = add(s1_new, s2_new);

		// Xac dinh day bit phan dinh tri co nghia
		int c = -1;
		for (int i = 0; i < t.size(); i++)
		{
			if (t.size() != count.size())
			{
				if (t[i] == 1 && i != t.size() - 1) c = i;
			}
			else
			{
				if (t[i] == 1) c = i;
			}
		}
		for (int i = 0; i <= c; i++)
			tmp.push_back(t[i]);
	}

	int distance_exp = tmp.size() - 112; // Do lech chieu dai day bit phan dinh tri
	e = e + distance_exp; // thiet lap lai so mu cua ket qua
	if (distance_exp <= 0)
	{
		for (int i = 0; i <= -distance_exp; i++)
			res.push_back(0); // Them bit 0 de du 112 bit phan dinh tri
	}
	// Ket qua phan dinh tri
	for (int i = 0; i < tmp.size() - 1; i++)
		res.push_back(tmp[i]);

	// Bieu dien Bias cho phan mu
	if (e != -16382)
	{
		e += 16383;
		// Chuyen tu so nguyen sang day bit
		while (e != 0)
		{
			res.push_back(e % 2);
			e /= 2;
		}
		while (res.size() < 127)
		{
			res.push_back(0);
		}
	}

	// Ket qua phan dau
	res.push_back(sign);
	return BinToQFloat(res);
}

QFloat QFloat::operator-(QFloat &other)
{
	vector<bool> bit1 = QFloatToBin();
	vector<bool> bit2 = other.QFloatToBin();

	// Truong hop hai toan hang bang nhau va cung dau
	if (bit1[127] == bit2[127] && *this == other)
	{
		vector<bool> res_0; // Luu so 0
		for (int i = 0; i < 128; i++)
		{
			res_0.push_back(0);
		}
		return BinToQFloat(res_0);
	}

	//Doi dau so tru -> thuc hien phep cong
	if (bit2[127] == 1) bit2[127] = 0;
	else bit2[127] = 1;

	QFloat tmp = BinToQFloat(bit2);
	return tmp + *this;
}

QFloat QFloat::operator*(QFloat &other)
{
	//xu ly truong hop toan hang = 0
	QFloat zero;
	if (*this == zero || other == zero) return zero;
	vector<bool> bit1 = QFloatToBin();
	vector<bool> bit2 = other.QFloatToBin();

	//xet dau 2 toan hang
	bool sameSign = true;
	if (bit1[127] != bit2[127]) sameSign = false;

	//Xet toan hang thu nhat
	bool normal = true; 
	int exp1 = Exp(bit1); //so mu 
	if (exp1 == -16382) //so ko chuan
		normal = false;

	vector<bool> bitA; //chua phan dinh tri 
	int i;
	//loai bo cac so 0 vo nghia o phan dinh tri
	for (i = 0; i < 112; i++) 
		if (bit1[i] != 0) break;

	//do chi bieu dien dc 112 bit phan tri 
	//-> lay toi da 60 bit co nghia cua moi toan hang de nhan
	for (int j = max(i, 111 - 60); j < 112; j++)
	{
		exp1--;
		bitA.push_back(bit1[j]);
	}

	//neu la so chuan thi them 1 vao dau day bit
	if (normal) bitA.push_back(1); 
	while (bitA.size() < 128) bitA.push_back(0);
	QInt A = QInt::BinToQInt(bitA);

	//Xet toan hang thu 2
	normal = true;
	int exp2 = Exp(bit2); //so mu
	if (exp2 == -16382) //so ko chuan
		normal = false;

	vector<bool> bitB; //chua phan dinh tri
	//loai bo bit 0 vo nghia
	for (i = 0; i < 112; i++)
		if (bit2[i] != 0) break;
	//lay toi da 60 bit co nghia de nhan
	for (int j = max(i, 111 - 60); j < 112; j++)
	{
		exp2--;
		bitB.push_back(bit2[j]);
	}

	//neu la so chuan thi them 1 vao dau day bit
	if (normal) bitB.push_back(1);
	while (bitB.size() < 128) bitB.push_back(0);
	QInt B = QInt::BinToQInt(bitB);

	int expRes = exp1 + exp2; //so mu cua kq
	QInt C = A * B;
	vector<bool> bitRes = C.QIntToBin();

	string number = ""; //luu kq

	for (i = 127; i >= 0; i--)
		if (bitRes[i] != 0) break;

	//dich chuyen dau phay
	if (expRes >= 0) //so mu duong -> dich dau phay sang phai
	{
		for (int j = i; j >= 0; j--)
		{
			if (bitRes[j] == 1) number = number + "1";
			else number = number + "0";
		}
		for (int j = 0; j < expRes; j++)
			number = number + "0";
		number = number + ".0";
	}
	else //so mu am -> dich dau phay sang trai
	{
		for (int j = i; j >= 0; j--)
		{
			if (bitRes[j] == 1) number = number + "1";
			else number = number + "0";
			if (j == -expRes) number = number + ".";
		}
		if (i < -expRes) 
		//dich het nhung chua du bit -> them bit 0 vao dau
		{
			for (int j = 1; j < -expRes - i; j++)
				number = "0" + number;
			number = "0." + number;
		}
	}
	//dau kq
	if (!sameSign) number = "-" + number;
	bitRes = FloatStrToArray(number, 2);

	return BinToQFloat(bitRes);
}

QFloat QFloat::operator/(QFloat &other)
{
	vector<bool> res;
	vector<bool> bit1 = QFloatToBin(), bit2 = other.QFloatToBin();
	vector<bool> s1, s2; // Luu phan dinh tri
	int e1 = Exp(bit1), e2 = Exp(bit2); // So mu hai so he 10
	for (int i = 0; i < 128; i++)
	{
		res.push_back(0);
		s1.push_back(0);
		s2.push_back(0);
	}
	QFloat zero_float;
	QInt zero_int;

	//phep chia cho 0
	if (other == zero_float)
	{
		throw "INVALID DIVISOR";
	}

	//so chia = 0
	if (*this == zero_float) return BinToQFloat(res);

	// XU LY PHAN DAU CHO KET QUA												  
	bool sign;
	if (bit1[127] ^ bit2[127] == 1) sign = 1;
	else sign = 0;
	res[127] = sign;

	// XU LY PHAN DINH TRI
	if (*this == other || *this + other == zero_float)
	{
		// Truong hop hai so bang nhau hoac doi nhau 
		//-> phan tri 0000....(112 bits), phan mu 0111....1 (15 bits)
		for (int i = 125; i >= 112; i--) res[i] = 1;
		return BinToQFloat(res);
	}

	// Chuyen vector<bool> qua string de lay gia tri phan dinh tri (So bi chia)
	string int_part = "", point_part = "";
	ArrayToBin(bit1, int_part, point_part);

	int e;
	e = e1 - e2; //Luu mu cua ket qua

	// Dua chuoi vao lai vector
	// (vd: "1010110" = > vector co dang : 0 101011000..00)
		int i = 126;
	for (int j = 0; j < int_part.length(); j++)
	{
		if (i == 126 && int_part[j] == '0')
			continue;
		if (int_part[j] == '1')
			s1[i] = 1;
		else
			s1[i] = 0;
		i--;
	}
	for (int j = 0; j < point_part.length(); j++)
	{
		if (i == 126 && point_part[j] == '0')
			continue;
		if (point_part[j] == '1')
			s1[i] = 1;
		else
			s1[i] = 0;
		i--;
	}

	// Chuyen vector<bool> qua string de lay gia tri phan dinh tri (So chia)
	int_part = ""; point_part = "";
	ArrayToBin(bit2, int_part, point_part);

	// Dua chuoi vao lai vector
	// (vd: "1010110" = > vector co dang : 00...001010110)
	i = 0;
	for (int j = point_part.length() - 1; j >= 0; j--)
	{
		if (point_part[j] == '1')
			s2[i] = 1;
		else
			s2[i] = 0;
		i++;
	}
	for (int j = int_part.length() - 1; j >= 0; j--)
	{
		if (int_part[j] == '1')
			s2[i] = 1;
		else
			s2[i] = 0;
		i++;
	}
	i = 126;
	while (!s2[i]) // lay vi tri cua bit ket qua can xu ly (vi du: chieu dai so bi chia >= chieu dai so chia => loai bo so 0 vo nghia cua phep chia)
		i--;
	int length = i;

	// dua so chia va so bi chia vao QInt 
	// => Thuc hien chia tren so nguyen
	QInt Q = QInt::BinToQInt(s1), M = QInt::BinToQInt(s2);
	QInt r = Q / M;
	vector<bool> result_sign = r.QIntToBin();

	// Chuan hoa lai ket qua
	i = 126 - length;
	while (!result_sign[i])
	{
		i--;
		e--;
	}

	// Luu ket qua vao vector theo dang so cham dong
	int j = 111;
	for (j = 111; j >= 0; j--)
	{
		i--;
		if (i >= 0)
			res[j] = result_sign[i];
		else
			break;
	}

	// Dua phan mu vao mang bit
	if (e != -16382)
	{
		e += 16383;
		int pos = 112;
		// Chuyen tu so nguyen sang day bit
		while (e != 0)
		{
			res[pos] = e % 2;
			e /= 2;
			pos++;
		}
	}
	return BinToQFloat(res);
}