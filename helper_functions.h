#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "boardSpace.h"

char check_win(boardSpace board[3][3]);
int maximize(boardSpace(*)[3], int, int);
int minimize(boardSpace(*)[3], int, int);
void printBoard(boardSpace(*)[3]);
int comp_minmax(boardSpace board[3][3], int turn_count, int depth);

#endif // HELPER_FUNCTIONS_H

