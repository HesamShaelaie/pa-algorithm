#ifndef _config_d_c
#define _config_d_c

#include <iostream>
#include <fstream>

#include"exitence.h"
#include "config_d.h"
#include <sys/stat.h>

using std::endl;
void config_d::write_general_info()
{
     
    // checking if the address exists
    if (!exists(Address))
        mkdir(Address,0777); // if not make the folder

    // printing generall information of the problem
    std::ofstream out_G;
    out_G.open(AddGnInfo, std::ios_base::app);// append to the file
    
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    out_G << " ---------------------------------------------------------- "<< endl;
    out_G << "Time:   " << std::ctime(&end_time);
    out_G << "Ninstance:    " << Nint <<endl;
    out_G << "Nnode:    " << Ntnd <<endl;
    out_G << "Farcs:    " << Farcs <<endl;
    out_G << "Narcs:    " << Narcs <<endl;

    out_G << "Cordination_min: " << Cor_min <<endl;
    out_G << "Cordination_max: " << Cor_max <<endl;

    out_G << "Tchance: " << Cchance <<endl;
    out_G << "Tless: " << Cless <<endl;
    out_G << "Tmore: " << Cmore <<endl;

    out_G << "Min_on_path: " << min_on_path <<endl;
    out_G << "Max_on_path: " << max_on_path <<endl;

    out_G << "RNeighbor: " << NNeighbor <<endl;
    out_G << "Ffpath: " << Ffpath <<endl;
    out_G << "Nfpath: " << Nfpath <<endl;

    out_G.close();
}


void config_d::getpath(char *new_add)
{
    strncpy(Address,new_add, 300);
    sprintf(AddGnInfo, "%s/CSP-info.txt", Address);
}

void config_d::update()
{
    Narcs = int(Permutation(Ntnd, 2)*Farcs);
    Nfpath = int(Ffpath * Ntnd);
    min_on_path = int(Ntnd*min_on_pathf);
    max_on_path = int(Ntnd*max_on_pathf);
    NNeighbor = int(FNeighbor*Ntnd);
}
#endif