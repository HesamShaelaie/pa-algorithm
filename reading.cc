#ifndef _reading_c
#define _reading_c

#include<fstream>
#include<iostream>
#include<string>
#include<stdio.h>

using namespace std;

#include"config_t.h"
#include"config_r.h"

#include"reading.h"

InstanceInfo* reading (const config_t &configt, const config_r &configr, int x)   
{

    const char *add_input = configr.Tadd[x];
    InstanceInfo *Info = new InstanceInfo;
    
    strncpy(Info->name , configr.Tname[x],300);
    strncpy(Info->add_out , configr.address_out,300);

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
    input >> Info->constraint;

    Info->all_memory();

    input >> stmp;
    input >> stmp;
    input >> stmp;
    input >> stmp;
    input >> stmp;
    
    for (int a = 0; a < Info->Narcs; a++)
    {
        input >> stmp;
        input >>Info->arcs[a].st;
        input >>Info->arcs[a].ed;
        input >>Info->arcs[a].cost;
        input >>Info->arcs[a].time;
    }

    Info->all_node();
    for (int n = 0; n < Info->Nnodes; n++)
    {
        input >> Info->nodes[n].index;
        if (n!= Info->nodes[n].index)
        {
            cout<<"n!= atoi(stmp)"<<endl;
            exit(123);
        }

        input >> Info->nodes[n].Nnbr;
        Info->nodes[n].all_memory();

        for (int x = 0; x < Info->nodes[n].Nnbr; x++)
            input >> Info->nodes[n].nbr[x];
    }


    if (configt.testing)
    {
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


        for (int p = 0; p < Info->Nnodes; p++)
        {
            input>>stmp;
            input>>Info->nodes[p].x;
            input>>Info->nodes[p].y;
        }
        
    }
    
    input.close();
    // paper 
    // balas
    // balas I should genera integer progrram dynamic program. 

    // writing the story
    // phylosophy for 
    // repo 

    return Info;

}


#endif