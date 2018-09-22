#include <iostream>
#include <vector>
#include <utility>

//Class representing a space in the tic tac toe board, for improved readability
class boardSpace
{
    //symbol[0] represent X, O, or blank space
    //symbol[1] is used to check if the space is played or potential, used for checking possible game states
    private:
        char symbol[2] = {'-', 'P'};

    public:
        bool setChar(char c)
        {
            if(c == 'X' || c == 'O' || c == '-')
            {
                symbol[0] = c;
                return true;
            }
            else
            {
                std::cout << "Illegal Tic Tac Toe character";
                return false;
            }
        }

        char getChar()
        {
            return symbol[0];
        }

        bool setState(char c)
        {
            //F for final, P for potential
            //A space with state P represents a character used to check for the max possible score
            //A space with state F represents a character that has actually been played by either player or cpu
            if(c == 'F' || c == 'P')
            {
                symbol[1] = c;
                return true;
            }
            else
            {
                std::cout << "Illegal Tic Tac Toe character";
                return false;
            }
        }

        char getState()
        {
            return symbol[0];
        }

        boardState()
        {
            symbol[0] = '-';
            symbol[1] = 'P';
        }

};

//Return: - if game is not yet won, X if player X wins, O if player O wins, D if draw
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

int maximize(boardSpace(*)[3], int, int);
int minimize(boardSpace(*)[3], int, int);
void printBoard(boardSpace(*)[3]);

//Nice stack overflow error noob
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

int main()
{

    boardSpace tttBoard[3][3];
    char winState = '-';
    int playerX, playerY;
    int turnCount = 0;

    while(winState == '-')
    {
        std::cout << "Turn " << turnCount << "\n";
        printBoard(tttBoard);

        if(turnCount % 2 == 0)
        {
            std::cout << "Enter Row: ";
            std::cin >> playerX;
            std::cout << "Enter Column: ";
            std::cin >> playerY;
            tttBoard[playerX][playerY].setChar('X');
        }
        else
        {
            comp_minmax(tttBoard, turnCount, 1);
        }

        winState = check_win(tttBoard);
        ++turnCount;
        std::cout << "\n";
    }

    printBoard(tttBoard);
    std::cout << "Player " << winState << " wins";
}

