#ifndef _Qlearning_h
#define _Qlearning_h

#include"variables.h"

#define nx 100

struct statesinfo
{   
    bool done = false;

    int node = -1;
    float Qvalue = 0;  //
    float Avalue[nx];
    statesinfo *next[nx];

    float Rrhs = -1;  // remainings rhs

};


void Qlearning(InstanceInfo *Info);


#endif