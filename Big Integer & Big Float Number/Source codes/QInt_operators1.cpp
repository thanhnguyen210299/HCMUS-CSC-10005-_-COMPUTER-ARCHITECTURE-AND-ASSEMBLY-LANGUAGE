#include "QInt.h"

//cong hai day bit, moi day co numberOfBit bit
QInt QInt::BitAdd(QInt a, QInt b, int numberOfBit)
{
	vector<bool> bit1 = a.QIntToBin();
	vector<bool> bit2 = b.QIntToBin();
	vector<bool> res;
	int i = 0, t = 0; //t: bien nho
	while (i < numberOfBit)
	{
		int tmp = bit1[i] + bit2[i] + t;
		if (tmp > 1) // co nho
		{
			res.push_back(tmp % 2);
			t = 1;
		}
		else // khong co nho
		{
			res.push_back(tmp);
			t = 0;
		}
		i++;
	}
	if (t == 1) //con nho, neu do dai vuot qua so bit thi bo qua
		while (res.size() < numberOfBit) res.push_back(1);
	while (res.size() < 128) res.push_back(0);
	return QInt::BinToQInt(res);
}

//tru hai day bit, moi day co numberOfBit bit
QInt QInt::BitSub(QInt a, QInt b, int numberOfBit)
{
	vector<bool> bit1 = a.QIntToBin();
	vector<bool> bit2 = b.QIntToBin();
	vector<bool> res;
	int i = 0, t = 0; //t: bien nho
	while (i < numberOfBit)
	{
		int tmp = bit1[i] - bit2[i] - t;
		if (tmp < 0) // co nho
		{
			res.push_back((-tmp) % 2);
			t = 1;
		}
		else // ko nho
		{
			res.push_back(tmp);
			t = 0;
		}
		i++;
	}
	if (t == 1) // con nho, neu do dai da vuot qua so bit thi bo qua
		while (res.size() < numberOfBit) res.push_back(1);
	while (res.size() < 128) res.push_back(0);
	return QInt::BinToQInt(res);
}

QInt QInt::operator+(QInt &other)
{
	QInt res = BitAdd(*this, other, 128);
	bool x = getBit(127);
	// cong hai so cung dau, kq khac dau toan hang -> tran so
	if (x == other.getBit(127) && x != res.getBit(127))
		throw "OVERFLOW";
	return res;
}

QInt QInt::operator-(QInt &other)
{
	//a + b = a + (-b)
	vector<bool> bit = other.QIntToBin();
	//lay so bu 2
	TwoComplement(bit);
	QInt tmp = BinToQInt(bit);
	try
	{
		return *this + tmp;
	}
	catch (const char*msg)
	{
		throw msg;
	}
}

QInt QInt::operator*(QInt &M)
{
	if (getBit(127) == 0 && M.getBit(127) == 0)
		return UnsignedMultiply(M);
	else
		return SignedMultiply(M);
}

//nhan co dau bang thuat toan Booth
QInt QInt::SignedMultiply(QInt &M)
{
	QInt A;
	if (*this == A || M == A) return A;
	QInt Q = *this;
	if (Q.getBit(127) != 1) return M.SignedMultiply(Q);

	bool sign = Q.getBit(127) ^ M.getBit(127); //dau cua kq

	bool Q_1 = 0;
	for (int count = 0; count < 128; count++)
	{
		bool Q0 = 1 & Q.data[0];
		if (Q0 != Q_1)
			if (Q0 == 1) A = BitSub(A, M, 128); // A = A - M
			else A = BitAdd(A, M, 128); // A = A + M

			//cap nhat Q_1 truoc khi dich day bit
			Q_1 = 1 & Q.data[0];

			//giu lai bit cuoi cua A 
			bool bit = 1 & (A.data[0]);
			A >> 1;
			Q >> 1;
			A.setBit(127, A.getBit(126));
			//set MSB cua Q = bit cuoi cua A
			Q.setBit(127, bit); 
	}

	//ktra tran so
	if (Q.getBit(127) != sign) throw "OVERFLOW";
	return Q;
}

