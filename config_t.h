#include <iostream>
#include <string>

// store all of our command-line configuration parameters
struct config_t {

  
    std::string  name;
    int threads;

    // simple constructor
    config_t() : name("no_name"), threads(1) { }

    // Print the values of the iters, and name fields
    void dump();
};
