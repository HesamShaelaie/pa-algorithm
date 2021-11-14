#ifndef _inputesting_c
#define _inputesting_c

#include<iostream>
#include"Inputesting.h"
#include"variables.h"
#include"mathmatics.h"



void InputTesting(InstanceInfo *Info)
{
    for (int p = 0; p < Info->Npaths; p++)
    {
        float Time=0;
        float Weight=0;

        for (int x = 1; x < Info->PathsN[p]; x++)
        {
            int A = Info->PathsO[p][x-1];
            int B = Info->PathsO[p][x];

            arcinfo *c = Info->FindEdge(A,B);

            if (c==nullptr)
            {
                std::cout<<"input is piece of crap!!!"<<std::endl;
                exit(12);
            }
                        
            Time += c->cost;
            Weight += c->time;
        }

        if (abs(Time - Info->PathsT[p])> epzv2)
        {
            std::cout<<"if (abs(Time - Info->PathsT[p])>epz)"<<std::endl;
            std::cout<<abs(Time - Info->PathsT[p])<<std::endl;
            exit(1113);
        }

        if (abs(Weight - Info->PathsW[p])> epzv2)
        {
            std::cout<<"if (abs(Weight - Info->PathsW[p])>epz)"<<std::endl;
            std::cout<<abs(Weight - Info->PathsW[p])<<std::endl;
            exit(1115);
        }
    }
}

void InputTesting_Find(InstanceInfo *Info)
{
    int ar;
    int fm;
    int to;
    arcinfo *AR;

    for (int x = 0; x < 100; x++)
    {
        ar = rand_int_bet(0, Info->Narcs-1);
        fm = Info->arcs[ar].st;
        to = Info->arcs[ar].ed;

        AR = Info->FindEdge(fm,to);

        if (fm!= AR->st || to != AR->ed)
        {
            std::cout<<"if (fm!= AR->st || to != AR->ed)"<<std::endl;
            std::cout<<"InputTesting_Find"<<std::endl;
            exit(333);
        }
    }
}


void InputTesting_FindM(InstanceInfo *Info)
{
    int ar;
    int fm;
    int to;
    arcinfo *AR;

    for (int x = 0; x < 100; x++)
    {
        ar = rand_int_bet(0, Info->Narcs-1);
        fm = Info->arcs[ar].st;
        to = Info->arcs[ar].ed;

        AR = Info->FindEdgeM(fm,to);

        if (fm!= AR->st || to != AR->ed)
        {
            std::cout<<"if (fm!= AR->st || to != AR->ed)"<<std::endl;
            std::cout<<"InputTesting_FindM"<<std::endl;
            exit(333);
        }
    }
}



#endif