#ifndef _variabels_h
#define _variabels_h

#include <math.h>
#include <limits.h>

#define epz 0.0000001
#define epzv2 0.1

#include <map>

struct arcinfo
{
    bool key;
    int st;
    int ed;
    float cost;
    float time;

    arcinfo();

    bool operator < (const arcinfo& rhs) const;
    bool operator > (const arcinfo& rhs) const;
    bool operator == (const arcinfo& rhs) const;

};

struct nodeinfo
{
    float x;
    float y;
    int Nnbr;
    int *next;
    
    nodeinfo();
    void all_memory();
    void del_memory();
};

struct pathinfo
{
    float cost;
    float time;

    int npath;
    int *path;
    pathinfo();
    void all_memory();
    void del_memory();
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
    std::map<long long, arcinfo*>::iterator idx;
    long long index;
    InstanceInfo();
    int FindEdge(int fm, int to);

    void create_map();
    arcinfo * FindEdgeM(int fm, int to);

    void all_memory();
    void all_dijk();
    void all_memory_test_A();
    void all_memory_test_B();
    void del_memory();

    
};

#endif