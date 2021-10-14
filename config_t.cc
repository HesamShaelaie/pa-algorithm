// CSE 375/475 Assignment #1
// Fall 2021

// Description:  This file implements the config_t::dump() function

#include <iostream>
#include "config_t.h"

// Print the values of the iters, and name fields as comma separated
// values, with a header row

void config_t::dump() {
    std::cout << "# name, threads" << std::endl;
    std::cout << name << ", "
                << threads << std::endl;
}