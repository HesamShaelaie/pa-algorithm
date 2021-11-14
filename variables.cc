#ifndef _variabels_c
#define _variabels_c

#include "variables.h"
#include <math.h>
#include <limits.h>
#include <map>


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
    
    int start;
    int finish;
    float cost;

    arcinfo *arcs;
    nodeinfo *nodes;
    int *Nnb;
    int **Nb;

    int Npaths;
    int *PathsN;
    int **PathsO;
    float *PathsT;
    float *PathsW;
    bool *Dijk_S[2];
    float *Dijk_f[2];
    std::map<long long, arcinfo*> Dic;

    InstanceInfo()
    {
        Nnodes = 0;
        Narcs = 0;
        Npaths = 0;
        start = -1;
        finish = -1;
        arcs = nullptr;
        nodes = nullptr;
        Nnb = nullptr;
        PathsN = nullptr;
        PathsO = nullptr;
        PathsT = nullptr;
        PathsW = nullptr;

        Dijk_S[0] = nullptr;
        Dijk_S[1] = nullptr;
        Dijk_f[0] = nullptr;
        Dijk_f[1] = nullptr;
    }

    int FindEdge(int fm, int to)
    {
        int find = -1;
        for (int x = 0; x < Narcs; x++)
        {
            if (fm == arcs[x].st && to == arcs[x].ed)
                return x;

            if (fm<arcs[x].st)
                break;
            else if(fm ==arcs[x].st && to < arcs[x].ed)
                break;
        
        }
        
        return -1;
    }

    void all_memory()
    {
        arcs = new arcinfo [Narcs];
        nodes = new nodeinfo [Nnodes];
    };

    void all_dijk()
    {
        Dijk_S[0] = new bool[Nnodes];
        Dijk_S[1] = new bool[Nnodes];

        Dijk_f[0] = new float[Nnodes];
        Dijk_f[1] = new float[Nnodes];

        for (int n = 0; n < Nnodes; n++)
        {
            Dijk_S[0][n] = false;
            Dijk_S[1][n] = false;
            Dijk_f[0][n] = std::numeric_limits<float>::max();
            Dijk_f[1][n] = std::numeric_limits<float>::max();
        }
    }

    void all_memory_test_A()
    {
        Nnb = new int [Nnodes];
        Nb = new int *[Nnodes];
        for (int n = 0; n < Nnodes; n++)
        {
            Nb[n] = new int [Nnodes];
            for (int x = 0; x < Nnodes; x++)
                Nb[n][x] = -1;
        }
        
    };



    void all_memory_test_B()
    {
        PathsN = new int [Npaths];
        PathsT = new float [Npaths];
        PathsW = new float [Npaths];
        PathsO = new int *[Npaths];
        for (int p = 0; p < Npaths; p++)
        {
            PathsN[p] = 0;
            PathsT[p] = 0;
            PathsW[p] = 0;
            PathsO[p] = new int [Nnodes];
            for (int x = 0; x < Nnodes; x++)
                PathsO[p][x] = -1;
        }
        
    };



    void del_memory()
    {
        if (!arcs)
        {
            delete [] arcs;
            arcs = nullptr;
        }
        
        if (!nodes)
        {
            delete [] nodes;
            nodes = nullptr;
        }
        
        if (!Nnb)
        {   
            for (int n = 0; n < Nnodes; n++)
                delete Nb[n];

            delete [] Nnb;
            Nnb = nullptr;
            delete [] Nb;
            Nb = nullptr;
        }

        if (!PathsN)
        {
            for (int p = 0; p < Npaths; p++)
                delete[] PathsO[p];
            delete[] PathsN;
            delete[] PathsO;
            delete[] PathsT;
            delete[] PathsW;
            PathsN = nullptr;
            PathsO = nullptr;
            PathsT = nullptr;
            PathsW = nullptr;
        }
        if( !Dijk_S[0])
        {
            delete[] Dijk_S[0];
            delete[] Dijk_S[1];

            Dijk_S[0] = nullptr;
            Dijk_S[1] = nullptr;

            delete[] Dijk_f[0];
            delete[] Dijk_f[1];

            Dijk_f[0] = nullptr;
            Dijk_f[1] = nullptr;
        } 
        

    };
};

#endif