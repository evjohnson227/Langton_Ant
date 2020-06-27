/*************************************************************
* Group # 4
* Program name: Board.cpp
* Date: 5/4/2019
* Description: Source file for Board class
*   Implementation in Board which contains the critter pointers
*   in a 2D dynamic array for the prey-predator game of critters.
*************************************************************/

#include "Board.hpp"

/*************************************************************
* Create the board - the 2D dynamic array that will contain
*   the pointers to the critters, Ant and Doodlebug.
*************************************************************/
void Board::create_board(int row, int col)
{
    num_col = col;
    num_row = row;
    board = new Critter**[row];
    for (int i = 0; i < row; i++) {
        board[i] = new Critter*[col]{nullptr};
    }
}

/*************************************************************
* Prints out the 2D array of the pointers of critters. 
*   "O" for ant and "X" for doodlebug. " " for empty space.
*   to terminal.
*************************************************************/
void Board::print_board()
{
    int border_length = num_col + 2;
    std::string border(border_length , '*');

    std::cout << border << std::endl;
    for (int i = 0; i < num_row; i++) {
        std::cout << "*";
        for (int j = 0; j < num_col; j++) {
            std::string type = get_type(i, j);
            if (type == "Ant")
                std::cout << "O";
            else if (type == "Doodlebug")
                std::cout << "X";
            else
                std::cout << " ";
        }
        std::cout << "*" << std::endl;
    }
    std::cout << border << std::endl;
}

/*************************************************************
* Returns the type of the new location by giving the original
*   row and column as integers for the index in the array
*   and the direction to travel to in character
*   'U', 'D', 'R', 'L' for down, up, left, right
* Returns the string as either "Ant", "Doodlebug" or "empty
*************************************************************/
std::string Board::get_type(int row, int col, char dir)
{
    int new_row, 
        new_col;

    int * new_coords = get_new_coordinates(row, col, dir);
    new_row = new_coords[0];
    new_col = new_coords[1];

    return get_type(new_row, new_col);
}

/*************************************************************
* Returns the type of the location by giving the 
*   row and column as integers for the index in the array
*   'U', 'D', 'R', 'L' for down, up, left, right
* Returns the string as either "Ant", "Doodlebug" or "empty
*************************************************************/
std::string Board::get_type(int row, int col)
{
    Critter * piece = board[row][col];
    
    if (!piece) { // nullptr / Empty piece
        return "empty";
    }
    else {
        return piece->get_type();
    }
}

/*************************************************************
* Adds the critter to board by pointer.
*************************************************************/
void Board::add_critter(int row, int col, Critter * c)
{
    // If it's not blank, delete the old critter
    if (board[row][col]) {
        remove_critter(row, col);
    }
    board[row][col] = c;
}

/*************************************************************
* Removes the critter from board and frees up the memory.
*************************************************************/
void Board::remove_critter(int row, int col)
{
    if (board[row][col]) {
        delete board[row][col];
        board[row][col] = nullptr;
    }
}

/*************************************************************
* Checks if the new location provided in the original row,
*   and column with the new direction will be out of bounds
*   in terms of the 2d array.
* Returns true if it will be out of bounds. False, otherwise
*************************************************************/
bool Board::out_of_bounds(int row, int col, char direction)
{
    int * coords = get_new_coordinates(row, col, direction);
    
    if (coords[0] < 0)
        return true;
    if (coords[0] > num_row - 1)
        return true;
    if (coords[1] < 0)
        return true;
    if (coords[1] > num_col - 1)
        return true;
    return false;
}

/*************************************************************
* Rol and Column given as integers. Direction for the direction
*   new location from the current one. 'U', 'D', 'R', 'L' are the
*   directions given.
* Returns an int pointer for an int array will contain [row, column]
*   for the new coordinates.
*************************************************************/
int * Board::get_new_coordinates(int row, int col, char direction)
{
    temp_coords[0] = row;
    temp_coords[1] = col;

    if (direction == 'U') { // UP
        temp_coords[0]--;
    }
    else if (direction == 'D') // DOWN
    {
        temp_coords[0]++;
    }
    else if (direction == 'L') // LEFT
    {
        temp_coords[1]--;
    }
    else if (direction == 'R') // RIGHT
    {
        temp_coords[1]++;
    } 
    // ' ' will lead to no change

    //std::cout << direction << " " << row << " " << col << " " << coords[0] << " " << coords[1] << std::endl;
     return temp_coords;

}

/*************************************************************
* Moves the critter from the original location to the new one
*   decided by the direction character: 'U', 'D', 'R', 'L'
*************************************************************/
void Board::move_critter(int old_row, int old_col, char direction)
{
    if (get_type(old_row, old_col, direction).compare("empty") == 0)
    {
        int * new_coords = get_new_coordinates(old_row, old_col, direction);
        int new_row = new_coords[0],
            new_col = new_coords[1];

        Critter * temp_crit = board[old_row][old_col];
        board[old_row][old_col] = nullptr;
        board[new_row][new_col] = temp_crit;
        temp_crit = nullptr;
    }
    else
    {
        std::cout << "ERROR: You're trying to replace a board piece that already exists" << std::endl;
    }
    
}

/*************************************************************
* Deletes board, the 2D dynamic array when the game ends.
*   Called by the game class. 
*************************************************************/
void Board::delete_board()
{
    for (int i = 0; i < num_row; i++) {
        delete [] board[i];
        board[i] = nullptr;
    }
    delete[] board;
    board = nullptr;
}