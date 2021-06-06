#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string toString(unsigned char x)
{
	if (x == 0) return ("0");
	string res = "";
	while (x > 0)
	{
		res = char('0' + (x % 10)) + res;
		x = x / 10;
	}
	return res;
}

void main()
{
	cout << "Name: ";
	string name;
	cin >> name;
	int length = name.length();
	if (length < 5)
	{
		cout << "The name must be at least 5 characters.\n";
		system("pause");
		return;
	}

	unsigned char tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0;
	for (int i = 0; i < length; i++) //i = EBX - 1
	{
		//EAX = length;
		//EDX = name;
		tmp1 += length;
		tmp1 += int(name[i - 0]);

		tmp2 += length - 1;
		if (i > 0) tmp2 += int(name[i - 1]);

		tmp3 += length - 2;
		if (i > 1) tmp3 += int(name[i - 2]);

		tmp4 += length - 3;
		if (i > 2) tmp4 += int(name[i - 3]);
	}

	unsigned char key[26];
	key[0] = tmp1 ^ 144;
	key[1] = tmp1 ^ 255;
	key[2] = tmp1 ^ 144;
	key[3] = tmp1 ^ 255;
	key[4] = tmp1 ^ 15;

	key[5] = tmp2 ^ 88;
	key[6] = tmp2 ^ 68;
	key[7] = tmp2 ^ 67;
	key[8] = tmp2 ^ 86;
	key[9] = tmp2 ^ 35;

	key[10] = tmp3 ^ 85;
	key[11] = tmp3 ^ 68;
	key[12] = tmp3 ^ 100;
	key[13] = tmp3 ^ 87;
	key[14] = tmp3 ^ 69;
	key[15] = tmp3 ^ 149;

	key[16] = tmp1 ^ tmp4;
	key[17] = tmp2 ^ tmp4;
	key[18] = tmp3 ^ tmp4;
	key[19] = (tmp1 + tmp2) ^ tmp4;
	key[20] = (tmp2 + tmp3) ^ tmp4;

	key[21] = int(name[0]) ^ 68;
	key[22] = int(name[1]) ^ 68;
	key[23] = int(name[2]) ^ 68;
	key[24] = int(name[3]) ^ 34;
	key[25] = int(name[4]) ^ 17;

	string serial = "";
	for (int i = 0; i < 26; i++)
		serial += toString(key[i]);
	cout << "Serial : " << serial;
	cout << "\nPlease open output.txt to copy Name & Serial.\n";

	ofstream output("output.txt");
	output << "Name: " << name;
	output << "\nSerial: " << serial;
	output.close();

	system("pause");
}