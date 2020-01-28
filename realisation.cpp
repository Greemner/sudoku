#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

void SetColor(int text, int bg)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

class Puzzle
{
private:
	int sudoku[9][9], sudoku_0[9][9];
public:
	void inputSudoku();
	void printSudoku();
	int sameColumn(int x, int num);
	int sameRow(int y, int num);
	int sameSquare(int x, int y, int num);
	int solveSudoku(int x, int y);
	void choosesudoku();
};

/*Line-by-line puzzle input function. Enter 0 if the cell is empty*/
void Puzzle::inputSudoku()
{
	cout << "Enter the Sudoku you want to solve: " << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << "Enter " << i + 1 << " row: \n";
		for (int j = 0; j < 9; j++)
		{
			cin >> sudoku_0[i][j];
			sudoku[i][j] = sudoku_0[i][j];
		}
		cout << endl;
	}
}

/*Line-by-line puzzle output function*/
void Puzzle::printSudoku()
{
	cout << "----------------------" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << "|";
		for (int j = 0; j < 9; j++)
		{
			cout << sudoku[i][j] << " ";
			if (((j + 1) % 3) == 0)
			{
				cout << "|";
			}
		}
		cout << endl;
		if (((i + 1) % 3) == 0)
		{
			cout << "----------------------" << endl;
		}
	}
}

/*Function for splitting a puzzle into columns*/
int Puzzle::sameColumn(int x, int num)
{
	for (int i = 0; i < 9; i++)
		if (sudoku[x][i] == num)
			return 1;
	return 0;
}

/*Function for splitting a puzzle into lines*/
int Puzzle::sameRow(int y, int num)
{
	for (int i = 0; i < 9; i++)
		if (sudoku[i][y] == num)
			return 1;
	return 0;
}

/*Function for splitting a puzzle into squares 3*3*/
int Puzzle::sameSquare(int x, int y, int num)
{
	if (x < 3)
		x = 0;
	else if (x < 6)
		x = 3;
	else
		x = 6;


	if (y < 3)
		y = 0;
	else if (y < 6)
		y = 3;
	else
		y = 6;


	for (int i = x; i < x + 3; i++)
	{
		for (int j = y; j < y + 3; j++)
		{
			if (sudoku[i][j] == num)
				return 1;
		}
	}

	return 0;
}

/*Recursive function for solving*/
int Puzzle::solveSudoku(int x, int y)
{
	int num = 1;
	int tx = 0;
	int ty = 0;
	if (sudoku[x][y] != 0)
	{
		if ((x == 8) && (y == 8))
		{
			return 1;
		}
		if (x < 8)
		{
			x++;
		}
		else
		{
			x = 0;
			y++;
		}
		if (solveSudoku(x, y))
		{
			return 1;
		}
		else
		{
			return 0;
		}

	}
	if (sudoku[x][y] == 0)
	{
		while (num < 10)
		{
			if ((!sameSquare(x, y, num)) && (!sameRow(y, num)) && (!sameColumn(x, num)))
			{
				sudoku[x][y] = num;
				if ((x == 8) && (y == 8))
				{
					return 1;
				}
				if (x < 8)
				{
					tx = x + 1;
				}
				else
				{
					tx = 0;
					ty = y + 1;
				}
				if (solveSudoku(tx, ty))
				{
					return 1;
				}
			}
			num++;
		}
		sudoku[x][y] = 0;
		return 0;
	}
}

/*Function for output of the solution*/
void Puzzle::choosesudoku()
{
	cout << "\nEnter the color number that the open digits will be colored in: \n\n     0 - Black\n     1 - Blue\n     2 - Green\n     3 - Cyan\n     4 - Red\n     5 - Mauve\n     6 - Yellow\n     7 - White\n\n";
	int klr;
	cin >> klr;
	cout << "\nEnter the number of cells to open: ";
	int col, xr, yr, p = 0;
	cin >> col;
	cout << "\n\nOutput a step-by-step solution?\n\n     YES - 1\n     NO - 0\n\n";
	int po;
	cin >> po;
	int col_mas[2][81];
		while (p < col)
		{
			xr = rand() % 10;
			yr = rand() % 10;
			if (po == 1)
			{
				cout << "\n   " << p + 1 << " table cell selected at random: [" << xr << "][" << yr << "]\n";
			}
			if (sudoku_0[xr - 1][yr - 1] == 0)
			{
				col_mas[0][p] = xr - 1;
				col_mas[1][p] = yr - 1;
				sudoku_0[xr - 1][yr - 1] = sudoku[xr - 1][yr - 1];
				
				if (po == 1)
				{
					cout << "----------------------" << endl;
					for (int i = 0; i < 9; i++)
					{
						cout << "|";
						for (int j = 0; j < 9; j++)
						{
							if ((i == (xr - 1)) && (j == (yr - 1)))
							{
								SetColor(klr, 0);
								cout << sudoku_0[i][j] << " ";
								SetColor(7, 0);
							}
							else
								cout << sudoku_0[i][j] << " ";
							if (((j + 1) % 3) == 0)
							{
								cout << "|";
							}
						}
						cout << endl;
						if (((i + 1) % 3) == 0)
						{
							cout << "----------------------" << endl;
						}
					}
				}
			}
			else
			{
				if (po == 1)
					cout << "\n   Since this cell already contains a number, let's choose another cell. \n";
				p--;
			}
			p++;
		}
		if (po != 1)
		{
			cout << "----------------------" << endl;
				for (int i = 0; i < 9; i++)
				{
					cout << "|";
					for (int j = 0; j < 9; j++)
					{
						bool tr = false;
						for (int g = 0;g < col;g++)
							if ((i == col_mas[0][g]) && (j == col_mas[1][g]))
							{
								tr = true;
								goto label;
							}
						label:
						if (tr == true)
						{
							SetColor(klr, 0);
							cout << sudoku_0[i][j] << " ";
							SetColor(7, 0);
						}
						else
							cout << sudoku_0[i][j] << " ";
						if (((j + 1) % 3) == 0)
						{
							cout << "|";
						}
					}
					cout << endl;
					if (((i + 1) % 3) == 0)
					{
						cout << "----------------------" << endl;
					}
				}
		}
}

int main()
{
	srand(time(0));
	int x = 0, y = 0, number = 1;
	Puzzle S;
	S.inputSudoku();
	S.printSudoku();
	S.solveSudoku(x, y);
	while (number = 1)
	{
		cout << "\nDo you want to open part of the Sudoku cells?\n\n     If YES, press 1\n     If NO, press 0 \n\n";
		cin >> number;
		if (number == 1)
		{
			S.choosesudoku();
		}
		else
			break;
	}
	cout << "\nFully solved Sudoku: \n";
	S.printSudoku();
	system("pause");
	return 0;
}
