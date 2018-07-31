#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <windows.h>
#define getch _getch
#define mapsz 30

using namespace std;

/*Game Of Life*/

int a(0);//temporary x position	
int b(0);//temporary y position
int pos[mapsz][mapsz] = { {0},{0} };//2-dimentional array for cartesian croodinate system

void gotoxy(int x, int y)//responsible for moving the cusor on the screen
{
	COORD tmp = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp);
}

void init()//initialization
{
	cout << "Press any key to start..." << endl;
	getch();
	system("cls");
	return;
}

void mapgen()//map generator (mapsz*mapsz)
{
	for (int i(0); i < mapsz + 1 ; i += 1)
	{
		gotoxy(2*(mapsz + 1), i);
		cout << "|";
	}
	gotoxy(0, mapsz + 1);
	cout << "--------------------------------------------------------------";
	return;
}

void position()//controls position of the cusor(H) and writes position of the 'p' to pos array
{
	char input(0);
	//int i(0);
	while (input != 'n')
	{
		//gotoxy(2 * (mapsz + 3), i);
		//if (pos[a][b]) cout << "Placement: " << "(" << a << "," << b << ")";
		//else cout << "(" << a << "," << b << ")" << "		";
		gotoxy(2 *a, b);
		if (pos[a][b] == 0) cout << "H";
		if (pos[a][b] == 1) cout << "p";
		input = getch();
		gotoxy(2 * a, b);
		if (pos[a][b] == 0) cout << " ";
		switch (input)
		{
		case 'w':
			if (b)//cusor position restriction.
			b -= 1;
			break;
		case 'a':
			if (a)//cusor position restriction.
			a -= 1;
			break;
		case 's':
			if (b - mapsz)//cusor position restriction.
			b += 1;
			break;
		case 'd':
			if (a - mapsz)//cusor position restriction.
			a += 1;
			break;
		case ' ':
			if (pos[a][b] == 0) pos[a][b] = 1;//placement('p') toggle
			else pos[a][b] = 0;
			break;
		}
		//i += 1;
	}
	return;
}

void iteration()//responsible for computing and displaying iterated result
{
	int count;//stores the number of 'p' around certain position
	int tmp;//stores the number of needed modification

	while (getch() != 'q')
	{
		unsigned int secposxc[10000]{ NULL };//second x coordinate
		unsigned int secposyc[10000]{ NULL };//second y coordinate
		tmp = 0;
			for (int i(0); i < mapsz; i += 1)
			{
				for (int j(0); j < mapsz; j += 1)
				{
					count = 0;
					for (int k(0); k < 3; k += 1) for (int l(0); l < 3; l += 1) if (((-1 < j) && (j < (mapsz + 2))) && ((-1 < i) && (i < (mapsz + 2))))
					{
						//gotoxy(2*(j + l - 1), i + k - 1);
						//cout << "D";
						count += pos[j + l - 1][i + k - 1];//counts the number of the 'p' around position(j, i)
						getch();
					}
					if (pos[j][i]) count -= 1;//prevents counting 'p' in the middle of 3*3 square
					gotoxy(2 * (mapsz + 3), i);
					cout << "                   ";
					gotoxy(2 * (mapsz + 3), i);
					cout << "Count: " << count << endl;
					gotoxy(2 * j, i);
					switch (count)//Rules of GOL(GameOfLife)
					{
					case 0:
						break;
					case 1:
						if (pos[j][i]) secposxc[tmp] = j; secposyc[tmp] = i;//records modificated position of 'p'
						cout << " ";
						tmp += 1;
						break;
					case 2:
						break;
					case 3:
						if (pos[j][i] + 1)
						{
							secposxc[tmp] = j; secposyc[tmp] = i;//records modificated position of 'p'
							cout << "p";
							tmp += 1;
						}
						break;
					case 4:
					case 5:
					case 6:
					case 7:
					case 8:
						if (pos[j][i])
						{
							secposxc[tmp] = j; secposyc[tmp] = i;//records modificated position of 'p'
							cout << " ";
							tmp += 1;
						}
						break;
					}
				}
			}
			for (int i(0); tmp - i > -1 ; i += 1)//writes changes stored in secposxc and secposyc to pos array.
			{
				if (pos[secposxc[i]][secposyc[i]]) pos[secposxc[i]][secposyc[i]] = 0;
				else pos[secposxc[i]][secposyc[i]] = 1;
			}
		}
	return;
}

int main();

void fnit()//finalization
{
	for (int i(0); i < 3; i += 1)
	{
		switch (i)
		{
		case 0:
			gotoxy(2 * (mapsz + 3), (mapsz / 2) + i);
			cout << "/*Game Of Life*/";
			break;
		case 1:
			gotoxy(2 * (mapsz + 3), (mapsz / 2) + i);
			cout << "Press 'r' to play again";
			break;
		case 2:
			gotoxy(2 * (mapsz + 3), (mapsz / 2) + i);
			cout << "Press 'x' to exit";
			break;
		}
	}
	switch (getch())
	{
	case 'r':
		system("cls");
		main();
	case 'x':
		system("cls");
		cout << "Thank you for playing" << endl;
		return;
	default:
		break;
	}
}

int main()//main function
{
	init();
	mapgen();
	position();
	iteration();
	fnit();
	return 0;
}