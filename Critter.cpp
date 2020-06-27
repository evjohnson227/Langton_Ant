/*************************************************************
* Group # 4
* Program name: Critter.cpp
* Date: 5/4/2019
* Description: Source file for Critter class.
*  Derived from the critter base class detailed in "critter.hpp".
*  This file implements the member variables and functions for used 
*  for the predator-prey game used for ants.
*************************************************************/

#include "Critter.hpp"

/*************************************************************
* Returns a direction if the bug can breed a new bug and place
*   it to that direction, which will be empty. Otherwise,
*   if it's full or if bug is not an adult yet, it will
*   return ' '
*************************************************************/
char Critter::check_breed(Board board)
{
    // Direction to breed in, no direction = ' '
    char result = ' ';

    if (life == 0)
        return result;
    else if ((life % adult_life) != 0)
        return result;

    // Checked directions U, R, D, L
    bool checked[4] = { false, false, false, false };

    //Check all directions before returning default value
    while (checked[0] != true || checked[1] != true || checked[2] != true || checked[3] != true)
    {
        //Choose random move direction
        int breedDir = Helper::randInt(0, 3);

        //Direction up chosen
        if (breedDir == 0)
        {
            checked[0] = true; //Mark the direction as checked
            //Check if spot empty
            if (!board.out_of_bounds(row, col, 'U') &&
                board.get_type(row, col, 'U').compare("empty") == 0)
            {
                //Set return direction
                result = 'U';
                return result;
            }
        }

        //Direction right chosen
        else if (breedDir == 1)
        {
            checked[1] = true;
            if (!board.out_of_bounds(row, col, 'R') &&
                board.get_type(row, col, 'R').compare("empty") == 0)
            {
                result = 'R';
                return result;
            }
        }

        //Direction down chosen
        else if (breedDir == 2)
        {
            checked[2] = true;
            if (!board.out_of_bounds(row, col, 'D') &&
                board.get_type(row, col, 'D').compare("empty") == 0)
            {
                result = 'D';
                return result;
            }
        }

        //Direction left chosen
        else if (breedDir == 3)
        {
            checked[3] = true;
            if (!board.out_of_bounds(row, col, 'L') &&
                board.get_type(row, col, 'L').compare("empty") == 0)
            {
                result = 'L';
                return result;
            }
        }
    }

    return result;
}


// Returns critter's row as int
int Critter::getRow()
{
    return row;
}

// Returns critter's column as int
int Critter::getCol()
{
    return col;
}

// Sets critter's row to int r
void Critter::setRow(int r)
{
    row = r;
}

// Sets critter's column to int c
void Critter::setCol(int c)
{
    col = c;
}


void Critter::set_loc(int r, int c)
{
    row = r;
    col = c;
}


/*************************************************************
* Critter moves to a new location. Checks that it's empty
*   and changes the row, and col.
*************************************************************/
void Critter::move(int new_row, int new_col, std::string new_cell_type)
{
    if (new_cell_type.compare("empty") == 0)
    {
        set_loc(new_row, new_col);
    }
}