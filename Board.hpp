/*************************************************************
* Group # 4
* Program name: Board.hpp
* Date: 5/4/2019
* Description: Header files for Board class.
*   Handles board which is a 2D array containing the critter
*   pointers and the propagation and  deletion of the ptrs.
*************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Critter.hpp"
#include <string>
#include <iostream>

class Critter;

class Board
{
private:
    Critter *** board = nullptr;
    int num_row;
    int num_col;
    int temp_coords[2] = { 0 };
public:
    void delete_board();
    void print_board();
    void add_critter(int y, int x, Critter *);
    void move_critter(int old_row, int old_col, char direction);
    void remove_critter(int y, int x);

    bool out_of_bounds(int row, int col, char direction);
    int get_num_row() { return num_row; };
    int get_num_col() { return num_col; };
    std::string get_type(int row, int col, char dir);
    std::string get_type(int row, int col);

    void create_board(int row, int col);

    int * get_new_coordinates(int row, int col, char direction);
};

#endif