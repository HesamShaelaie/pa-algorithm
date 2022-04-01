#ifndef _config_r_c
#define _config_r_c

#include"config_r.h"
#include"config_d.h"

void config_r::update()
{
    Itnd =0;
    for (int i = Inst_s; i < Inst_f; i++)
    {
        sprintf(Tadd[Itnd], "%s/CSP-%d-%2d-%d-f.txt", address, Ntnd, Farc, i);
        sprintf(Tname[Itnd], "CSP-%d-%2d-%d-f", Ntnd, Farc, i);
        Itnd++;
    }
};

void config_r::update(const config_d &configd)
{
    Inst_s = 0;                     //start
    Inst_f = configd.Nint;          //finish
    Farc = int(configd.Farcs*100);  
    Ntnd = configd.Ntnd;

    update();
}

#endif