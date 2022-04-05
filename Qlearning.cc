#ifndef _Qlearning_c
#define _Qlearning_c

#include "Qlearning.h"

#include<iostream>
using std::cout;
using std::endl;

#define TNNCONSTANT 10000000
#define RHSCONSTANT 10000000

//We need to put print here
//We need to put print here

void Qlearning(InstanceInfo *Info)
{

    //checking requirements 
    if (Info->Nnodes> TNNCONSTANT || Info->constraint>RHSCONSTANT)
    {
        cout<<"Info->nodes> TNNCONSTANT!!!"<<endl;
        exit(12);
    }

    // inner global variables
    statesinfo *tmp_state;


    // termination conditions
    int Dtn = Info->finish; // destination


    //Staring State
    statesinfo *PStart = new statesinfo(ObjStatus::MINIMUM);

    //how to delete the graph created???

    // filling the information for the state
    PStart->NodeInfo.node = Info->start; // which node to start
    PStart->NodeInfo.Rrhs = 0;
    PStart->ID =PStart->NodeInfo.CreateID();
    
    
    
    //Creating dictionary of the created nodes
    //why?
    // for connecting the repeated states together

    std::map<long long, statesinfo*> DicState;
    std::map<long long, statesinfo*>::iterator idxState;

    
    long long index = PStart->ID;
    
    idxState = DicState.find(index);
    //searching for the index in dic
    if (idxState == DicState.end()) 
    {
        tmp_state = PStart;
        DicState[index] = tmp_state;
    }
    else
    {
        cout<<"this cannot happen!!"<<endl;
        exit(33);
        //tmp_state = idxState->second;
    }
    
    int *ListStateOnPath= new int [Info->Nnodes];

    int Fr;
    int NTo; // Number of next
    int ITo; // ID or name name of the next node

    float FrRhs;
    float ToRhs;
    arcinfo *tmp_arc;

    while (true) //iteration
    {

        statesinfo *st = PStart;

        // cout<<"size is  "<< DicState.size() <<endl;

        // record the path info
        
        do
        {
            
            // Preparation
            // Preparation
            // Preparation
            // Preparation

            if (st->done)
            {

                Fr = st->NodeInfo.node;
                FrRhs = st->NodeInfo.Rrhs;

                NTo = Info->nodes[Fr].Nnbr;

                for (size_t i = 0; i < NTo; i++)
                {
                    tmp_arc = Info->nodes[Fr].arcs[i];
                    ITo = tmp_arc->ed;
                    ToRhs = tmp_arc->time + FrRhs;

                    index = CreateStateID(ITo, ToRhs);
                    idxState = DicState.find(index);
                    //searching for the index in dic
                    if (idxState == DicState.end()) 
                    {
                        //creating new state

                        tmp_state = new statesinfo(MINIMUM);

                        //node info
                        tmp_state.ID = index;
                        tmp_state->NodeInfo.node = ITo;
                        tmp_state->NodeInfo.Rrhs = ToRhs;

                        //state info connnections
                        st->next[st->CntNX] = tmp_state;
                        st->Avalue[st->CntNX] = std::numeric_limits<float>::max();
                        st->CntNX++;
                        DicState[index] = tmp_state;
                    }
                    else
                    {
                        // we found it
                        tmp_state = idxState->second;

                        //state info connnections
                        st->next[st->CntNX] = tmp_state;
                        st->Avalue[st->CntNX] = std::numeric_limits<float>::max();
                        st->CntNX++;
                        DicState[index] = tmp_state;
                    }
                }
                
                st->done = true;
            }
            //==========//==========//==========//==========//==========
            
            

            //Select and move
            //Select and move
            //Select and move
            //Select and move


            //==========//==========//==========//==========//==========

            //Check the terminations
            //If termination conditions 1
            //If termination conditions 2
            //If termination conditions 3
            //If termination conditions 4


            //==========//==========//==========//==========//==========
            

        
        }while(true) //path termination condition 1- resource 2- reach to destination 
        
        //updating the states
        //updating the qvalues

        break;
    }


    //deleting section
    delete [] ListStateOnPath;

}

#endif