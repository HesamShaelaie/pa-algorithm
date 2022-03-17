#ifndef _variabels_c
#define _variabels_c

#include "variables.h"
#include "index_creator.h"
#include"exitence.h"

#include <iostream>
#include <math.h>
#include <limits.h>
#include <map>
#include <fstream>
#include <sys/stat.h>
#include <iomanip>

using std::endl;
using std::cout;
using std::setw;

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
    nbr = nullptr;
}

void nodeinfo::all_memory()
{
    nbr = new int [Nnbr];
};

void nodeinfo::del_memory()
{
    delete[] nbr;
    nbr = nullptr;
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
    SolF = 0;
    
    PathsN = nullptr;
    PathsO = nullptr;
    PathsT = nullptr;
    PathsW = nullptr;

    Dijk_S[0] = nullptr;
    Dijk_S[1] = nullptr;
    Dijk_f[0] = nullptr;
    Dijk_f[1] = nullptr;
    
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

void InstanceInfo::all_node()
{
    nodes = new nodeinfo [Nnodes];

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
    
    if (!nodes)
    {   
        for (int N = 0; N < Nnodes; N++)
        {
            if (nodes[N].Nnbr)
                delete[] nodes[N].nbr;
        }
        
        delete[] nodes;
        nodes = nullptr;
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

arcinfo * InstanceInfo::FindEdgeM(int fm, int to)
{

    index = index_creator(Nnodes, fm, to);
    idx = Dic.find(index);

    if (idx == Dic.end()) 
        return nullptr;
    else
        return idx->second;
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

void InstanceInfo::dump_dijk()
{
    if (!exists(add_out))
        mkdir(add_out,0777);

    sprintf(Dijk_name, "%s/%s-D.txt", add_out, name);
    
    
    std::ofstream out;
    out.open(Dijk_name);

    if(!out)
    {
        cout<<"cannot write dijk!!"<<endl;
        exit(11);
    }    


    out << setw(4) << "#";
    out << setw(10) << "TimeS";
    out << setw(10) << "CostS";
    out << setw(15) << "Time";
    out << setw(15) << "Cost"<<endl<<endl;

    for (int n = 0; n < Nnodes; n++)
    {
        out << setw(4) << n;
        out << setw(10) << Dijk_S[0][n];
        out << setw(10) << Dijk_S[1][n];
        out << setw(15) << Dijk_f[0][n];
        out << setw(15) << Dijk_f[1][n];
        out << endl;
    }    
}

lableinfo::lableinfo()
{
    time =0;
    cost =0;
}

/*
void InstanceInfo::all_sol()
{
    Lables = new lableinfo [Nnodes];
}
*/
// we saw numbers aling the way but we did not track them
// give you an enalogy 

//traverseinfo::deallocate

#endif