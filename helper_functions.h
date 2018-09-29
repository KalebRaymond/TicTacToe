#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "boardSpace.h"

char check_win(boardSpace board[3][3]);
int maximize(boardSpace(*)[3], int);
int minimize(boardSpace(*)[3], int);
void printBoard(boardSpace(*)[3]);
int comp_minmax(boardSpace(*)[3], int);

#endif // HELPER_FUNCTIONS_H

