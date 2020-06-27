/*************************************************************
* Group # 4
* Program name: Ant.cpp
* Date: 5/4/2019
* Description: Source file for the ant class
*   Consists of constructor and check_move which is a virtual
*   function from the Critter class.
*************************************************************/

#include "Ant.hpp"

/*************************************************************
* Constructor for Ant. Sets up variables for game.
*************************************************************/
Ant::Ant(int r, int c)
{
    adult_life = 3;
    life = 0;
    row = r;
    col = c;
    type_name = "Ant";
}

/*************************************************************
* Ant returns a random character for the direction it will go.
"   'D', 'U', 'L', 'R' for down, up, left, right
*************************************************************/
char Ant::check_move(Board b)
{
    //Randomly pick 1 of 4 cardinal directions
    int breedDir = Helper::randInt(0, 3);

    //Up for 0
    if (breedDir == 0)
        return 'U';

    //Right for 1
    else if (breedDir == 1)
        return 'R';

    //Down for 2
    else if (breedDir == 2)
        return 'D';

    //Left for 3
    else
        return 'L';
}