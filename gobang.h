#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>

extern int BOARD_SIZE;
extern int CPLAYER;
extern int HPLAYER;
extern int MINMAX_DEPTH;
extern std::string WINNER;
extern std::vector<std::vector<int>> BOARD;
extern std::vector<std::vector<int>> BOARD_VALUES;

extern int currPlayer;

const int NegInf = std::numeric_limits<int>::min();
const int PosInf = std::numeric_limits<int>::max();

extern int bestMoveR;
extern int bestMoveC;


int maximizer(int depth, int alpha, int beta);
int minimizer(int depth, int alpha, int beta);
int compute_move_value(int player);

bool check_win(int player);
bool check_tie();
bool check_empty(int x, int y);

void read_input();
void computer_move();
void print_board();