/*************************************************************
* Group # 4
* Program name: Game.cpp
* Date: 5/4/2019
* Description: Source for Game class.
*   Functions to game the prey-predator game with critters,
*   creation of these classes as pointers, and i/o with user
*************************************************************/

#include "Game.hpp"

/*************************************************************
* Constructor for Game class. Starts the game with this.
*************************************************************/
Game::Game()
{
    Helper::set_srand();
    start_game();
}


/*************************************************************
* Starts the game itself, asks user for board size
*   and # critters and then complete the game until the user
*   chooses to exit.
*************************************************************/
void Game::start_game()
{
    std::cout << "CS 162 Group Project" << std::endl;
    std::cout << std::endl;
    std::cout << "**with Extra Credit**" << std::endl;
    std::cout << std::endl;
    std::cout << "What size board would you like?" << std::endl;
    std::cout << "Please enter an integer for row size." << std::endl;

    int row = Helper::getIntInput(10, 75);

    std::cout << "Please enter an integer for col size." << std::endl;
    int col = Helper::getIntInput(10, 75);

    board.create_board(row, col);

    bool correct_num_bugs = false;
    int ants_input;
    int doodlebugs_input;

    while (!correct_num_bugs) { // Make sure that # bugs does not exceed board
        std::cout << "How many ants would you like?" << std::endl;
        ants_input = Helper::getIntInput(0, 200);

        std::cout << "How many doodlebugs would you like?" << std::endl;
        doodlebugs_input = Helper::getIntInput(0, 200);

        if ((doodlebugs_input + ants_input) <= (row * col)) {
            correct_num_bugs = true;
        }
        else {
            std::cout << "You wanted more bugs than there are board spaces available." << std::endl;
            std::cout << "Please enter the values again for a total of " << row * col << " or fewer";
            std::cout << std::endl << std::endl;
        }
    }

    // Create Ants until all are placed by selecting randomly and placing on empty spots
    for (int i = 0; i < ants_input; i++) {
        bool found_empty_spot = false;
        while (!found_empty_spot) {
            int random_row = Helper::randInt(0, row - 1),
                random_col = Helper::randInt(0, col - 1);
            if (board.get_type(random_row, random_col) == "empty") {
                create_ant(random_row, random_col);
                found_empty_spot = true;
            }
        }
    }
    
    // Create Doodlebugs until all are placed
    for (int i = 0; i < doodlebugs_input; i++) {
        bool found_empty_spot = false;
        while (!found_empty_spot) {
            int random_row = Helper::randInt(0, row - 1),
                random_col = Helper::randInt(0, col - 1);
            if (board.get_type(random_row, random_col) == "empty") {
                create_doodlebug(random_row, random_col);
                found_empty_spot = true;
            }
        }
    }

    int num_steps = 10;

    // Ask user how many steps they want and run game until user quits
    board.print_board();
    std::cout << "How many steps would you like to run of the simulation?" << std::endl;
    num_steps = Helper::getIntInput(1, 50);
    run_steps(num_steps);

    while (num_steps > 0) {
        std::cout << "How many steps would you like to run of the simulation?" << std::endl;
        std::cout << "Enter 0 to quit the game." << std::endl;
        num_steps = Helper::getIntInput(0, 50);

        if (num_steps)
            run_steps(num_steps);
    }
}

/*************************************************************
* Create ant object, sets it to pointer, and add to board
*************************************************************/
void Game::create_ant(int row, int col)
{
    Ant * a = new Ant(row, col);
    board.add_critter(row, col, a);

    ants.push_back(a);
    
}

/*************************************************************
* Create doodlebug, sets it to a pointer, and add to board.
*************************************************************/
void Game::create_doodlebug(int row, int col)
{
    Doodlebug * d = new Doodlebug(row, col);
    board.add_critter(row, col, d);


    doodlebugs.push_back(d);
}

/*************************************************************
* Run number of steps specificed by variable num_steps for game.
*************************************************************/
void Game::run_steps(int num_steps)
{
    for (int i = 0; i < num_steps; i++)
        run_step();
}

/*************************************************************
* Run a single step of the game, which consits of moving the
*   critters, having doodle bug eat the ants, breeding the 
*   critters and then checking if doodlebug will starve.
*   Finally the board is printed to terminal.
*************************************************************/
void Game::run_step()
{
    // Run index backwards to solve problem of deleting objects in vector
    // and breeding animals without running them until next turn. 

    // Run Doodlebugs thru the vector
    Doodlebug * db;
    for (int i = doodlebugs.size() -1; i >= 0; i--)
    {
        db = doodlebugs.at(i);
        move_critter(db);

       breed_critter(db);

        if (db->will_starve()) {
            remove_critter("Doodlebug", i);
        }
    }

    Ant * a;
    // Run Ants thru the array
    for (int i = ants.size() - 1; i >= 0; i--) {
        a = ants.at(i);
        move_critter(a);

        breed_critter(a);
    }

    board.print_board();
}

