#include "function.h"

// Tach he co so tu mot chuoi (he 2, he 10, he 16)
int getRadix(size_t &startPos, size_t &foundPos, string line)
{
	foundPos = line.find(' ', startPos);
	return stoi(line.substr(startPos, foundPos - startPos));
}

// Tich phan nguyen va phan thap phan cua mot so cham dong
void SplitNumber(string &int_part, string &point_part, string number)
{
	size_t foundPos = number.find('.', 0);
	if (foundPos != string::npos) 
	// So cham dong co dau "." => int_part = phan nguyen, point_part = phan thap phan
	{
		int_part = number.substr(0, foundPos);
		int count = number.length() - foundPos - 1;
		point_part = number.substr(foundPos + 1, count);
	}
	else // So cham dong la so nguyen (vi du: 12) => int_part = phan nguyen, point_part = "0"
	{
		int_part = number;
		point_part = "0";
	}
}

// Nhan chuoi thap phan cho 2 
// => Dung de chuyen doi phan thap phan tu he 10 sang he 2
string PointMultiply2(string &a)
{
	string temp = "";
	int t = 0; // t: bien dung de nho
	
	// Nhan tung chu so cua chuoi cho 2
	for (int i = a.length() - 1; i >= 0; i--) 
	{
		int tmp = (a[i] - '0') * 2 + t;

		if ((tmp == 0 || tmp == 10) && temp.length() == 0) 
		// Loai bo so 0 vo nghia phia sau (do phan thap phan)
		{
			if (tmp == 10)
				t = 1;
			continue;
		}

		if (tmp < 10) 
		// Neu tmp = 1 -> 9 thi luu vao phia truoc bien ket qua temp
		{
			temp = (char)('0' + tmp) + temp;
			t = 0;
		}
		else
		{
			temp = (char)('0' + tmp % 10) + temp;
			t = 1;
		}
	}

	if (temp.length() == 0) // Xet truong hop ket qua = 0
		a = "0";
	else
		a = temp; // a = a * 2

	if (t == 1) // Ket qua tra ve la bit phia truoc dau "."
		return "1";
	return "0";
}

// Chia chuoi thap phan cho 2
// => Dung de in tu day bit => chuoi so cham dong he 10
void PointDivide2(string &number)
{
	string result = "";
	int miss = 0, i = 0, temp;
	do // Chia tung chu so cua chuoi cho 2
	{
		if (i < number.length()) // So chia > So bi chia
			temp = (number[i] - 48) + (miss * 10);
		else // So chia < So bi chia => Muon
			temp = miss * 10;
		miss = temp % 2; // Lay du
		i++;
		result += ((temp / 2) + 48);
	} while (miss != 0 || i < number.length()); // Ngung khi chia het hoac da duyet het chuoi so

	number = result; // number = number / 2
}

// Chuan hoa phan nguyen cua so cham dong o he 2
// Vi du: 10100.1 => 1.01001 exp = 4
void NormalizeInt(string &int_part, string &point_part, int &exp)
{
	if (int_part.compare("0") == 0) // Chuoi so co dang 0.xxx
		return;

	// Duyet nguoc phan nguyen cho den so 1 dau tien, vua duyet vua tang exp
		for (int i = int_part.length() - 1; i > 0; i--) 
	{
		point_part = int_part[i] + point_part;
		exp++;
	}

	// Chuan hoa lai chuoi
	int_part = "1";
	int temp = point_part.length();
	// So sanh do dai cua point_part hien co voi so bit co the bieu dien duoc
	point_part = point_part.substr(0, min(temp, 112)); 
}

// Chuyen tu chuoi SCD he 10 sang chuoi SCD he 2
void DecToBinFloat(string &int_part, string &point_part, int &exp)
{
	// Phan nguyen
	bool check = false;
	string result = "";
	int t = 112;

	if (int_part.compare("0") != 0) 
	// Phan nguyen !=0 => chuyen phan nguyen sang he 2
	{
		while (int_part.compare("0") != 0)
		{
			if ((int_part[int_part.length() - 1] - 48) % 2 == 0)
				result = "0" + result;
			else
				result = "1" + result;
			DecDivide2(int_part);
		}
		int_part = result;
	}
	else //phan nguyen => bo qua
		check = true;

	// Phan thap phan
	result = "";
	NormalizeInt(int_part, result, exp); // Chuan hoa phan nguyen 
	// Vd: 10001 sau khi chuan hoa int_part = 1, result = 0001

	// Chuyen phan thap phan tu he 10 sang he 2
	while (point_part.compare("0") != 0 && result.length() < t) 
	{
		string bit = PointMultiply2(point_part);

		if (check && t < 16494) t++; // Truong hop so khong chuan

		if (bit.compare("1") == 0)
			check = false;

		result = result + bit;
	}
	point_part = result;
}

