#include "helper_functions.h"
#include "boardSpace.h"
#include <iostream>

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
            bool valid_move_flag = false;
            while(true)
            {
                std::cout << "Enter Row: ";
                std::cin >> playerX;
                std::cout << "Enter Column: ";
                std::cin >> playerY;

                valid_move_flag = (playerX >= 0) && (playerX <= 2) && (playerY >=0) && (playerY <=2) && (tttBoard[playerX][playerY].getChar() == '-');

                if(valid_move_flag)
                {
                    break;
                }
                else
                {
                    std::cout << "Illegal move.\n";
                }
            }

            tttBoard[playerX][playerY].setChar('X');
        }
        else
        {
            comp_minmax(tttBoard, turnCount);
        }

        winState = check_win(tttBoard);
        ++turnCount;
        std::cout << "\n";
    }

    printBoard(tttBoard);
    std::cout << "Player " << winState << " wins";
}

