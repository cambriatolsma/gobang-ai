#include "gobang.h"

#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

int BOARD_SIZE;
int CPLAYER;
int HPLAYER;
int MINMAX_DEPTH;
std::string WINNER;
std::vector<std::vector<int>> BOARD;
std::vector<std::vector<int>> BOARD_VALUES;

int currPlayer = 0;

int bestMoveR;
int bestMoveC;

bool check_win(int player)
{
	int target = player;
	int MAX_TILES = 5;
	int horizontal = 1;
	int vertical = 1;
	int diagonalU = 1;
	int diagonalD = 1;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (BOARD[i][j] == target)
			{
				for (int s = 1; s < 5; s++)
				{
					if (j + s < BOARD_SIZE)
					{
						if (BOARD[i][j + s] == target)
						{
							horizontal++;

							if (horizontal == MAX_TILES)
							{
								return true;
							}
						}
					}

					if (i + s < BOARD_SIZE)
					{
						if (BOARD[i + s][j] == target)
						{
							vertical++;

							if (vertical == MAX_TILES)
							{
								return true;
							}
						}
					}

					if (i + s < BOARD_SIZE && j + s < BOARD_SIZE)
					{
						if (BOARD[i + s][j + s] == target)
						{
							diagonalD++;

							if (diagonalD == MAX_TILES)
							{
								return true;
							}
						}
					}

					if (i - s >= 0 && j + s < BOARD_SIZE)
					{
						if (BOARD[i - s][j + s] == target)
						{
							diagonalU++;

							if (diagonalU == MAX_TILES)
							{
								return true;
							}
						}
					}
				}

				horizontal = 1;
				vertical = 1;
				diagonalU = 1;
				diagonalD = 1;
			}
		}
	}

	return false;
}

bool check_tie()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (BOARD[i][j] == 0)
			{
				return false;
			}
		}
	}

	return true;
}

bool check_empty(int x, int y)
{
	if (BOARD[x][y] == 0)
	{
		return true;
	}

	return false;
}

void read_input()
{
	string input;
	cout << "Human, make your move: \n";
	cin >> input;

	if (HPLAYER == 1)
	{
		while (!check_empty((input[0] - 97), (input[1] - 49)))
		{
			cout << "Invalid move! Try again: \n";
			cin >> input; 
		}

		BOARD[input[0] - 97][input[1] - 49] = 1;
	}

	else
	{
		while (!check_empty((input[0] - 97), (input[1] - 49)))
		{
			cout << "Invalid move! Try again: \n";
			cin >> input;
		}

		BOARD[input[0] - 97][input[1] - 49] = 2;
	}

	int row = input[0] - 97;
	int col = input[1] - 49;
  
  /*
	if (row - 1 > 0)
	{
		BOARD_VALUES[row - 1][col] += 1;
		
		if (col - 1 > 0)
		{
			BOARD_VALUES[row - 1][col - 1] += 1;
		}

		if (col + 1 < BOARD_SIZE)
		{
			BOARD_VALUES[row - 1][col + 1] += 1;
		}
	}

	if (row + 1 < BOARD_SIZE)
	{
		BOARD_VALUES[row + 1][col] += 1;

		if (col - 1 > 0)
		{
			BOARD_VALUES[row + 1][col - 1] += 1;
		}

		if (col + 1 < BOARD_SIZE)
		{
			BOARD_VALUES[row + 1][col + 1] += 1;
		}
	}

	if (col - 1 > 0)
	{
		BOARD_VALUES[row][col - 1] += 1;
	}

	if (col + 1 < BOARD_SIZE)
	{
		BOARD_VALUES[row][col + 1] += 1;
	}
  
	BOARD_VALUES[row][col] += 1;
  */
	cout << "Move played: " << input[0] << input[1] << endl;
}

