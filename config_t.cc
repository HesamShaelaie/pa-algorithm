#ifndef _config_t_c
#define _config_t_c

#include <iostream>
#include "config_t.h"

// Print the values of the iters, and name fields as comma separated
// values, with a header row

void config_t::dump() 
{
    std::cout << "# mood, threads, testing" << std::endl;
    std::cout << mood << ", " << threads << ", ";
                if (testing == false)
                    std::cout<< "FALSE" << std::endl;
                else
                    std::cout<<"TRUE"<<std::endl;
                
}

#endif