/*************************************************************
* Gets the new coordinates in traveling to that direction,
*   0 for up direction and work clockwise.
* Returns an int[2] array with [row, column] being the values.
*************************************************************/
int * Game::get_new_coordinates(int row, int col, char direction)
{
    return board.get_new_coordinates(row, col, direction);
}

/*************************************************************
* First gets a coordinate that the critter would like to move to,
*   Checks if the critter can move there (doodlebug can "move"
*   to the ant spot by eating it, and then moves the critter there.
* Changes the board array and deletes the ant if it is eaten.
*************************************************************/
void Game::move_critter(Critter * critter)
{
    critter->age();
    char dir = critter->check_move(board);
    int c_row = critter->getRow(),  
        c_col = critter->getCol();

    // Check of the coordinate is out of bounds
    if (!board.out_of_bounds(c_row, c_col, dir))
    {
        int * coords = get_new_coordinates(c_row, c_col, dir);
        int new_row = coords[0],
            new_col = coords[1];

        std::string type = critter->get_type();
        std::string next_cell_type = board.get_type(c_row, c_col, dir);

        // Move only if new coordinates are different
        if (new_row != c_row || new_col != c_col)
        {
            // Move only if bd eats an ant or empty space
            bool move_status = false;

            if (type.compare("Doodlebug") == 0) // Doodlebug "eats" Ants
            { // Will delete the ate and reset doodlebug's steps w/o eating
                if (next_cell_type.compare("Ant") == 0)
                {
                    int index = find_ant(new_row, new_col);
                    remove_critter("Ant", index);
                    move_status = true;
                }
            }
            // Confirms that it's an empty space
            if (next_cell_type.compare("empty") == 0)
                move_status = true;

            if (move_status) {
                critter->move(new_row, new_col, next_cell_type);
                board.move_critter(c_row, c_col, dir);
            }
            
        }
    }
}


/*************************************************************
* Searches for ant when index is not known.
* Returns the index when found
*************************************************************/
int Game::find_ant(int row, int col)
{
    int a_row, a_col;
    Ant * a;
    for (int i = 0; i < ants.size(); i++)
    {
        a = ants.at(i);
        a_row = a->getRow();
        a_col = a->getCol();
        if (a_row == row && a_col == col)
            return i;
    }
    return -1;
}

/*************************************************************
* Checks if the critter can bread and then creates another
*   critter in the empty space, if possible.
*************************************************************/
void Game::breed_critter(Critter * critter)
{
    int c_row = critter->getRow(),
        c_col = critter->getCol();

    char breed_dir = critter->check_breed(board);
    // ' ' means that critter doesn't have a spot to breed.
    if (breed_dir != ' ')
    {
        int * coords = board.get_new_coordinates(c_row, c_col, breed_dir);
        int new_row = coords[0];
        int new_col = coords[1];


        std::string critter_type = critter->get_type();
        // If the spot is empty then create a critter there.
        if (board.get_type(c_row, c_col, breed_dir).compare("empty") == 0) {
            if (critter_type.compare("Ant") == 0)
            {
                create_ant(new_row, new_col);
            }
            else if (critter_type.compare("Doodlebug") == 0)
            {
                create_doodlebug(new_row, new_col);
            }
        }
        
    }
}

/*************************************************************
* Remvoes the critter from the vector that contains it.
*************************************************************/
void Game::remove_critter(std::string type, int index)
{
    int row, col;
    if (type == "Ant")
    {
        Ant * a = ants.at(index);
        row = a->getRow();
        col = a->getCol();
        ants.erase(ants.begin() + index);
    }
    else if (type == "Doodlebug")
    {
        Doodlebug * db = doodlebugs.at(index);
        doodlebugs.erase(doodlebugs.begin() + index);
        row = db->getRow();
        col = db->getCol();
    }
    board.remove_critter(row, col); // Board deletes the dynamic memory of the object
}


/*************************************************************
* Destructor for Game. Deletes the critter pointers and tells
*   Board to delete its 2D dynamic arrays.
*************************************************************/
Game::~Game()
{
    while (!ants.empty()) {
        delete ants.back();
        ants.pop_back();
    }

    while (!doodlebugs.empty()) {
        delete doodlebugs.back();
        doodlebugs.pop_back();
    }

    board.delete_board();
}