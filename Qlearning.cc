#ifndef _Qlearning_c
#define _Qlearning_c


#include<unistd.h>
#include<iostream>
#include <fstream>
#include <sys/stat.h>
#include"exitence.h"
#include <iomanip>
using std::cout;
using std::endl;
using std::ofstream;
using std::setw;
#include "Qlearning.h"


#define TNNCONSTANT 10000000
#define RHSCONSTANT 10000000

//We need to put print here
//We need to put print here
enum TerminationStatus {NotDetermined, Destination, Constraint, LowerBound, UpperBound};


long long CreateStateID(int node, float Rrhs)
{
    return node * pow(10,9) + int(Rrhs*100);
}


long long CreateStateID(const NodeReferenceCSP &tmpnode)
{
    return tmpnode.node * pow(10,9) + int(tmpnode.Rrhs*100);
}



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
        if (State == ObjStatus::MINIMUM)
        {
            tmp =  std::numeric_limits<float>::max();
            index = -1;
            for (int x = 0; x < CntNx; x++)
            {
                if(Avalues[x]<=tmp)
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
                if(Avalues[x]>=tmp)
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

void Qlearning(InstanceInfo *Info, bool dump)
{
    //checking requirements for what? for the hashing
    if (Info->Nnodes> TNNCONSTANT || Info->constraint>RHSCONSTANT)
    {
        cout<<"Info->nodes> TNNCONSTANT!!!"<<endl;
        exit(12);
    }

    char add_raw_A[300];//all
    char add_raw_B[300];//best
    char add_out_A[300];
    char add_out_B[300];
    getcwd(add_raw_A,256); // getting the folder of the codes
    getcwd(add_raw_B,256); // getting the folder of the codes
    strcat(add_raw_A, "/QLearningA"); // add the instance to the address
    strcat(add_raw_B, "/QLearningB"); // add the instance to the address
    ofstream out;
    ofstream outB;
    
    if (dump)
    {
        if (!exists(add_raw_A))
            mkdir(add_raw_A,0777); // if not make the folder
        sprintf(add_out_A, "%s/%s", add_raw_A, Info->name);// add general info

        
        out.open(add_out_A);
        if (!out)
        {
            cout<<"cannot create qlearning output files!!"<<endl;
            exit(12);
        }
        out<<"Paths generated:"<<endl<<endl;


        /// bests

        if (!exists(add_raw_B))
            mkdir(add_raw_B,0777); // if not make the folder
        sprintf(add_out_B, "%s/%s", add_raw_B, Info->name);// add general info

        
        outB.open(add_out_B);
        if (!outB)
        {
            cout<<"cannot create qlearning output files (best)!!"<<endl;
            exit(12);
        }

        outB<<"Paths generated:"<<endl<<endl;
    }
    

    // inner global variables
    statesinfo *tmp_state;
    ObjStatus StateOfOptimization = ObjStatus::MINIMUM;

    // termination conditions
    int Dtn = Info->finish; // destination

    //Staring State
    statesinfo *PStart = new statesinfo(ObjStatus::MINIMUM);
    statesinfo *PLast;
    statesinfo *st;

    PLast = PStart;

    //how to delete the graph created???

    // filling the information for the state
    PStart->NodeInfo.node = Info->start; // which node to start
    PStart->NodeInfo.Rrhs = 0;
    PStart->ID =CreateStateID(PStart->NodeInfo);
    
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

    statesinfo *StUpdate;
    float CltObj  = 0;
    float bestObj = std::numeric_limits<float>::max();
    

    int ContNumberOfPathGenerated = 0;
    TerminationStatus TrmPath = TerminationStatus::NotDetermined;
    
    float BestConstraint;
    int NgeneratedStates = 1;
    int NRepeatedStates = 0;
    int Cnt_Termination = 0;
    while (Cnt_Termination < 100) //iteration
    {

        st = PStart;
        NodeOnPath = 0;
        CltObj = 0;
        TrmPath = TerminationStatus::NotDetermined;
        // cout<<"size is  "<< DicState.size() <<endl;

        // record the path info
        
        do
        {
            // Preparation

            if (!st->done)
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
                        NgeneratedStates++;
                        //creating new state
                        tmp_state = new statesinfo(MINIMUM);

                        //node info
                        tmp_state->ID = index;
                        tmp_state->NodeInfo.node = ITo;
                        tmp_state->NodeInfo.Rrhs = ToRhs;

                        //state info connnections
                        st->next[st->CntNX] = tmp_state;
                        st->arcnext[st->CntNX] = tmp_arc;
                        st->Avalue[st->CntNX] = std::numeric_limits<float>::max();
                        st->CntNX++;
                        DicState[index] = tmp_state;
                        PLast->DeleteingLine = tmp_state;
                        PLast = tmp_state;
                    }
                    else
                    {
                        NRepeatedStates++;
                        // we found it
                        tmp_state = idxState->second;

                        //state info connnections
                        st->next[st->CntNX] = tmp_state;
                        st->arcnext[st->CntNX] = tmp_arc;
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
            CltObj += st->arcnext[NextMoveIndex]->cost;
            // Move
            StUpdate = st;
            st = st->next[NextMoveIndex]; 

            //==========//==========//==========//==========//==========

            //Check the terminations

            //If termination conditions 1 // did we reach to the destination
            if (st->NodeInfo.node == Info->finish)
            {
                TrmPath = TerminationStatus::Destination;
                //Update
                //StUpdate->Avalue[NextMoveIndex] = 
                break;
            }
            
            //If termination conditions 2 // did we reach to infeasibility
            if (st->NodeInfo.Rrhs >Info->constraint)
            {
                TrmPath = TerminationStatus::Constraint;
                //Update
                //StUpdate->Avalue[NextMoveIndex] = 
                break;
            }

            //if take more termination condition like PA algorithm

            //==========//==========//==========//==========//==========
            

        
        }while(true); //path termination condition 1- resource 2- reach to destination 


        ContNumberOfPathGenerated++;
        if (CltObj < bestObj)
        {
            bestObj = CltObj;
            BestNdPath = NodeOnPath;
            BestConstraint = st->NodeInfo.Rrhs;
            for (int x = 0; x < BestNdPath; x++)
            {
                BestLSateOnPath[x] = ListStateOnPath[x];
            }
        }
        
        // Updating the qvalues

        





        Cnt_Termination++;



        // Printing the results
        if (dump)
        {
            //All
           
            if (TrmPath == TerminationStatus::Destination)
            {
                out<<setw(4)<<"D";
                
            } else if (TrmPath == TerminationStatus::Constraint)
            {
                out<<setw(4)<<"C";
            }
            else
            {
                out<<setw(4)<<"X";
            }
           
           

            out << setw(8) << "Obj::"<<setw(8)<< CltObj;
            out << setw(8) << "Con::"<<setw(8)<< st->NodeInfo.Rrhs;
            out << setw(8) << "Npt::"<<setw(8)<< NodeOnPath<<setw(8)<< "||";

            //starting the path from the beginning!!!
            st = PStart;

            out << setw(4)<<st->NodeInfo.node;
            for (int z = 0; z < NodeOnPath; z++)
            {
                NextMoveIndex =  ListStateOnPath[z];
                st = st->next[NextMoveIndex];
                out << setw(4)<<st->NodeInfo.node;
            }
            out<<endl;
        }

        if (dump)
        {
            //Best
           
            outB << setw(8) << "Itr::"<<setw(8)<< Cnt_Termination;
            outB << setw(8) << "StG::"<<setw(8)<< NgeneratedStates;
            outB << setw(8) << "StR::"<<setw(8)<< NRepeatedStates;
            outB << setw(8) << "Obj::"<<setw(8)<< bestObj;
            outB << setw(8) << "Con::"<<setw(8)<< BestConstraint;
            outB << setw(8) << "Npt::"<<setw(8)<< BestNdPath << setw(8) << "||";

            //starting the path from the beginning!!!
            st = PStart;

            outB << setw(4)<<st->NodeInfo.node;
            for (int z = 0; z < BestNdPath; z++)
            {
                NextMoveIndex =  BestLSateOnPath[z];
                st = st->next[NextMoveIndex];
                outB << setw(4)<<st->NodeInfo.node;
            }
            outB<<endl;
        }
        
    }

    if (dump)
    {
        out.close();
        outB.close();
    }


    


    // Deleteing the network
    st = PStart;
    while(st)
    {
        PLast = st;
        st = st->DeleteingLine;
        delete PLast;
    }
     
    delete [] ListStateOnPath;
    delete [] BestLSateOnPath;

}

#endif