// Ham chuan hoa SCD
void ToNormalize(string &int_part, string &point_part, string number, int typeOfNumber, int &exp)
{
	// Tach phan nguyen va phan thap phan cua SCD
	SplitNumber(int_part, point_part, number); 

	if (typeOfNumber == 10)
		DecToBinFloat(int_part, point_part, exp); // Doi thap phan sang nhi phan va chuan hoa
	else
		NormalizeInt(int_part, point_part, exp); // Chuan hoa SCD he 2

	if (int_part.compare("0") == 0) // Xet truong hop SCD co dang 0.xxx
	{
		int pos = 0;
		exp--;
		// Duyet cho den khi nao gap so 1 phan thap phan
		while (point_part[pos] == '0') 
		{
			pos++;
			exp--;
		}

		if (exp > -16382) // So dang chuan 
		// Vd: 0.0000101 => int_part = 1, point_part= 01, exp = -5
		{
			int_part = "1";
			pos++;
			int r = point_part.length() - pos;
			point_part = point_part.substr(pos, min(r, 112));
			if (point_part.compare("") == 0)
				point_part = "0";
		}
		else // So dang khong chuan
		{
			int r = point_part.length() - 16382;
			point_part = point_part.substr(16382, min(r, 112));
			exp = -16382;
		}
	}
}

// Tinh mu dua tren cac bit mu tu bit  112 -> 126
int Exp(vector<bool> bit)
{
	int sum = 0, power = 1;
	for (int i = 112; i < 127; i++)
	{
		if (bit[i])
			sum += power;
		power *= 2;
	}

	// Tru cho so bias
	if (sum == 0)
		return - 16382;
	else
		return sum - 16383;
}

// Chuyen tu mang vector<bool> sang chuoi he 2
void ArrayToBin(vector<bool> bit, string &int_part, string &point_part)
{
	// Xet truong hop SCD = 0
	bool isZero = true;
	for (int i = 0; i < 128; i++)
		if (bit[i])
			isZero = false;
	if (isZero)
	{
		int_part = "0";
		return;
	}

	// Tinh toan mu
	int exp = Exp(bit);
	if (exp == -16382) // So khong chuan
	{
		for (int i = 0; i < 112; i++)
		{
			if (!bit[i] && point_part.length() == 0) 
				continue; // Loai bo so 0 vo nghia
			else
				if (!bit[i])
					point_part = "0" + point_part;
				else
					point_part = "1" + point_part;
		}
		for (int i = 0; i < 16382; i++)
			point_part = "0" + point_part;
		int_part = "0";
	}
	else // So dang chuan
	{
		if (exp >= 0) // truong hop dich "." len tren phan nguyen
		{
			int_part = "1";
			int pos = 112;
			for (int i = 0; i < exp; i++)
			{
				pos--;
				if (!bit[pos])
					int_part += "0";
				else
					int_part += "1";
			}
			for (int i = 0; i < pos; i++)
			{
				if (!bit[i] && point_part.length() == 0) 
					continue; // loai bo so 0 vo nghia
				else
					if (!bit[i])
						point_part = "0" + point_part;
					else
						point_part = "1" + point_part;
			}
		}
		else // truong hop dich "." xuong phan thap phan
		{
			for (int i = 0; i < 112; i++)
			{
				if (!bit[i] && point_part.length() == 0) 
					continue; // loai bo so 0 vo nghia
				else
					if (!bit[i])
						point_part = "0" + point_part;
					else
						point_part = "1" + point_part;
			}
			point_part = "1" + point_part;
			for (int i = 0; i < abs(exp) - 1; i++)
				point_part = "0" + point_part;
			int_part = "0";
		}
	}
}

// Chuyen tu vector<bool> sang chuoi he 10
void ArrayToDec(vector<bool> bit, string &int_part, string &point_part)
{
	// Xu ly phan nguyen
	string temp_int = "1", sum_int = "0";
	for (int i = int_part.length() - 1; i >= 0; i--)
	{
		if (int_part[i] == '1')
			DecAdd(sum_int, temp_int);
		DecMultiply2(temp_int);
	}
	// Xu ly phan thap phan
	string temp_point = "5", sum_point = "0";

	for (int i = 0; i < point_part.length(); i++)
	{
		if (point_part[i] == '1')
		{
			for (int j = sum_point.length(); j < temp_point.length(); j++)
				sum_point += "0";
			DecAdd(sum_point, temp_point);
		}
		PointDivide2(temp_point);
	}

	int_part = sum_int;
	point_part = sum_point;
}