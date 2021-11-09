#ifndef _config_r_h
#define _config_r_h

#include<fstream>
#include<unistd.h>

#define MAXINSTANCE 10000
// store all data which is necessary for generating inputs (feasible)

struct config_r 
{
    char address[300];
    int Inst_s;
    int Inst_f;
    int Ntnd;
    int Farc;

    int Itnd;
    char Tadd[MAXINSTANCE][300];
    config_r()
    {
        Inst_s = 0;
        Inst_f = 10; //not included
        Ntnd = 100;
        Farc = 30;
        getcwd(address,256); // getting the folder of the codes
        strcat(address, "/instances"); // add the instance to the address
        update();
    }

    void update();
};


#endif