#ifndef _inputesting_c
#define _inputesting_c

#include<iostream>
#include"Inputesting.h"
#include"variables.h"

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

            int c = Info->FindEdge(A,B);

            if (c==-1)
            {
                std::cout<<"input is piece of crap!!!"<<std::endl;
                exit(12);
            }
                        
            Time += Info->arcs[c].cost;
            Weight += Info->arcs[c].time;
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

#endif