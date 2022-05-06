#ifndef _index_creator_c
#define _index_creator_c

#include<math.h>
#include "index_creator.h"

long long index_creator(int Nnodes, int from, int to)
{
    int tens = ceil(log10(Nnodes))+1;

    long long tmp = (from * pow(10,tens)) + to;

    return tmp;
}



#endif