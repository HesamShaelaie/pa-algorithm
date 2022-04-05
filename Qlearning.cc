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



int EpsilonGreedy(int limit, int CntNx, float *Avalues, ObjStatus State) //limit should be between 0 and 100 -> if it is 10 means 0 to 10 we will go for exploration
{
    int RndStart = rand()%101;

    float tmp;
    int index;

    if (RndStart <= limit)
    {   
        index = rand()%CntNx;
    }
    else
    {
        if (State = ObjStatus::MINIMUM)
        {
            tmp =  std::numeric_limits<float>::max();
            index = -1;
            for (int x = 0; x < CntNx; x++)
            {
                if(Avalues[x]<tmp)
                {
                    tmp = Avalues[x];
                    index = x;
                }
            }

            if (index == -1)
            {
                cout<<"something is wrong in epsilong greedy!!"<<endl;
                exit(555);
            }
            
            
        }
        else
        {
            tmp =  std::numeric_limits<float>::min();
            
            index = -1;
            for (int x = 0; x < CntNx; x++)
            {
                if(Avalues[x]>tmp)
                {
                    tmp = Avalues[x];
                    index = x;
                }
            }

            if (index == -1)
            {
                cout<<"something is wrong in epsilong greedy!!"<<endl;
                exit(555);
            }

        }
    }

    return index;
}



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
    ObjStatus StateOfOptimization = ObjStatus::MINIMUM;

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

    int Fr;
    int NTo; // Number of next
    int ITo; // ID or name name of the next node

    float FrRhs;
    float ToRhs;

    int NextMoveIndex;
    arcinfo *tmp_arc;
    int ExplorationLimit = 20; // 0-Exploration goes to exploration the rest goes to use the current answers

    int NodeOnPath;
    int BestNdPath;
    int *ListStateOnPath= new int [Info->Nnodes];
    int *BestLSateOnPath= new int [Info->Nnodes];

    statesinfo *StartFromHere;
    float CltObj  = 0;
    float bestObj = (ObjStatus::MINIMUM );
    

    while (true) //iteration
    {

        statesinfo *st = PStart;
        StartFromHere = st;
        NodeOnPath = 0;

        // cout<<"size is  "<< DicState.size() <<endl;

        // record the path info
        
        do
        {
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
            
            //Selecing action based on the epsilon greedy
            NextMoveIndex = EpsilonGreedy(ExplorationLimit, st->CntNX, st->Avalue, ObjStatus::MINIMUM);
            // record the path
            ListStateOnPath[NodeOnPath++] = NextMoveIndex;
            // move
            st = st->next[NextMoveIndex];

            //==========//==========//==========//==========//==========

            //Check the terminations

            //If termination conditions 1 // did we reach to the destination
            if (st->NodeInfo.node == Info->finish)
            {
                /* code */
            }
            
            //If termination conditions 2 // did we reach to infeasibility
            

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