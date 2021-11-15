#ifndef _config_r_c
#define _config_r_c
#include"config_r.h"


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
#endif