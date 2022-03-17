#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <lemon/list_graph.h>


#include "variables.h"

#include "config_t.h"
#include "config_d.h"
#include "config_r.h"
#include "pa_algorithm.h"
#include "dijkstra.h"
#include "Qlearning.h"

#include "tests.h"
#include "inputesting.h"
#include "generating_data.h"
#include "reading.h"
#include "printout.h"


using namespace lemon;
using namespace std;

// Report on how to use the command line to configure this program
void usage() {
    std::cout
        << "Command-Line Options:" << std::endl
        << "  -m <int>    : mode to create instances or run the algorithm (create, run)" << std::endl
        << "Mood 1- create data version 1" << std::endl
        << "Mood 2- create data version 2" << std::endl 
        << "Mood 3- run the algorithm" << std::endl
        << "Mood 4- run the set of tests" << std::endl
        << "  -t <int>    : the number of threads in the experiment" << std::endl
        << "  -d <int>    : testing is on or off!!" << std::endl
        << "  -h          : display this message and exit" << std::endl << std::endl<<endl
        << "============================================================================" << std::endl
        << "make crt1  ->  mood 1"<<std::endl
        << "make crt2  ->  mood 2"<<std::endl
        << "make run  ->  run"<<std::endl
        << "make test  ->  test"<<std::endl;
    exit(0);
}

// Parse command line arguments using getopt()
void parseargs(int argc, char** argv, config_t& cfg) {
    // parse the command-line options
    int opt;
    while ((opt = getopt(argc, argv, "m::t:d:h")) != -1) {
        switch (opt) {
          //case 'm': cfg.mood = std::string(optarg); break;
          case 'm': cfg.mood = atoi(optarg); break;
          case 't': cfg.threads = atoi(optarg); break;
          case 'd': cfg.testing = atoi(optarg); break;
          case 'h': usage(); break;
        }
    }
}

// The main routine simply parses the arguments, dumps the arguments, populates the
int main(int argc, char** argv) 
{
    // get the configuration, print it
    config_t configt;
    config_d configd;
    config_r configr;
    parseargs(argc, argv, configt);
    configt.dump();

    try
    {   
        switch (configt.mood)
        {
            case 1: //create version one
                configd.write_general_info();
                gen_data_without_feasibility(configt, configd);
                break;

            case 2: //create version two
                configd.write_general_info();
                gen_data_with_feasibility(configt, configd);
                break;

            case 5: //create version two
                configd.Ntnd = 10;
                configd.update();
                configd.write_general_info();
                gen_data_with_feasibility(configt, configd);
                break;

            case 3: //run the algorithm
                
                configd.Ntnd = 10;
                configd.update();
                configr.update(configd);

                for (int x = 0; x < configr.Itnd; x++)
                {
                    cout << configr.Tname[x] << "::";
                    

                    InstanceInfo *Info = reading(configt, configr, x);
                    
                    if (configt.testing)
                        InputTesting(Info);
                    
                    Info->create_map();

                    if (configt.testing)
                    {
                        InputTesting(Info);
                        InputTesting_Find(Info);
                        InputTesting_FindM(Info);
                    }
                    
                    Dijkstra(Info);

                    if (configt.testing)
                        Info->dump_dijk();

                    Solve_PA(Info);
                    PrintSolution(Info);
                    Info->del_memory();
                    
                    //https://www.geeksforgeeks.org/draw-line-c-graphics/
                    //https://www.youtube.com/watch?v=Dyz9O7s7B8w  installing sdl2

                    cout << "   OK!"<<endl;
                }
                
                //Testing data
                //Running algorithm
                break;

            case 4: //run the test
                testing(First, &configt);
                testing(Second, &configt);
                break;

            case 6: //run the algorithm
                

                break;
        
        default:
            cout<<"wrong input pragma for the code!!"<<endl;
            exit(13);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}
