/*************************************************************
* Group # 4
* Program name: Game.hpp
* Date: 5/4/2019
* Description: Header class files of Game.
*   Runs the game itself and handles everything, from creating
*   of critters to the board class to user input & output.
*************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"

#include <vector>

#include "Helper.hpp"

class Game
{
private:
    // Contains the 2D array of the pointers.
    Board board;
    void run_step();
    void run_steps(int num_steps); // Uses run_step for num_steps

    // Vector of ant pointers
    std::vector<Ant *> ants;
    // Vector of the doodlebug pointers 
    std::vector<Doodlebug *> doodlebugs;

    void create_ant(int y, int x);
    void create_doodlebug(int y, int x);

    void remove_critter(std::string type, int index);
    int find_ant(int row, int col);
    void start_game();

    int * get_new_coordinates(int row, int col, char direction);

    // Running move for each step for critter, not actual move function
    void move_critter(Critter *);

    void breed_critter(Critter *);

public:
    Game();
    ~Game(); // Deletes the critter pointers & board dynamic arrays
};

#endif