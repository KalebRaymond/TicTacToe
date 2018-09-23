#include "boardSpace.h"
#include <iostream>
#include <vector>
#include <utility>

bool boardSpace::setChar(char c)
{
    if(c == 'X' || c == 'O' || c == '-')
    {
        symbol = c;
        return true;
    }
    else
    {
        std::cout << "Illegal Tic Tac Toe character";
        return false;
    }
}

char boardSpace::getChar()
{
    return symbol;
}

bool boardSpace::setState(char c)
{
    //F for final, P for potential
    //A space with state P represents a character used to check for the max possible score
    //A space with state F represents a character that has actually been played by either player or cpu
    if(c == 'F' || c == 'P')
    {
        state = c;
        return true;
    }
    else
    {
        std::cout << "Illegal Tic Tac Toe character";
        return false;
    }
}

char boardSpace::getState()
{
    return state;
}

boardSpace::boardSpace()
{
    //symbol = new char[2];
    symbol = '-';
    state = 'P';
}
