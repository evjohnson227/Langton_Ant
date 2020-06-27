/*************************************************************
* Group # 4
* Program name: Doodlebug.hpp
* Date: 5/4/2019
* Description: Header files for Doodlebug class.
*   Inherits from Critter class and displays properties of a
*   predator to eat the Ant class in the game.
*************************************************************/

#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "Critter.hpp"
#include "Helper.hpp"
#include "Board.hpp"

class Doodlebug: public Critter
{
private:
    int steps_eaten = 0;
public:
    Doodlebug(int r, int c);
    bool will_starve(); // checks if DoodleBug will starve, returns true if so
    virtual char check_move(Board);

    // Increase life by 1 and steps eaten
    virtual void age() { 
        life++;
        steps_eaten++;
    }; 

    void ate() { // reset steps_eaten
        steps_eaten = 0;
    };
    virtual void move(int row, int col, std::string type);
};

#endif