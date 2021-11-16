#ifndef _variabels_h
#define _variabels_h

#include <math.h>
#include <limits.h>

#define epz 0.0000001
#define epzv2 0.1

#define MAX 1
#define MIN 0

#include <map>


enum TypeOfConstraint{Time, Weight};


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


struct lableinfo
{
    float time;
    float cost;
    lableinfo();
    bool operator < (const lableinfo& rhs) const;
    bool operator > (const lableinfo& rhs) const;
    bool operator == (const lableinfo& rhs) const;
    struct lableinfo& operator+=(const arcinfo *rhs)
    {
        time += rhs->time;
        cost += rhs->cost;
        return *this;
    };
};


struct nodeinfo
{
    int index;
    float x;
    float y;
    int Nnbr;
    int *nbr;
    lableinfo lable;
    
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

    float sol_obj;
    int *sol_path;
    int sol_n;

    arcinfo *arcs;
    nodeinfo *nodes;

    int Npaths;
    int *PathsN;
    int **PathsO;
    float *PathsT;
    float *PathsW;
    bool *Dijk_S[2];
    float *Dijk_f[2];
    char add_out[300];
    char name[300];
    char Dijk_name[300];
    
    std::map<long long, arcinfo*> Dic;
    std::map<long long, arcinfo*>::iterator idx;
    long long index;



    // solution variables
    float SolF;

    InstanceInfo();
    
    void create_map();

    arcinfo * FindEdge(int fm, int to);
    arcinfo * FindEdgeM(int fm, int to);
    
    void dump_dijk();
    void all_memory();
    void all_dijk();
    void all_node();
    void all_memory_test_B();
    void del_memory();
};


struct traverseinfo
{
    bool *SltB;
    int SltN;
    int *SltL;
    float obj;
    
    lableinfo lable;
    traverseinfo *next;
    int Nnodes;
    nodeinfo *Node;

    traverseinfo(int N, nodeinfo *Nd);
    void allocate();
    void deallocate();
};


#endif