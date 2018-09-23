#include "boardSpace.h"
#include "helper_functions.h"

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

