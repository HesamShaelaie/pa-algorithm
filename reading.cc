#ifndef _reading_c
#define _reading_c


#include<fstream>
#include<iostream>

using namespace std;
#include"config_t.h"
#include"config_r.h"

#include"reading.h"

InstanceInfo* reading (const config_t &configt, const config_r &configr, int x)   
{

    const char *add_input = configr.Tadd[x];
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

    if (configt.testing)
    {
        Info->all_memory_test_A();

        for (int n = 0; n < Info->Nnodes; n++)
        {
            input >> stmp;
            if (n!= stoi(stmp))
            {
                cout<<"n!= atoi(stmp)"<<endl;
                exit(123);
            }

            input >> Info->Nnb[n];
            for (int x = 0; x < Info->Nnb[n]; x++)
                input>>Info->Nb[n][x];
        }


        input >> Info->Npaths;
        Info->all_memory_test_B();


        for (int p = 0; p < Info->Npaths; p++)
        {
            input>>stmp;
            input>>Info->PathsN[p];
            input>>Info->PathsT[p];
            input>>Info->PathsW[p];
            for (int x = 0; x < Info->PathsN[p]; x++)
                input>>Info->PathsO[p][x];
        }

    }
    
    


    // paper 
    // balas
    // balas I should genera integer progrram dynamic program. 

    // writing the story
    // phylosophy for 
    // repo 

    return Info;

}


#endif