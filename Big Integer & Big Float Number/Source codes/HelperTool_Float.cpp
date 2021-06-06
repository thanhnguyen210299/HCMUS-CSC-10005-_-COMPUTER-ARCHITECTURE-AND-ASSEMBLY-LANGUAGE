#include "HelperTool.h"

string FloatConvertTool(string number, int typeOfNumber, int typeChange)
{
	// Thuc hien yeu cau
//	vector<bool> temp = FloatStrToArray(number, typeOfNumber);
	vector<bool> temp;
	if (typeOfNumber == 2)
	{
		for (int i = 127; i >= 0; i--)
			if (number[i] == '1') temp.push_back(1);
			else temp.push_back(0);
	}
	else temp = FloatStrToArray(number, typeOfNumber);
	QFloat n = n.BinToQFloat(temp);
	return n.toString(typeChange);
}

string Calculate_Float(QFloat a, QFloat b, int typeNumber, string typeOperator)
{

	string operators[4] = { "+", "-", "*", "/" };
	QFloat result;
	int i;
	for (i = 0; i < 4; i++)
		if (typeOperator.compare(operators[i]) == 0)
			break;


	switch (i)
	{
	case 0: result = a + b; break;
	case 1: result = a - b; break;
	case 2: result = a * b; break;
	default:
	{
		QFloat zero;
		if (b == zero) return "INVALID DIVISOR";
		result = a / b; break;
	}
	}
	return result.toString(typeNumber);
}