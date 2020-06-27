/*************************************************************
*  Author: David Martinez, Andy Situ
*  Date: 5/4/19
*  Description: Headerfile for Critter class
*  This file lists the member variables and function prototypes 
*  for used for the predator-prey game.
*************************************************************/
#ifndef CRITTER_HPP
#define CRITTER_HPP

#include <string>
#include "Board.hpp"
#include "Helper.hpp"

class Board;

class Critter
{
protected:
    int adult_life; // Num steps required to be an adult;
    int row;
    int col;
    std::string type_name;
    int life; // num steps it has survived
public:
    // NOTE: DIRECTIONS ARE 'R', 'L', 'U', 'D', AND ' '
    virtual char check_move(Board b) = 0;
    virtual void move(int row, int col, std::string type);
    virtual char check_breed(Board b);

    std::string get_type() { return type_name; }

    int getRow();                 // Returns critter's row as int
    int getCol();                 // Returns critter's column as int
    void setRow(int);
    void setCol(int);

    virtual void age() { life++; } // Increase life by 1

    void set_loc(int row, int col);
};

#endif