#ifndef _Qlearning_h
#define _Qlearning_h


#include"variables.h"

#include <map>


enum ObjStatus {MINIMUM, MAXIMUM};
#define nx 100  //max degree of each node



struct NodeReferenceCSP
{
    int node = -1;
    float Rrhs = -1;
};


long long CreateStateID(int node, float Rrhs);
long long CreateStateID(const NodeReferenceCSP &tmpnode);



struct statesinfo
{   
    // general information on the RL problems
    bool done = false;
    long long ID = -1;
    int CntNX = 0;
    float Qvalue = 0;
    float Avalue[nx];
    statesinfo *next[nx];
    arcinfo *arcnext[nx];
    statesinfo *DeleteingLine = nullptr;
    // supper important information

    NodeReferenceCSP NodeInfo;

    statesinfo(ObjStatus ObSt)
    {
        if (ObSt == ObjStatus::MINIMUM)
        {
            Qvalue = std::numeric_limits<float>::max();
        }
        else
        {
            Qvalue = std::numeric_limits<float>::min();
        }
    }
};

int EpsilonGreedy(int limit, int CntNx, float *Avalues, ObjStatus State);
void Qlearning(InstanceInfo *Info, bool dump = false);



#endif