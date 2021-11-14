#ifndef _variabels_c
#define _variabels_c

#include "variables.h"
#include "index_creator.h"

#include <iostream>
#include <math.h>
#include <limits.h>
#include <map>

using std::endl;
using std::cout;

arcinfo::arcinfo()
{
    key = false;
    st = -1;
    ed = -1;
    cost = 0;
    time = 0;
}

bool arcinfo::operator < (const arcinfo& rhs) const
{
    if (time + epz < rhs.time)
        return true;
    else
        return false;

}

bool arcinfo::operator > (const arcinfo& rhs) const
{
    if (time - epz > rhs.time)
        return true;
    else
        return false;

}


bool arcinfo::operator == (const arcinfo& rhs) const
{
    if (abs(time - rhs.time)< epz)
        return true;
    else
        return false;
}

nodeinfo::nodeinfo()
{
    x = -1;
    y = -1;
    Nnbr = 0;
    next = nullptr;

}

void nodeinfo::all_memory()
{
    next = new int [Nnbr];
};

void nodeinfo::del_memory()
{
    delete[] next;
    next = nullptr;
};

pathinfo::pathinfo()
{
    cost=0;
    time=0;

    npath=0;
    path=nullptr;
}

void pathinfo::all_memory()
{
    path = new int [npath];
};
void pathinfo::del_memory()
{
    delete[] path;
    path = nullptr;
};

InstanceInfo::InstanceInfo()
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

arcinfo * InstanceInfo::FindEdge(int fm, int to)
{
    int find = -1;
    for (int x = 0; x < Narcs; x++)
    {
        if (fm == arcs[x].st && to == arcs[x].ed)
            return &arcs[x];

        if (fm<arcs[x].st)
            break;
        else if(fm ==arcs[x].st && to < arcs[x].ed)
            break;
    
    }
    
    return nullptr;
}


void InstanceInfo::all_memory()
{
    arcs = new arcinfo [Narcs];
    nodes = new nodeinfo [Nnodes];
};

void InstanceInfo::all_dijk()
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

void InstanceInfo::all_memory_test_A()
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



void InstanceInfo::all_memory_test_B()
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



void InstanceInfo::del_memory()
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

    if(!Dic.empty())
        Dic.clear();
};


arcinfo * InstanceInfo::FindEdgeM(int fm, int to)
{
    arcinfo * tmp;

    index = index_creator(Nnodes, fm, to);
    idx = Dic.find(index);

    if (idx == Dic.end()) 
    {
        cout<<"cannot fine the edge!!"<<endl;
        exit(1113);
    }
    else
       tmp = idx->second;

    return tmp;
}

void InstanceInfo::create_map()
{
    int pointA;
    int pointB;
    

    for (int a = 0; a < Narcs; a++)
    {
        pointA = arcs[a].st;
        pointB = arcs[a].ed;

        index = index_creator(Nnodes, pointA, pointB);

        if (Dic.find(index) == Dic.end()) 
        {
            arcinfo *tmp_arc;
            tmp_arc = &arcs[a];
            Dic[index] = tmp_arc;
        }
        else
        {
            cout<<"InstanceInfo: section read data."<<endl;
            cout<<"something wrong at the reading data"<<endl;
        }
    }
}



#endif