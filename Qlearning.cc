#ifndef _Qlearning_c
#define _Qlearning_c

#include "Qlearning.h"

#include<iostream>
using std::cout;
using std::endl;

#define TNNCONSTANT 10000000
#define RHSCONSTANT 10000000



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

    int fr;
    int Nto; // number of next
    int Ito; // ID or name name of the next node

    while (true) //iteration
    {

        statesinfo *st = PStart;
        //cout<<"size is  "<< DicState.size() <<endl;
        // record the path info
        /*
        do
        {
            if (st->done)
            {

                fr = st->NodeInfo.node;
                Nto = Info->nodes[fr].Nnbr;
                for (size_t i = 0; i < Nto; i++)
                {
                    Ito = 
                }
                
                //to
                //calclulate the future node
                //check if it exist
                //if not
                // create state
                // add to the map
                // if yes connect this to that
                

            }
            








            //if termination conditions 1
            //if termination conditions 2
            //if termination conditions 3
            //if termination conditions 4


           
            

        
        }while(true) //path termination condition 1- resource 2- reach to destination 
        
        //updating the states
        //updating the qvalues
        */

        break;
    }


    //deleting section
    delete [] ListStateOnPath;

}

#endif