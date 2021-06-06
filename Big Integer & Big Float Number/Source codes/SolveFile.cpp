#include "SolveFile.h"

void Solve(string fileIn, string fileOut, bool isReal)
{
	ifstream in;
	ofstream out;
	in.open(fileIn);
	out.open(fileOut);
	string line;
	while (getline(in, line))
	{
		out << SolveLine(line, isReal) << endl;		
	}
	in.close();
	out.close();
}

string SolveLine(string line, bool isReal)
{
	// TACH CHUOI 

	// Kiem tra kieu so bieu dien (so nguyen, so cham dong)
//	bool isReal = IsReal(line);

	// Luu loai so (he 2, he 10, he 16)
	size_t startPos = 0, foundPos;
	int typeOfNumber = getRadix(startPos, foundPos, line);

	// Xu li loai toan tu (Chuyen doi, tinh toan) 
//	startPos = foundPos + 1;
//	foundPos = line.find(' ', startPos);

	startPos = foundPos + 1;
	foundPos = line.find(' ', startPos);
	if (line[foundPos - 1] == '~')
	{
		startPos = foundPos + 1;
		int count = line.length() - startPos;
		string number = line.substr(startPos, count);
		return UnaryOperator(typeOfNumber, number);
	}
	if (line[foundPos - 3] == 'r')
	{
		string typeOperator = line.substr(startPos, foundPos - startPos);
		startPos = foundPos + 1;
		int count = line.length() - startPos;
		string number = line.substr(startPos, count);

	//	int numberOfBit = number.length() + 1;
		vector <bool> bit = ChangeStrToArray(number, typeOfNumber);
		
		QInt n = n.BinToQInt(bit);
		int numberOfBit = 1;
		return Calculate1_Int(n, numberOfBit, typeOfNumber, typeOperator);
	}
//	if (typeOperator == "ror" || typeOperator == "rol")
	// Yeu cau Chuyen doi he 
	if ((line[foundPos + 1] >= 'A' && line[foundPos + 1] <= 'F') || (line[foundPos + 1] >= '0' && line[foundPos + 1] <= '9') || (line[foundPos + 1] == '-' && line[foundPos + 2] != ' ')) // Dang chuyen doi tu he nay sang he khac
	{
		// Tach he can chuyen
		int typeChange = getRadix(startPos, foundPos, line);

		// Tach so can chuyen
		startPos = foundPos + 1;
		int count = line.length() - startPos;
		string number = line.substr(startPos, count);

		// Thuc hien yeu cau
		if (!isReal)
			return IntConvertTool(number, typeOfNumber, typeChange);
		else
			return FloatConvertTool(number, typeOfNumber, typeChange);
	}
	// Yeu cau Tinh toan
	else
	{
		// Tach so thu 1
		string number1 = line.substr(startPos, foundPos - startPos);

		// Tach toan tu
		startPos = foundPos + 1;
		foundPos = line.find(' ', startPos);
		string typeOperator = line.substr(startPos, foundPos - startPos);

		// Tach so thu 2
		startPos = foundPos + 1;
		int count = line.length() - startPos;
		string number2 = line.substr(startPos, count);

		// Dich phai, dich trai, xoay
		string tmp[] = { ">>", "<<", "ror", "rol" };
		for (int i = 0; i < 4; i++)
			if (typeOperator.compare(tmp[i]) == 0)
			{
				int numberOfBit = DecStrToDec(number2);
				QInt n = n.BinToQInt(ChangeStrToArray(number1, typeOfNumber));
				return Calculate1_Int(n, numberOfBit, typeOfNumber, typeOperator);
			}

		if (typeOperator.compare("~") == 0)
		{
			return UnaryOperator(typeOfNumber, number1);
		}
	//	if (number1.find(".") == string::npos && number2.find(".") == string::npos)
		if (!isReal)
		{
			// toan tu 2 ngoi: +, -, *, /, AND, OR, XOR, so sanh
			QInt n1 = n1.BinToQInt(ChangeStrToArray(number1, typeOfNumber));
			QInt n2 = n2.BinToQInt(ChangeStrToArray(number2, typeOfNumber));
			return Calculate2_Int(n1, n2, typeOfNumber, typeOperator);
		}
		else
		{
			// toan tu 2 ngoi: +, - ,* ,/ tren so cham dong
			QFloat f1 = f1.BinToQFloat(FloatStrToArray(number1, typeOfNumber));
			QFloat f2 = f2.BinToQFloat(FloatStrToArray(number2, typeOfNumber));
			return Calculate_Float(f1, f2, typeOfNumber, typeOperator);
		}
	}
}