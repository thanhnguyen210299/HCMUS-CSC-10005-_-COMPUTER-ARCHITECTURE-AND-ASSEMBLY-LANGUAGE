#include <iostream>
#include <string>
#include <fstream>
using namespace std;


char repeat(char name, char X)
{
	string size_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.,";
	int c, tmp;
	do {
		c = rand() % 66; // 66 = size_table.length();
		tmp = ((int)size_table[c] ^ (int)name) % 10;
	} while (tmp != (int)(X - 48)); // chuyển X từ ký tự sang hệ thập phân

	return size_table[c];
}

string solve_Problem(string username)
{
	// Các trường hợp username không hợp lệ
	string res = "";
	// 1. Chỉ một ký tự
	if (username.length() == 1)	return res;
	// 2. Tồn tại ký tự dấu {',', '!',...}
	for (int i = 0; i < username.length(); i++)
	{
		if (username[i] < 'A' || username[i] > 'Z')
		{
			if (username[i] < 'a' || username[i] > 'z')
			{
				if (username[i] < '0' || username[i] > '9')
				{
					if (username[i] != '-' && username[i] != '_')
						return res;
				}
			}
		}
	}

	// Trường hợp username hợp lệ
	string X = "7815952891489145618"; //tìm bằng thuật toán RSA (X: biến đặt đồng nhất với trong báo cáo)
	string tmp = username;

	// Cộng chuỗi khi độ dài username < 19 = X.length()
	while (tmp.length() < X.length())
		tmp += username;

	for (int i = 0; i < X.length(); i++)
		res += repeat(tmp[i], X[i]);

	return res;
}

void main()
{
	string username;
	string serial;
	do
	{
		cout << "Input username: ";
		scanf_s("\n");
		getline(cin, username);

		serial = solve_Problem(username);
		if (serial == "")
		{
			cout << "Username is not valid!!\n\n";
			cout << "__INPUT AGAIN__\n";
		}
	} while (serial == "");

	cout << "Valid serial: ";
	cout << serial << endl;
	cout << "\nPlease open output.txt to copy Name & Serial.\n";

	ofstream output("output.txt");
	output << "Username: " << username;
	output << "\nSerial: " << serial;
	output.close();

	system("pause");
}
