/*************************************************************
* Group # 4
* Program name: Ant.hpp
* Date: 5/4/2019
* Description: This is the header file for the ant class  
*  This file lists the member variables and function prototypes 
*  for used for the predator-prey game used for ants.
*************************************************************/

#ifndef ANT_HPP
#define ANT_HPP

#include "Critter.hpp"
#include "Helper.hpp"
#include "Board.hpp"
#include <string>
using std::string;

class Ant: public Critter
{
public:
    Ant(int, int);                // Constructor for ant coordinates are int, int   
    virtual char check_move(Board b); // Critter asks to move in char direction
};

#endif