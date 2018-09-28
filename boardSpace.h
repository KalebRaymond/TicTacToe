#ifndef BOARDSPACE_H
#define BOARDSPACE_H

#include <iostream>
#include <vector>
#include <utility>

//Class representing a space in the tic tac toe board, for improved readability
class boardSpace
{
    private:
        char symbol;
        char state;
    public:
        bool setChar(char c);
        char getChar();
        bool setState(char c);
        char getState();
        boardSpace();
};

#endif
