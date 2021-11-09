#ifndef _reading_c
#define _reading_c


#include<fstream>
#include<iostream>

using namespace std;

#include"reading.h"

InstanceInfo* reading (const char *add_input)
{

    InstanceInfo *Info = new InstanceInfo;

    ifstream input;
    input.open(add_input);

    if(!input)
    {
        cout<<"cannot read!!"<<endl;
        exit(11);
    }

    string stmp;

    input >> stmp;
    input >> Info->Nnodes;

    input >> stmp;
    input >> Info->Narcs;

    input >> stmp;
    input >> Info->start;

    input >> stmp;
    input >> Info->finish;

    input >> stmp;
    input >> Info->cost;

    Info->all_memory();

    for (int a = 0; a < Info->Narcs; a++)
    {
        input >> stmp;
        input >>Info->arcs[a].st;
        input >>Info->arcs[a].ed;
        input >>Info->arcs[a].time;
        input >>Info->arcs[a].cost;
    }
    
    cout<<Info->arcs[Info->Narcs-1].cost<<endl;
    exit(12);

    return Info;

}


#endif