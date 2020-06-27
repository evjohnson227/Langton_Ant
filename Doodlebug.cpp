/*************************************************************
* Group # 4
* Program name: Doodlebug.cpp
* Date: 5/4/2019
* Description: Source file for Doodlebug class
*   Consists of functions that are overriding virtual ones 
*   from the Critter class and the constructor.
*************************************************************/

#include "Doodlebug.hpp"

/*************************************************************
* Constructor of Doodlebug. Sets the member variables up.
*************************************************************/
Doodlebug::Doodlebug(int r, int c)
{
    adult_life = 8;
    life = 0;
    row = r;
    col = c;
    type_name = "Doodlebug";
}

/*************************************************************
* Doodlebug checks if there is an ant and moves there if so,
*   if not, then it checks for an empty spot.
* Returns the spot that it was to by by char
*   'U', 'D', 'R', 'L' for down, up, left, right
*************************************************************/
char Doodlebug::check_move(Board board)
{
    //Checks for ants
    if (!board.out_of_bounds(row, col, 'D'))
        if (board.get_type(row, col, 'D').compare("Ant") == 0)
        {
            return 'D';
        }
    if (!board.out_of_bounds(row, col, 'U'))
        if (board.get_type(row, col, 'U').compare("Ant") == 0)
        {
            return 'U';
        }
    if (!board.out_of_bounds(row, col, 'R'))
        if (board.get_type(row, col, 'R').compare("Ant") == 0)
        {
            return 'R';
        }
    if (!board.out_of_bounds(row, col, 'L'))
        if (board.get_type(row, col, 'L').compare("Ant") == 0)
        {
            return 'L';
        }


    //Randomly pick 1 of 4 cardinal directions
    int direction = Helper::randInt(0, 3);

    //Up for 0
    if (direction == 0)
        return 'U';

    //Right for 1
    else if (direction == 1)
        return 'R';

    //Down for 2
    else if (direction == 2)
        return 'D';

    //Left for 3
    else
        return 'L';
}


/*************************************************************
* Moves Doodlebug and checks if the location had an ant.
* If so, it has eaten
*************************************************************/
void Doodlebug::move(int new_row, int new_col, std::string prev_cell_type)
{
    if (prev_cell_type.compare("empty") == 0)
    {
        set_loc(new_row, new_col);
    }
    else if (prev_cell_type.compare("Ant") == 0)
    {
        set_loc(new_row, new_col);
        ate();
    }
}

/*************************************************************
* Returns bool of whether it will starve that turn
*************************************************************/
bool Doodlebug::will_starve()
{
    if (steps_eaten >= 3)
        return true;
    return false;
}