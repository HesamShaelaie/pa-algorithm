#ifndef _generating_data_c
#define _generating_data_c

#include "variables.h"
#include "generating_data.h"
#include "config_t.h"
#include "config_d.h"
#include "mathmatics.h"
#include "index_creator.h"
#include "exitence.h"

#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <math.h>
using namespace std;


void gen_data_without_feasibility(config_t configt, config_d configd)
{
    char address[300];
    strncat(address, configd.Address, 300);
    
    int Nint = configd.Nint;
    int Ntnd = configd.Ntnd;
    int Narcs = configd.Narcs;
    int Nfpath = configd.Nfpath;
    float Cor_min = configd.Cor_min;           
    float Cor_max = configd.Cor_max;
    float Cchance = configd.Cchance;
    float Cless = configd.Cless;
    float Cmore = configd.Cmore;
    int min_on_path = configd.min_on_path;
    int max_on_path = configd.max_on_path;
    int NNeighbor = configd.NNeighbor;
    float Tmin = configd.Tmin;
    float Tmax = configd.Tmax;

    
    ofstream out;
    for (int Instance = 0; Instance < Nint; Instance++)
    {
        //creating the name of the file
        //CSP-Number of nodes-fraction-instance.txt
        char name[300];
        sprintf(name, "%s/CSP-%d-%2d-%d.txt", address, Ntnd, int(configd.Farcs*100), Instance);

        out.open(name);

        out << "Nodes:  " << Ntnd << endl;
        out << "Narcs:  " << Narcs << endl;
        
        int startpoint;
        int pointA;
        int pointB;

        do
        {
            pointA = rand_int_bet(0,Ntnd-1);
            pointB = rand_int_bet(0,Ntnd-1);
            /* code */
        } while (pointA==pointB);

        out << "Snode:  " << pointA << endl;
        out << "Enode:  " << pointB << endl;
        
        
        long long index;
        map<long long, arcinfo*> Dic;


        int **Mnbr = new int *[Ntnd];
        bool **Mchk = new bool *[Ntnd];
        for (int i = 0; i < Ntnd; i++)
        {
            Mnbr[i]= new int[Ntnd+1];
            Mchk[i] = new bool [Ntnd];
            for (int j = 0; j < Ntnd+1; j++)
            {
                Mnbr[i][j]=0;
                Mchk[i][j] = false;
            }

        }

        int Cnt_arcs = 0;
        
        while (Cnt_arcs < Narcs)
        {
            
            pointA = rand_int_bet(0,Ntnd-1);
            pointB = rand_int_bet(0,Ntnd-1);
        
            index = index_creator(Ntnd, pointA, pointB);

            if (Dic.find(index) == Dic.end()) 
            {
                
                arcinfo *tmp_arc = new arcinfo;
                tmp_arc->st = pointA;
                tmp_arc->ed = pointB;
                tmp_arc->time = rand_float_bet(Tmin,Tmax, 2);

                if (rand_int_bet(0,10)>5)
                    tmp_arc->time = tmp_arc->time * Cmore;
                else
                    tmp_arc->time = tmp_arc->time * Cless;

                Dic[index] = tmp_arc;
                Cnt_arcs++;
                //cout<<Cnt_arcs<<endl;
            }

            
        }

        Cnt_arcs=0;
        for ( const auto &myPair: Dic )
        {
            out << setw(5) << Cnt_arcs;
            out << setw(10) << myPair.first;
            out << setw(5) << myPair.second->st ;
            out << setw(5) << myPair.second->ed ;
            out << setw(10) << myPair.second->cost ;
            out << setw(10) << myPair.second->time << endl;
            Cnt_arcs++;
        }

        try
        {
            for ( const auto &myPair: Dic )
            {
                int fm = myPair.second->st ;
                int to = myPair.second->ed ;
                if (Mchk[fm][to] ==true)
                {
                    cout<<string("Something is wrong in neighboor finding!!")<<endl;
                    throw string("Something is wrong in neighboor finding!!");
                }
                else
                {
                    Mchk[fm][to] = true;
                }
                int cc = ++Mnbr[fm][0];
                Mnbr[fm][cc] = to;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            exit(100);
        }
        
        out << endl << endl;

        for (int i = 0; i < Ntnd; i++)
            if (Mnbr[i][0]>0)
            {
                out << setw(4) << i;
                for (int j = 1; j <= Mnbr[i][0]; j++)
                {
                    out << setw(4) << Mnbr[i][j];
                }
                out<<endl;
            }
        out.close();

        //deleting part

        for ( const auto &myPair: Dic )
            delete myPair.second;
        
        for (int i = 0; i < Ntnd; i++)
        {
            delete[] Mnbr[i];
            delete[] Mchk[i];
        }
        delete[] Mnbr;
        delete[] Mchk;
    }
}


void gen_data_with_feasibility(config_t configt, config_d configd)
{
    //cout<< "gen_data_with_feasibility!!!" <<endl;

    // 1- get the address and create instance folder
    // 2- get the general informantion
        // coordination of the nodes
        // decision on the weights and costs

    // 3- decide on number of arcs
    // 4- decide on number of feasible paths
    // 5- add arcs as long as you reach to the number of arcs

    //==============================================================================
    //==============================================================================
    //==============================================================================

    char address[300];
    strncat(address, configd.Address, 300);
    
    int Nint = configd.Nint;        // number of instances
    int Ntnd = configd.Ntnd;        // number of nodes in the game
    int Narcs = configd.Narcs;      // number of arcs in the game total. comes from int(Permutation(Ntnd, 2)*Farcs);
    int Nfpath = configd.Nfpath;    // number of nodes on the path
    
    float Cor_min = configd.Cor_min;// min cordination on the map
    float Cor_max = configd.Cor_max;// max cordination on the map

    float Cchance = configd.Cchance;// with respect to the time we will increase or decrese the costs
    float Cless = configd.Cless;    // goes down or
    float Cmore = configd.Cmore;    // goes up

    int min_on_path = configd.min_on_path;      // min number of nodes on the path
    int max_on_path = configd.max_on_path;      // max number of nodes on the path
    int NNeighbor = configd.NNeighbor;          // number of neighbors

    //==============================================================================
    //==============================================================================
    //==============================================================================

    ofstream out;
    for (int Instance = 0; Instance < Nint; Instance++)
    {
        //Creating the name of the file
        //CSP-Number of nodes-fraction-instance.txt
        cout<<"starting instance (" <<Instance << ")!!"<<endl;

        nodeinfo *Nodes = new nodeinfo[Ntnd];
        for (int n = 1; n < Ntnd-1; n++)
        {
            Nodes[n].x = rand_float_bet(Cor_min,Cor_max,2);
            Nodes[n].y = rand_float_bet(Cor_min,Cor_max,2);
        }

        Nodes[0].x = Cor_min; // start at 0 for x
        Nodes[0].y = Cor_min; // start at 0 for y

        Nodes[Ntnd-1].x = Cor_max;  // finish at max for x
        Nodes[Ntnd-1].y = Cor_max;  // finish at max for y
 
        arcinfo **Neighbor = new arcinfo *[Ntnd]; // Ntnd number of nodes in the game
        arcinfo **Arces = new arcinfo *[Ntnd];

        for (int i = 0; i < Ntnd; i++)
        {
            Neighbor[i] = new arcinfo[Ntnd];
            Arces[i] = new arcinfo [Ntnd];
        }

        for (int i = 0; i < Ntnd; i++)
            for (int j = i+1; j < Ntnd; j++)
            {
                Arces[i][j].time = distance(Nodes[i],Nodes[j]);
                
                Arces[i][j].st=i;
                Arces[i][j].ed=j;
                if (rand_int_bet(0,10)>(Cchance*10))
                    Arces[i][j].cost = Arces[i][j].time * Cmore;
                else
                    Arces[i][j].cost = Arces[i][j].time * Cless;
                
                Arces[j][i] = Arces[i][j];
                Arces[j][i].st = j;
                Arces[j][i].ed = i;
            }

        for (int i = 0; i < Ntnd; i++)
        for (int j = 0; j < Ntnd; j++)
            Neighbor[i][j] = Arces[i][j];

        
        // sorting the neighbors
        for (int i = 0; i < Ntnd; i++)
        {
            arcinfo time_min; 
            int index_min;
            for (int j = 0; j < Ntnd-1; j++)
            {
                time_min = Neighbor[i][j];
                index_min = j;
                
                for (int k = j+1; k < Ntnd; k++)
                {
                    
                    if (Neighbor[i][k] < time_min)
                    {
                        time_min = Neighbor[i][k];
                        index_min = k;
                    }
                }

                Neighbor[i][index_min] = Neighbor[i][j];
                Neighbor[i][j] = time_min;
            }
        }
        
        if (configt.testing == true)
        {
            for (int i = 0; i < Ntnd; i++)
            {
                cout <<setw(3) << i << "::";
                for (int j = 0; j < Ntnd; j++)
                {
                    cout << setw(3) << Arces[i][j].ed;
                }
                cout<<endl;
                cout <<setw(3) << i << "::";
                for (int j = 0; j < Ntnd; j++)
                {
                    cout << setw(3) << Neighbor[i][j].ed;
                }

                cout<<endl<<endl;
            }
        }
        

        //checking the neighbors
        if (configt.testing == true)
        {
            for (int i = 0; i < Ntnd; i++)
            {
                if (Neighbor[i][0].ed!= -1)
                {
                    cout<<"if (Neighbor[i][0].ed!= -1)"<<endl;
                    exit(333);
                }
                
            }
        }
    
        if (configt.testing == true)
        {
            int Test_cnt = 0;
            for (int i = 0; i < Ntnd; i++)
            for (int j = 0; j < Ntnd; j++)
                if (Arces[i][j].key)
                    Test_cnt++;

            if (Test_cnt!= 0)
            {
                cout<<"Test_cnt!= 0"<<endl;
                exit(1112);
            }
            
        }

        /// ========================================================================================
        /// ========================================================================================
        /// ================================== creating the paths ==================================
        /// ========================================================================================
        /// ========================================================================================

        int **Fpaths = new int*[Nfpath];        // Nfpath number of paths
        bool **Opaths = new bool *[Nfpath];     
        int *Npaths = new int [Nfpath];         // number of nodes on the path
        float *Tpaths = new float[Nfpath];      // time of the path
        float *Cpaths = new float[Nfpath];      // cost of the path
        
        for (int i = 0; i < Nfpath; i++)
        {
            Npaths[i] = 0;
            Tpaths[i] = 0;
            Cpaths[i] = 0;
        }

        int Cnt_arc = 0;
        for (int p = 0; p < Nfpath; p++)
        {
            cout<<"Path ("<< p <<")"<<endl;
            int Tmp_I = rand_int_bet(min_on_path, max_on_path);
            Npaths[p] = Tmp_I;
            Tpaths[p] = 0;
            Cpaths[p] = 0;

            int *Tmp_P_O;       // name of cities on the path
            bool *Tmp_B_O;      // bool the cities if they are selected or not
            float Tmp_C_O = 0;  // cost
            float Tmp_T_O = 0;  // time

            do
            {
                int *Tmp_P = new int [Tmp_I];
                bool *Tmp_B = new bool [Ntnd];

                float Tmp_C = 0;
                float Tmp_T = 0;

                for (int i = 0; i < Ntnd; i++)
                    Tmp_B[i] = false;

                int Cnt = 0;

                // starting point should be 0 
                Tmp_P[Cnt] = 0; // starting point on the path
                Tmp_B[0] = true; //starting point cannot be selected at all
                
                Cnt++;
                int W_Count = 0;
                while (Cnt < Tmp_I - 1) //why not -2, since we are counting from 0 to n-1 then we add the ending point by ourself
                {
                    W_Count++;
                    if (W_Count>10000) // if we cannot find a node to go forward we need to take a step back and then start from a new place
                    {
                        W_Count = 0;
                        int CntX = rand_int_bet(1, Cnt-1);

                        // example if Cnt = 4
                        // 1- 3 2 cnt = 3
                        // 2- 2 1 cnt = 2
                        // 3- 1 0 cnt = 1

                        for (size_t cnt = 0; cnt < CntX; cnt++)
                        {
                            int onpath = Tmp_P[Cnt-1];
                            Tmp_B[onpath] = false;

                            Tmp_T -=  Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].time;
                            Tmp_C -=  Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].cost;

                            Cnt--;
                            if (Cnt < 1)
                            {
                                cout<<"Cnt<1"<<endl;
                                cout<<"even by back tracking we cannot creat the path!!"<<endl;
                                exit(111);
                            }
                        }
                    }
                    
                    //cout<<Cnt<<endl;
                    //int tmp_n = rand_int_bet(1,Nnodes-2); // no start (0) and no finish (Nnodes-1) if the rand is inclusive???
                    int tmp_n = rand_int_bet(1, NNeighbor);
                    tmp_n =  Neighbor[Tmp_P[Cnt-1]][tmp_n].ed;
                    if (tmp_n<=-1)
                    {
                        cout<<"(tmp_n==-1)"<<endl;
                        exit(331);
                    }

                    if (tmp_n >= Ntnd)
                    {
                        cout<<"(tmp_n >= Nnodes || tmp_n <=0)"<<endl;
                        cout<<tmp_n<<endl;
                        exit(45);
                    }
                    
                    
                    if (!Tmp_B[tmp_n])
                    {
                        Tmp_P[Cnt] = tmp_n;
                        Tmp_B[tmp_n]= true;
                        Cnt++;
                        try
                        {
                            Tmp_T +=  Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].time;
                            Tmp_C +=  Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].cost;
                        }
                        catch(const std::exception& e)
                        {
                            std::cerr << e.what() << '\n';
                            exit(323);
                        }
                        
                        

                        if (!Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].key)
                        {
                            Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].key = true;
                            Cnt_arc++;
                        }
                    }
                }
                try
                {
                    Tmp_P[Cnt] = Ntnd-1; // ending point
                    Tmp_B[Ntnd-1] = true;
                    Cnt++;

                    if (!Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].key)
                    {
                        Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].key = true;
                        Cnt_arc++;
                    }
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    cout<<"section 4"<<endl;
                    exit(224);
                }

                try
                {
                    Tmp_T +=  Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].time;
                    Tmp_C +=  Arces[Tmp_P[Cnt-2]][Tmp_P[Cnt-1]].cost;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    cout<<"section 3"<<endl;
                    exit(211);
                }

                //checking the path
                bool Kfind = false; // start with we did not find the 
                
                for (int u = 0; u < p && Kfind == false; u++) // p starts from 0, if we find the path we put it at the (p) location
                {
                    if (Tmp_I == Npaths[u])
                    {
                        bool Ktmp = true;
                        for (int k = 0; k < Tmp_I; k++)
                            if (Tmp_P[k]!=Fpaths[u][k])
                            {
                                Ktmp = false;
                                break;
                            }

                        if (Ktmp)
                            Kfind = true;   
                    }
                }
                
                if (!Kfind)
                {
                    Tmp_P_O = Tmp_P;
                    Tmp_B_O = Tmp_B;
                    Tmp_C_O = Tmp_C;
                    Tmp_T_O = Tmp_T;
                    break;
                }
                else
                {
                    delete [] Tmp_P;
                    delete [] Tmp_B;
                    Tmp_P = nullptr;
                    Tmp_B = nullptr;
                }

            } while (true);
            cout<<"path added!!!"<<endl;
            Fpaths[p] = Tmp_P_O;
            Opaths[p] = Tmp_B_O;
            Tpaths[p] = Tmp_T_O;
            Cpaths[p] = Tmp_C_O;
        }
        
        float max_path= -1;

        for (int i = 0; i < Nfpath; i++)  //time is going to be on the constraint
            if (max_path < Tpaths[i])      // finding the max of the time as the cap
                max_path = Tpaths[i];
        
        
        if(configt.testing)
        {
            int T_cnt = 0;
            for (int i = 0; i < Ntnd; i++)
                for (int j = 0; j < Ntnd; j++)
                    if (Arces[i][j].key)
                        T_cnt++;
            
            if (T_cnt!= Cnt_arc)
            {
                cout<<"T_cnt!= Cnt_arc!!"<<endl;
                exit(1114);
            }
        }
        
        while (Cnt_arc < Narcs)
        {
            
            int pointA = rand_int_bet(0, Ntnd-1);
            int pointB = rand_int_bet(0, Ntnd-1);

            if ((!Arces[pointA][pointB].key)&& (pointA!=pointB))
            {
                Arces[pointA][pointB].key = true;
                Cnt_arc++;
            }
        }

        char name[300];
        sprintf(name, "%s/CSP-%d-%2d-%d-f.txt", address, Ntnd, int(configd.Farcs*100), Instance);

        out.open(name);

        //creating the data
            // number of nodes
            // number of arcs
            // nodes
                // start
                // end
            // arcs
            // weight
            // time
            // constraints

        out << "Nodes:  " << Ntnd << endl;
        out << "Narcs:  " << Narcs << endl;
        out << "Snode:  " << 0 << endl;
        out << "Enode:  " << Ntnd-1 << endl;
        out << "Const:  " << max_path << endl; //which here it is time
        

        int Cnt_test = 0;

        out << setw(5) << "Nb";
        out << setw(5) << "Fr";
        out << setw(5) << "To";
        out << setw(5) << "Ct";
        out << setw(5) << "tm"<<endl<<endl;

        for (int i = 0; i < Ntnd; i++)
        for (int j = 0; j < Ntnd; j++)
        {
            if (Arces[i][j].key)
            {
                out << setw(5) << Cnt_test;
                out << setw(5) << i ;
                out << setw(5) << j ;
                
                std::ios cout_state(nullptr);
                cout_state.copyfmt(out);

                out.setf(ios::fixed);
                out.setf(ios::showpoint);
                out.precision(2);
                
                out << setw(10) << Arces[i][j].cost ;  //obj
                out << setw(10) << Arces[i][j].time <<endl;   //constraint
                
                // cost obj
                // time constraint

                out.copyfmt(cout_state);
                Cnt_test++;
            }
        }
                
        out << endl << endl;

        for (int i = 0; i < Ntnd; i++)
        {
            int nbours=0;
            for (int j = 0; j < Ntnd; j++)
                if (Arces[i][j].key)
                    nbours++;
                

            
            out << setw(4) << i << setw(4)<<nbours;
            for (int j = 0; j < Ntnd; j++)
            {
                if (Arces[i][j].key)
                {
                    out << setw(4) << Arces[i][j].ed;
                }
                
            }
            out<<endl;
        }

        out<<endl;
        out<<endl;
        out<<endl;

        out << Nfpath<<endl<<endl;

        out << setw(4) << "Nb";
        out << setw(8) << "NoP";
        out << setw(8) << "Cost";
        out << setw(8) << "Time"<<endl<<endl;


        for (int p = 0; p < Nfpath; p++)
        {
            out << setw(4) << p ;
            out << setw(8) << Npaths[p] ;

            std::ios cout_state(nullptr);
            cout_state.copyfmt(out);

            out.setf(ios::fixed);
            out.setf(ios::showpoint);
            out.precision(2);
            
        
            out << setw(12) << Cpaths[p] ;
            out << setw(12) << Tpaths[p] ;

            out.copyfmt(cout_state);
            
            for (int j = 0; j < Npaths[p]; j++)
            {
                out << setw(4) << Fpaths[p][j] ;
            }
            out<<endl;
        }

        out<<endl;
        out<<endl;
        out<<endl;

        for (int n = 0; n < Ntnd; n++)
        {
            out << setw(4) << n ;
            std::ios cout_state(nullptr);
            cout_state.copyfmt(out);

            out.setf(ios::fixed);
            out.setf(ios::showpoint);
            out.precision(2);
            
            out << setw(8) << Nodes[n].x ;
            out << setw(8) << Nodes[n].y ;

            out.copyfmt(cout_state);
       
            out<<endl;
        }
        out.close();

        //================================================
        //================================================
        //========= releasing the memory =================
        //================================================
        //================================================

        delete [] Nodes;
        Nodes = nullptr;

        for (int i = 0; i < Ntnd; i++)
        {
            delete[] Neighbor[i];
            delete[] Arces[i];
        }
        delete[] Neighbor;
        Neighbor = nullptr;
        delete[] Arces;
        Arces = nullptr;

        delete[] Npaths;
        delete[] Tpaths;
        delete[] Cpaths;

        Npaths = nullptr;
        Tpaths = nullptr;
        Cpaths = nullptr;

        for (int i = 0; i < Nfpath; i++)
        {
            delete[] Fpaths[i];
            delete[] Opaths[i];
        }
        delete[] Fpaths;
        Fpaths = nullptr;
        delete[] Opaths;
        Opaths = nullptr;
    }//for instances
}

#endif