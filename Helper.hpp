/*********************************************************************
* Program name: helper.hpp
* Author: Andy Situ
* Date: 4/19/2019
* Description: Helper class declaration with static functions
*   Used to get int input and a random integer.
**********************************************************************/

#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>


class Helper
{
public:
    static int getIntInput(int minValue, int maxValue);
    static void set_srand();
    static int randInt(int min, int max);
};

#endif