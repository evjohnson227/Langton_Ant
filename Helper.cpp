/*********************************************************************
* Program name: helper.hpp
* Author: Andy Situ
* Date: 4/19/2019
* Description: Helper class declaration with static functions
*   Used to get int input and random integer as a helper class.
*   Contains static functions only.
**********************************************************************/

#include "Helper.hpp"
#include <iostream>
#include <string>
#include <ctype.h> // for isdigit

#include <ctime> // For rand
#include <stdio.h>

using std::cout;
using std::endl;

/*********************************************************************
 *  Gets User input for positive integers only from minValue to maxValue.
 *  Only accepts integers. No spacing, letters, etc allowed. Continues
 *  asking user for this until a valid int is given.
*********************************************************************/
int Helper::getIntInput(int minValue, int maxValue)
{
    std::string input;
    bool correctInput = false;
    int intValue;

    // Continue asking for input until input is correct
    while (!correctInput) {
        bool correctFormat = true;
        cout << "Please enter ONLY an integer between " << minValue <<
            " and " << maxValue << " (No spacing, letters, etc.)" << endl;
        std::getline(std::cin, input);

        // Check that each char is an int
        int inputLen = input.length();
        if (inputLen >= 1) {
            for (int i = 0; i < inputLen; i++) {
                if (!isdigit(input.at(i)))
                    correctFormat = false;
            }

            // Test that entire input is an integer
            if (correctFormat) {
                intValue = std::stoi(input);
                if (intValue >= minValue && intValue <= maxValue) {
                    correctInput = true;
                }

            }
        }
        std::cout << std::endl;
    }
    return intValue;
}

/*********************************************************************
 * Set srand before using randInt.
*********************************************************************/
void Helper::set_srand()
{
    srand(time(nullptr));
}

/*********************************************************************
 * Give a random number between min and max.
 * Requirement: Need to set srand (set_srand) once before using.
*********************************************************************/
int Helper::randInt(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}