//nhan khong dau
QInt QInt::UnsignedMultiply(QInt &M)
{
	QInt A;
	if (*this == A || M == A) return A;
	QInt Q = *this;

	int Q_MSB = Q.MSBpos();
	int M_MSB = M.MSBpos();
	if (M_MSB < Q_MSB) return M.UnsignedMultiply(Q);

	bool C = 0;
	for (int count = 0; count <= Q_MSB; count++)
	{
		if ((1 & Q.data[0]) == 1) //if Q0 = 1
		{
			//giu lai hai bit dau cua A va M de ktra nho
			bool t1 = A.getBit(M_MSB);
			bool t2 = M.getBit(M_MSB);
			A = BitAdd(A, M, M_MSB + 1); //A = A + M
			
			//neu t1+t2 != bit dau cua A -> co nho -> C=1
			if ((!(t1 == 0 && t2 == 0)) && (t1 + t2 != A.getBit(M_MSB)))
				C = 1;
			else C = 0;
		}

		//giu lai bit cuoi cua A 
		bool bit = 1 & (A.data[0]);
		A >> 1;
		A.setBit(M_MSB, C);
		C = 0;
		Q >> 1;
		//set MSB cua Q = bit cuoi cua A
		Q.setBit(Q_MSB, bit); 
	}

	//ghep KQ vao A
	A << (Q_MSB + 1);
	for (int i = Q_MSB; i >= 0; i--)
		A.setBit(i, Q.getBit(i));

	//ktra tran so
	if (0 != A.getBit(127)) throw "OVERFLOW";
	return A;
}

QInt QInt::operator/(QInt &M)
{
	QInt A;
	QInt Q = *this;
	QInt zero;

	if (M == zero) //so bi chia = 0
	{
		throw "INVALID DIVISOR";
	}
	if (Q == zero) return zero;

	//xet dau Q va M
	bool sameSign = true;
	if (Q.getBit(127) != M.getBit(127))
		sameSign = false;

	if (Q.getBit(127) == 1) // Q < 0
	{
		//khoi tao A = 11111...111
		for (int i = 0; i < 4; i++)
			A.setData(i, -1);
	}

	//truong hop |Q| < |M| -> return 0
	if (sameSign)
	{
		if ((Q > zero && Q < M) || (Q<zero && Q>M)) return zero;
	}
	else
	{
		if (Q < zero && zero - Q < M) return zero;
		if (Q > zero && Q < zero - M) return zero;
	}

	//lay MSB + 1 bit de chia -> giam bot so buoc can lap
	int MSB = Q.MSBpos() + 1;
	for (int count = 0; count <= MSB; count++)
	{
		bool tmp = Q.getBit(MSB);
		A << 1;
		Q << 1;
		A.setBit(0, tmp);

		QInt B = A; //luu lai A truoc khi thay doi
		//xet dau A va M
		if (A.getBit(MSB) == M.getBit(MSB)) //cung dau
			A = BitSub(A, M, MSB + 1); // A = A - M
		else //khac dau
			A = BitAdd(A, M, MSB + 1); // A = A + M

		//set bit cuoi cung cua Q = 0 hoac 1
		if (A.getBit(MSB) == B.getBit(MSB) || (A == zero && Q == zero))
		{
			//A va B cung dau hoac A = Q = 0
			Q.setBit(0, 1);
		}
		else
		{
			Q.setBit(0, 0);
			A = B; //khoi phuc A
		}
	}

	//lay ket qua
	//chuyen tu MSB-bit sang 128bit
	bool tmp = Q.getBit(MSB);
	for (int i = 127; i > MSB; i--)
		Q.setBit(i, tmp);

	//doi dau thuong neu Q va M khac dau
	if (!sameSign) Q = zero - Q;

	//lay so du
	tmp = A.getBit(MSB);
	for (int i = 127; i > MSB; i--)
		A.setBit(i, tmp);

	//truong hop chia het: so du = +- so chia 
	if ((sameSign && A == M) || (!sameSign && A + M == zero))
	{
		QInt one;
		one.setData(0, 1);
		if (Q > zero) Q = Q + one;
		else Q = Q - one;
	}
	return Q;
}
