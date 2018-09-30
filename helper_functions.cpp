#include "helper_functions.h"

//Return '-' if game is not yet won, 'X' if player X wins, 'O' if player O wins, 'D' if draw
char check_win(boardSpace board[3][3])
{

    for(int i = 0; i < 3; ++i)
    {
        if(board[i][0].getChar() != '-' && board[i][1].getChar() == board[i][0].getChar() && board[i][2].getChar() == board[i][0].getChar())
        {
            if(board[i][0].getChar() == 'X')
            {
                return 'X';
            }
            else
            {
                return 'O';
            }
        }
    }

    for(int j = 0; j < 3; ++j)
    {
        if(board[0][j].getChar() != '-' && board[1][j].getChar() == board[0][j].getChar() && board[2][j].getChar() == board[0][j].getChar())
        {
            if(board[0][j].getChar() == 'X')
            {
                return 'X';
            }
            else
            {
                return 'O';
            }
        }
    }

    if(board[0][0].getChar() != '-' && board[0][0].getChar() == board[1][1].getChar() && board[0][0].getChar() == board[2][2].getChar())
    {
        if(board[0][0].getChar() == 'X')
        {
            return 'X';
        }
        else
        {
            return 'O';
        }
    }

    if(board[0][2].getChar() != '-' && board[0][2].getChar() == board[1][1].getChar() && board[0][2].getChar() == board[2][0].getChar())
    {
        if(board[0][2].getChar() == 'X')
        {
            return 'X';
        }
        else
        {
            return 'O';
        }
    }

    //Check if game isn't over yet
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(board[i][j].getChar() == '-')
            {
                return '-';
            }
        }
    }

    return 'D';
}

//Recursive function intended to return the expected score of putting an X in a given boardSpace
int maximize(boardSpace board[3][3], int depth)
{
    char win_state = check_win(board);
    switch(win_state)
    {
        case 'X':
            return 10 - depth;
        case 'O':
            return depth - 10;
        case 'D':
            return depth;
    }

    int score = INT_MIN;

    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(board[i][j].getChar() == '-')
            {
                board[i][j].setChar('X');
                board[i][j].setState('P');

                score = std::max(score, minimize(board, depth + 1));

                board[i][j].setChar('-');
            }
        }
    }

    return score;
}

//Recursive function intended to return the expected score of putting an O in a given boardSpace
int minimize(boardSpace board[3][3], int depth)
{
    char win_state = check_win(board);
    switch(win_state)
    {
        case 'X':
            return 10 - depth;
        case 'O':
            return depth - 10;
        case 'D':
            return depth;
    }

    int score = INT_MAX;

    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(board[i][j].getChar() == '-')
            {
                board[i][j].setChar('O');
                board[i][j].setState('P');

                score = std::min(score, maximize(board, depth + 1));

                board[i][j].setChar('-');
            }
        }
    }

    return score;
}

//Function intended to determine the best possible move for player O
int comp_minmax(boardSpace board[3][3], int turn_count)
{

    //To save computation time, the best first move is known to either be the corner or the middle if the corner is taken
    if(turn_count == 1)
    {
        if(board[1][1].getChar() == '-')
        {
            board[1][1].setChar('O');
            board[1][1].setState('F');
        }
        else
        {
            board[0][0].setChar('O');
            board[0][0].setState('F');
        }
        return 0;
    }

    int best_move[2] = {0, 0};
    int min_score = INT_MAX;

    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(board[i][j].getChar() == '-')
            {
                board[i][j].setChar('O');
                board[i][j].setState('P');

                int move_score = maximize(board, 1);

                std::cout << move_score << " " << min_score << " | ";
                if(move_score < min_score)
                {
                    min_score = move_score;
                    best_move[0] = i;
                    best_move[1] = j;
                }

                board[i][j].setChar('-');
            }
        }
    }

    std::cout << best_move[0] << ", " << best_move[1] << " ";

    if(board[best_move[0]][best_move[1]].getChar() != '-')
    {
        std::cout << "Something went wrong";
        return -1;
    }
    else
    {
        board[best_move[0]][best_move[1]].setChar('O');
        board[best_move[0]][best_move[1]].setState('F');
    }
    return 0;

}

void printBoard(boardSpace board[3][3])
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            std::cout << board[i][j].getChar() << " ";
        }
        std::cout << "\n";
    }
}
