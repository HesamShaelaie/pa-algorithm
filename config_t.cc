#ifndef _configuration_c
#define _configuration_c

#include <iostream>
#include "config_t.h"

// Print the values of the iters, and name fields as comma separated
// values, with a header row

void config_t::dump() {
    std::cout << "# name, threads" << std::endl;
    std::cout << name << ", "
                << threads << std::endl;
}

#endif
