#include "menu.h"

void textcolor(int x) //Ham to mau - Text Color
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}

void gotoxy(int x, int y) //Tu dinh nghia ham dich chuyen con tro den vi tri x, y
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1, y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void hidepointedmouse()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void showpointedmouse()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void printMenu1(int i)
{
	int y = 1, x = 22;
	textcolor(white);
	gotoxy(1, y);
	cout << "- Chon loai du lieu:\n";
	gotoxy(x, y);
	if (i == 0) textcolor(selected);
	else textcolor(gray);
	cout << "Int";

	textcolor(white);
	cout << " / ";
	
	x += 6;
	gotoxy(x, y);
	if (i == 1) textcolor(selected);
	else textcolor(gray);
	cout << "Float";
}

int TypeOfData()
{
	printMenu1(0);
	int count = 0;
	while (1)
	{
		int c = 0;
		c = _getch();
		if (c == KEY_LEFT || c == KEY_RIGHT)
		{
			count = (count + 1) % 2;
			Sleep(100);
			printMenu1(count);
		}
		if (c == KEY_ENTER) break;
	}
	textcolor(white);
	return count + 1;
}

void printMenu2(int i, bool isReal)
{
	int y = 3, x = 18;
	textcolor(white);
	gotoxy(1, y);
	cout << "- Chon he co so:\n";
	gotoxy(x, y);
	if (i == 0) textcolor(selected);
	else textcolor(gray);
	cout << "2";

	textcolor(white);
	cout << " / ";

	x += 4;
	gotoxy(x, y);
	if (i == 1) textcolor(selected);
	else textcolor(gray);
	cout << "10";

	if (isReal) return;

	textcolor(white);
	cout << " / ";

	x += 5;
	gotoxy(x, y);
	if (i == 2) textcolor(selected);
	else textcolor(gray);
	cout << "16";
}

int Base1(bool isReal)
{
	printMenu2(0, isReal);
	int count = 0;
	while (1)
	{
		int c = 0;
		c = _getch();
		if (c == KEY_LEFT || c == KEY_RIGHT)
		{
			if (!isReal)
			{
				if (c == KEY_LEFT) count = (count + 2) % 3;
				else count = (count + 1) % 3;
			}
			else count = (count + 1) % 2;
			Sleep(100);
			printMenu2(count, isReal);
		}
		if (c == KEY_ENTER) break;
	}
	textcolor(white);
	if (count == 0) return 2;
	if (count == 1) return 10;
	return 16;
}

void printMenu3(int i, bool isReal, int base1)
{
	int y = 5;
	textcolor(white);
	gotoxy(1, y);
	cout << "- Chon thao tac:\n";

	gotoxy(5, y + 1);
	if (i == 0) textcolor(selected);
	else textcolor(gray);
	if (!isReal)
		cout << "+ Chuyen doi he co so";
	else
	{
		cout << "+ Chuyen doi sang he co so ";
		if (base1 == 10) cout<< "2";
		else cout << "10";
	}

	gotoxy(5, y + 2);
	if (i == 1) textcolor(selected);
	else textcolor(gray);
	cout << "+ Tinh toan";
}

int Action(bool isReal, int base)
{
	printMenu3(0, isReal, base);
	int count = 0;
	while (1)
	{
		int c = 0;
		c = _getch();
		if (c == KEY_UP || c == KEY_DOWN)
		{
			count = (count + 1) % 2;
			Sleep(100);
			printMenu3(count, isReal, base);
		}
		if (c == KEY_ENTER) break;
	}
	textcolor(white);
	return count + 1;
}

void printMenu4(int i, int a[])
{
	int y = 9, x = 33;
	textcolor(white);
	gotoxy(1, y);
	cout << "- Chon he co so can chuyen doi:\n";
	gotoxy(x, y);
	if (i == 0) textcolor(selected);
	else textcolor(gray);
	cout << a[0];

	textcolor(white);
	cout << " / ";

	x += 4;
	if (a[0] > 2) x++;
	gotoxy(x, y);
	if (i == 1) textcolor(selected);
	else textcolor(gray);
	cout << a[1];
}

int Base2(int base1)
{
	int a[2];
	if (base1 == 10 || base1 == 16) a[0] = 2;
	else a[0] = 10;
	if (base1 == 2 || base1 == 10) a[1] = 16;
	else a[1] = 10;
	printMenu4(0, a);
	int count = 0;
	while (1)
	{
		int c = 0;
		c = _getch();
		if (c == KEY_LEFT || c == KEY_RIGHT)
		{
			count = (count + 1) % 2;
			Sleep(100);
			printMenu4(count, a);
		}
		if (c == KEY_ENTER) break;
	}
	textcolor(white);
	return a[count];
}

void printMenu5(int i, string operators[], bool isReal)
{
	int y = 9, x = 15, t = 17;
	if (isReal) t = 4;
	for (int j = 0; j < t; j++)
	{
		if (j == i) textcolor(selected);
		else textcolor(gray);
		gotoxy(x, y);
		cout << operators[j];
		x = x + operators[j].length() + 2;
	}
}

string Oper(bool isReal)
{
	gotoxy(1, 9);
	textcolor(white);
	cout << "Chon toan tu: ";
	string operators[17] = { "+","-","*", "/",">","<","==","<=",">=","&","|","^","~",">>","<<","ror","rol" };
	printMenu5(0, operators, isReal);
	int count = 0;
	int t = 17;
	if (isReal) t = 4;
	while (1)
	{
		int c = 0;
		c = _getch();
		if (c == KEY_LEFT || c == KEY_RIGHT)
		{
			if (c == KEY_LEFT) count = (count + t - 1) % t;
			else count = (count + 1) % t;
			Sleep(100);
			printMenu5(count, operators, isReal);
		}
		if (c == KEY_ENTER) break;
	}
	textcolor(white);
	return operators[count];
}

void printMenu6(int i, int y)
{
	int x = 21;
	gotoxy(x, y);
	if (i == 0) textcolor(selected);
	else textcolor(gray);
	cout << "CO";

	textcolor(white);
	cout << " / ";

	x += 5;
	gotoxy(x, y);
	if (i == 1) textcolor(selected);
	else textcolor(gray);
	cout << "KHONG";
}

bool End(int y)
{
	hidepointedmouse();
	gotoxy(1, y);
	cout << "Tiep tuc tinh toan? ";
	printMenu6(0, y);
	int count = 0;
	while (1)
	{
		int c = 0;
		c = _getch();
		if (c == KEY_LEFT || c == KEY_RIGHT)
		{
			count = (count + 1) % 2;
			Sleep(100);
			printMenu6(count, y);
		}
		if (c == KEY_ENTER) break;
	}
	textcolor(white);
	return (count == 1);
}