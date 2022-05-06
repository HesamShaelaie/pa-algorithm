#ifndef _config_r_h
#define _config_r_h

#include<fstream>
#include<unistd.h>
#include"config_d.h"

#define MAXINSTANCE 10000
// store all data which is necessary for generating inputs (feasible)

struct config_r 
{
    char address[300];
    char address_out[300];
    char address_raw[300];
    int Inst_s;
    int Inst_f;
    int Ntnd;
    int Farc;

    int Itnd;
    char Tadd[MAXINSTANCE][300];
    char Tname[MAXINSTANCE][300];
    
    config_r()
    {
        Inst_s = 0;
        Inst_f = 10; //not inclusive
        Ntnd = 10;
        Farc = 30;

        getcwd(address,256); // getting the folder of the codes
        strcat(address, "/instances"); // add the instance to the address
        getcwd(address_out,256);
        strcat(address_out, "/output"); // add the instance to the address
        getcwd(address_raw,256);
        update();
    }

    void update();
    void update(const config_d &configd);
};


#endif