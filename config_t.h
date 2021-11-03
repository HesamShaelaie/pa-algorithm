#ifndef _configuration_h
#define _configuration_h

#include <iostream>
#include <string>

// store all of our command-line configuration parameters
struct config_t {

    int mood;
    int threads;
    bool testing;

    // simple constructor
    config_t() : mood(0), threads(1), testing(0) { }

    // Print the values of the iters, and name fields
    void dump();
};
#endif