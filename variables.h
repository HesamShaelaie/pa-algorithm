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
    int Nnbr;
    int *next;
    nodeinfo()
    {
        x = -1;
        y = -1;
        Nnbr = 0;
        next = nullptr;
    }
    void all_memory()
    {
        next = new int [Nnbr];
    };
    void del_memory()
    {
        delete[] next;
        next = nullptr;
    };
    /* data */
};

struct pathinfo
{
    float cost;
    float time;

    int npath;
    int *path;
    void all_memory()
    {
        path = new int [npath];
    };
    void del_memory()
    {
        delete[] path;
        path = nullptr;
    };
};

struct InstanceInfo
{
    int Nnodes;
    int Narcs;
    int Npaths;
    int start;
    int finish;
    float cost;

    arcinfo *arcs;
    nodeinfo *nodes;
    InstanceInfo()
    {
        Nnodes = 0;
        Narcs = 0;
        Npaths = 0;
        start = -1;
        finish = -1;
        arcs = nullptr;
        nodes = nullptr;
    }

    void all_memory()
    {
        arcs = new arcinfo [Narcs];
        nodes = new nodeinfo [Nnodes];
    };

    void del_memory()
    {
        delete [] arcs;
        arcs = nullptr;
        delete [] nodes;
        nodes = nullptr;
    };
};

#endif