void computer_move()
{
	int bestScore = NegInf;
	int bestRow = BOARD_SIZE / 2;
	int bestCol = BOARD_SIZE / 2; 

	int score = maximizer(MINMAX_DEPTH, NegInf, PosInf);

	if (score > bestScore)
	{
		bestScore = score;
		bestRow = bestMoveR;
		bestCol = bestMoveC;
	}
  
  BOARD[bestRow][bestCol] = CPLAYER;
	cout << "Move played: " << (char)(bestRow + 'a') << bestCol + 1 << endl;
}

void print_board()
{
	for (int i = 0; i < BOARD.size(); i++)
	{
		cout << "----";
	}

	cout << endl;

	for (int i = 0; i < BOARD.size(); i++)
	{
		for (int j = 0; j < BOARD.size(); j++)
		{
			if (BOARD[i][j] == 0)
			{
				cout << "| * ";
			}

			else if (BOARD[i][j] == 1)
			{
				cout << "| B ";
			}

			else if (BOARD[i][j] == 2)
			{
				cout << "| W ";
			}
		}
		cout << "|" << endl;

		for (int k = 0; k < BOARD.size() * 4; k++)
		{
			cout << "-";
		}

		cout << endl;
	}
}

int main (int argc, char *argv[])
{
	BOARD_SIZE = 0;
	CPLAYER = 0;
	HPLAYER = 0;
	MINMAX_DEPTH = 0;

	for (int i = 1; i < argc; i++)
	{
		string label = argv[i]; 

		if (label.compare("-n") == 0)
		{
			BOARD_SIZE = stoi(argv[i + 1]);
		}
		
		if (label.compare("-l") == 0)
		{
			CPLAYER = 1;
			HPLAYER = 2;
		}

		if (label.compare("-d") == 0)
		{
			MINMAX_DEPTH = stoi(argv[i + 1]);
		}
	}

	if (BOARD_SIZE == 0)
	{
		BOARD_SIZE = 11;
	}

	if (CPLAYER == 0 && HPLAYER == 0)
	{
		HPLAYER = 1;
		CPLAYER = 2;
	}

	if (MINMAX_DEPTH == 0)
	{
		MINMAX_DEPTH = 3;
	}

	BOARD = vector<vector<int>> (BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
	BOARD_VALUES = vector<vector<int>>(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

	/*
	for (int i = 0; i < BOARD_SIZE / 2 + 1; i++)
	{
		for (int j = 0; j < BOARD_SIZE / 2 + 1; j++)
		{
			BOARD_VALUES[i][j] += 1;
			BOARD_VALUES[i][BOARD_SIZE - 1 - j] += 1;
			BOARD_VALUES[BOARD_SIZE - 1 - i][j] += 1;
			BOARD_VALUES[BOARD_SIZE - 1 - i][BOARD_SIZE - 1 - j] += 1;
		}
	}
  */

	while (true)
	{
		if (CPLAYER == 1)
		{
			//Computer Turn
			computer_move();
			print_board();

			if (check_win(CPLAYER))
			{
				WINNER = "Computer";
				cout << "Computer wins!";
				break;
			}

			if (check_tie())
			{
				WINNER = "Tie";
				cout << "No one wins :(";
				break;
			}

			//Human Turn
			read_input();
			print_board();

			if (check_win(HPLAYER))
			{
				WINNER = "Human";
				cout << "Human wins!";
				break;
			}

			if (check_tie())
			{
				WINNER = "Tie";
				cout << "No one wins :(";
				break;
			}
		}

		else
		{
			//Human Turn
			read_input();
			print_board();

			if (check_win(HPLAYER))
			{
				WINNER = "Human";
				cout << "Human wins!";
				break;
			}

			if (check_tie())
			{
				WINNER = "Tie";
				cout << "No one wins :(";
				break;
			}

			//Computer Turn
			computer_move();
			print_board();

			if (check_win(CPLAYER))
			{
				WINNER = "Computer";
				cout << "Computer wins!";
				break;
			}

			if (check_tie())
			{
				WINNER = "Tie";
				cout << "No one wins :(";
				break;
			}
		}
	}
	return 0;
}