#ifndef _printout_c
#define _printout_c

#include "variables.h"
#include "exitence.h"
#include "printout.h"
#include <sysdir.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <iomanip>


using std::endl;
using std::cout;
using std::setw;

void PrintSolution(InstanceInfo *Info)
{
    char name[300];

    if (!exists(Info->add_out))
        mkdir(Info->add_out,0777);


    sprintf(name, "%s/%s-S.txt", Info->add_out, Info->name);
    
    
    std::ofstream out;
    out.open(name);

    if(!out)
    {
        cout<<"cannot write solution!!"<<endl;
        exit(11);
    }    

    out<<"Obj:"<<setw(10)<<Info->sol_obj<<endl;
    out<<"Path:";
    for (int x = 0; x < Info->sol_n; x++)
        out<<setw(8)<<Info->sol_path[x];
    
    out<<endl;

}


#endif