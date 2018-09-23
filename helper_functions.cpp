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
int maximize(boardSpace board[3][3], int depth, int score)
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(board[i][j].getChar() == '-')
            {
                board[i][j].setChar('X');
                board[i][j].setState('P');

                char win_state = check_win(board);

                switch(win_state)
                {
                    case 'X':
                                score += (10 - depth);
                                return score;
                    case 'D':
                                return -1;
                    default:
                                //printBoard(board);
                                minimize(board, depth + 1, score);

                }

                board[i][j].setChar('-');
            }
        }
    }
}

//Recursive function intended to return the expected score of putting an O in a given boardSpace
int minimize(boardSpace board[3][3], int depth, int score)
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(board[i][j].getChar() == '-')
            {
                board[i][j].setChar('O');
                board[i][j].setState('P');

                char win_state = check_win(board);

                switch(win_state)
                {
                    case 'O':
                                score -= (10 - depth);
                                return score;
                    case 'D':
                                return -1;
                    default:
                                //printBoard(board);
                                maximize(board, depth + 1, score);
                }

                board[i][j].setChar('-');
            }
        }
    }
}

//Function intended to determine the best possible move for player O
int comp_minmax(boardSpace board[3][3], int turn_count, int depth)
{

    //To save computation time, the best first move is known to either be the corner or the middle if the corner is taken
    if(turn_count == 1)
    {
        if(board[0][0].getChar() == 'X' || board[0][2].getChar() == 'X' || board[2][0].getChar() == 'X' || board[2][2].getChar() == 'X')
        {
            board[1][1].setChar('O');
        }
        else
        {
            board[0][0].setChar('O');
        }

        return 0;
    }

    static std::vector< std::pair <char[3][3], int>> game_states;
    int best_move[2];
    int min_score = 0;


    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(board[i][j].getChar() == '-')
            {
                if((turn_count + depth) % 2 == 0)
                {
                    //find move that gives x most points
                    maximize(board, 0, 0);
                }
                else
                {
                    //find move that gives x least points, lose < tie
                    if(minimize(board, 0, 0) < min_score)
                    {
                        best_move[0] = i;
                        best_move[1] = j;
                    }
                }

            }
        }
    }

    board[best_move[0]][best_move[1]].setChar('O');
    board[best_move[0]][best_move[1]].setState('F');


    return 0;

}

void printBoard(boardSpace board[3][3])
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            //tttBoard[i][j] = boardSpace();
            std::cout << board[i][j].getChar() << " ";
        }
        std::cout << "\n";
    }
}
