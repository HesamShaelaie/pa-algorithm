#ifndef _config_d_h
#define _config_d_h

#include<fstream>
#include<unistd.h>
#include "mathmatics.h"
// store all data which is necessary for generating inputs (feasible)
struct config_d {

    
    int Nint;     //#number of instance
    int Ntnd;     //#number of total nodes in the game

    //with respect to complete graphs
    float Farcs; 
    int Narcs;

    // cost max and min
    float Tmin;
    float Tmax;

    // number of nodes on the path
    float Ffpath;
    int Nfpath;


    // max and min of coordination
    float Cor_min;
    float Cor_max;


    // if the chance is over the 0.5 then increase by tmore
    float Cchance;
    float Cless;
    float Cmore;

    // max and min number of nodes on the path with respect to the total number of nodes
    int min_on_path;
    int max_on_path;

    float min_on_pathf;
    float max_on_pathf;

    // neighbor search for the nodes
    float FNeighbor;
    int   NNeighbor;
    
    char AddGnInfo[300];
    char Address[300];

    config_d()
    { 
        Nint =10;
        Ntnd = 100;
        Farcs  = 0.3;
        Narcs = int(Permutation(Ntnd, 2)*Farcs);
        Ffpath = 0.5;
        Nfpath = int(Ffpath * Ntnd);
        Cor_min = 0;
        Cor_max = 1000;
        Cchance = 0.5;    // I should fix this    
        Cless = 0.8;
        Cmore = 1.2;

        min_on_pathf = 0.2;
        max_on_pathf = 0.6;

        min_on_path = int(Ntnd*min_on_pathf);
        max_on_path = int(Ntnd*max_on_pathf);
        
        FNeighbor = 0.3;
        NNeighbor = int(FNeighbor*Ntnd);

        getcwd(Address,256); // getting the folder of the codes
        strcat(Address, "/instances"); // add the instance to the address
        sprintf(AddGnInfo, "%s/CSP-info.txt", Address);// add general info
        // without feasibility
        Tmin = 10;
        Tmax = 1000;
    }

    void write_general_info();

    // Print the values of the iters, and name fields
    void getpath(char *);
    void update();
};


#endif