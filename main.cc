#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <lemon/list_graph.h>

#include "config_t.h"
#include "tests.h"
#include "generating_data.h"

using namespace lemon;
using namespace std;

// Report on how to use the command line to configure this program
void usage() {
    std::cout
        << "Command-Line Options:" << std::endl
        << "  -m <string> : mode to create instances or run the algorithm (create, run)" << std::endl
        << "  -t <int>    : the number of threads in the experiment" << std::endl
        << "  -h          : display this message and exit" << std::endl << std::endl;
    exit(0);
}

// Parse command line arguments using getopt()
void parseargs(int argc, char** argv, config_t& cfg) {
    // parse the command-line options
    int opt;
    while ((opt = getopt(argc, argv, "m::t:h")) != -1) {
        switch (opt) {
          case 'm': cfg.name = std::string(optarg); break;
          case 't': cfg.threads = atoi(optarg); break;
          case 'h': usage(); break;
        }
    }
}

// The main routine simply parses the arguments, dumps the arguments, populates the
int main(int argc, char** argv) {
    // get the configuration, print it
    config_t config;
    parseargs(argc, argv, config);
    
    testing(First, &config);
    config.dump();


    
    

    if (config.name == "create")
       gen_data(config);

    
}
