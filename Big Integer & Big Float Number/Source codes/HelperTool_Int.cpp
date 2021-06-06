#include "HelperTool.h"

string IntConvertTool(string number, int typeOfNumber, int typeChange)
{
	// Thuc hien yeu cau
	if (typeOfNumber == 10 && typeChange == 2)
	{
		// Chuyen truc tiep tu DEC qua BIN, ko can luu vao QInt
		return Show(DecStrToArray(number));
	}
	else
	{
		QInt n = n.BinToQInt(ChangeStrToArray(number, typeOfNumber));
		return n.toString(typeChange);
	}
}

string UnaryOperator(int typeOfNumber, string number)
{
	QInt n = n.BinToQInt(ChangeStrToArray(number, typeOfNumber));
	n = ~n;
	return n.toString(typeOfNumber);
}

string Calculate1_Int(QInt &number, int numberOfBit, int typeNumber, string typeOperator)
{
	if (typeOperator.compare(">>") == 0)
		number >> numberOfBit;
	else if (typeOperator.compare("<<") == 0)
		number << numberOfBit;
	else if (typeOperator.compare("rol") == 0)
		number.rol(numberOfBit);
	else if (typeOperator.compare("ror") == 0)
		number.ror(numberOfBit);
	return number.toString(typeNumber);
}


string Calculate2_Int(QInt a, QInt b, int typeNumber, string typeOperator)
{
	string operators[12] = { "+", "-", "*", "/", "<", ">", "==", "<=", ">=", "&", "|", "^" };
	QInt result;
	int i;
	for (i = 0; i < 12; i++)
		if (typeOperator.compare(operators[i]) == 0)
			break;
	string T = "TRUE";
	string F = "FALSE";
	try
	{
		switch (i)
		{
		case 0: result = a + b; break;
		case 1: result = a - b; break;
		case 2: result = a * b; break;
		case 3: result = a / b; break;
		case 4: if (a < b) return T; else return F; break;
		case 5: if (a > b) return T; else return F; break;
		case 6: if (a == b) return T; else return F; break;
		case 7: if (a <= b) return T; else return F;  break;
		case 8: if (a >= b) return T; else return F; break;
		case 9: result = a & b; break;
		case 10: result = a | b; break;
		case 11: result = a ^ b; break;
		}
	}
	catch (const char*msg)
	{
		return msg;
	}
	return result.toString(typeNumber);
}