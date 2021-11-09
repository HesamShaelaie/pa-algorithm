#ifndef _variabels_h
#define _variabels_h

#include <math.h>
#define epz 0.0000001
struct arcinfo
{
    bool key;
    int st;
    int ed;
    float cost;
    float time;
    arcinfo()
    {
        key = false;
        st = -1;
        ed = -1;
        cost = 0;
        time = 0;
    } 
    bool operator < (const arcinfo& rhs) const
    {
        if (time + epz < rhs.time)
            return true;
        else
            return false;

    }

    bool operator > (const arcinfo& rhs) const
    {
        if (time - epz > rhs.time)
            return true;
        else
            return false;

    }

    bool operator == (const arcinfo& rhs) const
    {
        if (abs(time - rhs.time)< epz)
            return true;
        else
            return false;
    }
};

struct nodeinfo
{
    float x;
    float y;
    nodeinfo()
    {
        x = -1;
        y = -1;
    }
    /* data */
};

struct InstanceInfo
{
    int Nnodes;
    int Narcs;
    arcinfo *arcs;
};




#endif