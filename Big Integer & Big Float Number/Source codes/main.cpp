#include "SolveFile.h"
#include "menu.h"

string toString(int x);

void main(int argc, char *argv[])
{
	if (argc == 1)
	{
		bool end = false;
		while (!end)
		{
			system("cls");
			hidepointedmouse();
			int tmp, base;

			tmp = TypeOfData();
			bool isReal = (tmp == 2);

			base = Base1(isReal);
			string line = toString(base);

			tmp = Action(isReal, base);
			int y = 11;
			if (tmp == 1) //yc chuyen doi he co so
			{
				if (isReal) y = 9;
				if (!isReal)
				{
					base = Base2(base);
					gotoxy(1, y);
				}
				else
				{
					if (base == 2) base = 10;
					else base = 2;
					gotoxy(1, y);
				}
				line = line + " " + toString(base);
				cout << "Nhap gia tri can chuyen doi: ";
				string s;
				gotoxy(1 + 29, y);
				showpointedmouse();
				cin >> s;
				line = line + " " + s;
				y = y + 2;
			}
			else // yc tinh toan
			{
				hidepointedmouse();
				string oper = Oper(isReal);

				gotoxy(1, y);
				string a;
				if (oper.compare("~") == 0)
				{
					cout << "Nhap toan hang: ";
					gotoxy(17, y);
				}
				else
				{
					cout << "Nhap toan hang thu nhat: ";
					gotoxy(26, y);
				}
				showpointedmouse();
				cin >> a;

				line = line + " " + a + " " + oper;
				y = y + 2;

				if (oper.compare("~") != 0)
				{
					gotoxy(1, y);
					cout << "Nhap toan hang thu hai: ";
					string b;
					gotoxy(1 + 24, y);
					showpointedmouse();
					getchar();
					cin >> b;
					line = line + " " + b;
					y = y + 2;
				}
			}
			gotoxy(1, y);
			textcolor(red);
			cout << "KET QUA: ";
			textcolor(selected);
			cout << SolveLine(line, isReal) << endl << endl;
			textcolor(white);
			end = End(y + 3);
			cout << endl;
		}
		
	}
	else
	{
		bool isReal = (argv[3][0] == '2');
		Solve(argv[1], argv[2], isReal);
	}
}

string toString(int x)
{
	if (x == 2) return "2";
	else if (x == 10) return "10";
	else if (x == 16)return "16";
}