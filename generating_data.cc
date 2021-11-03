#ifndef _generating_data_c
#define _generating_data_c

#include "variables.h"
#include "generating_data.h"
#include "config_t.h"
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


void gen_data_without_feasibility(config_t config)
{
    char tmp[256];
    getcwd(tmp,256);
    strcat(tmp, "/instances");

    
    if (!exists(tmp))
        mkdir(tmp,0777); 
    
    
    //Number of nodes
    //Number of arcs
    //Number of instances
    //Creating the name of it
    int Ninstance = 10;
    int Nnodes = 100;
    float Farcs = 0.3; //with respect to complete graphs
    int Narcs = int(Permutation(Nnodes, 2)*Farcs);
    float Wmin, Wmax, Tmin, Tmax;

    Wmin = 1;
    Wmax = 10;

    Tmin = 10;
    Tmax = 20;
    
    ofstream out_G;

    char Gname[300];
    sprintf(Gname, "%s/CSP-info.txt", tmp);
    out_G.open(Gname, std::ios_base::app);
    
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    out_G << " ---------------------------------------------------------- "<< endl;
    out_G << "Time:   " << std::ctime(&end_time);
    out_G << "Ninstance:    " << Ninstance <<endl;
    out_G << "Nnode:" << Nnodes <<endl;
    out_G << "Farcs: " << Farcs <<endl;
    out_G << "Narcs: " << Narcs <<endl;
    
    out_G << "Wmin: " << Wmin <<endl;
    out_G << "Wmax: " << Wmax <<endl;

    out_G << "Tmin: " << Tmin <<endl;
    out_G << "Tmax: " << Tmax <<endl;
    out_G.close();

    
    ofstream out;
    for (int Instance = 0; Instance < Ninstance; Instance++)
    {
        //creating the name of the file
        //CSP-Number of nodes-fraction-instance.txt
        char name[300];
        sprintf(name, "%s/CSP-%d-%2d-%d.txt", tmp, Nnodes, int(Farcs*100), Instance);

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

        out << "Nodes:  " << Nnodes << endl;
        out << "Narcs:  " << Narcs << endl;
        
        int startpoint;
        int pointA;
        int pointB;

        do
        {
            pointA = rand_int_bet(0,Nnodes-1);
            pointB = rand_int_bet(0,Nnodes-1);
            /* code */
        } while (pointA==pointB);

        out << "Snode:  " << pointA << endl;
        out << "Enode:  " << pointB << endl;
        
        
        long long index;
        map<long long, arcinfo*> Dic;


        int **Mnbr = new int *[Nnodes];
        bool **Mchk = new bool *[Nnodes];
        for (int i = 0; i < Nnodes; i++)
        {
            Mnbr[i]= new int[Nnodes+1];
            Mchk[i] = new bool [Nnodes];
            for (int j = 0; j < Nnodes+1; j++)
            {
                Mnbr[i][j]=0;
                Mchk[i][j] = false;
            }

        }

        int Cnt_arcs = 0;
        
        while (Cnt_arcs < Narcs)
        {
            
            pointA = rand_int_bet(0,Nnodes-1);
            pointB = rand_int_bet(0,Nnodes-1);
        
            index = index_creator(Nnodes, pointA, pointB);

            if (Dic.find(index) == Dic.end()) 
            {
                
                arcinfo *tmp_arc = new arcinfo;
                tmp_arc->st = pointA;
                tmp_arc->ed = pointB;
                tmp_arc->cost = rand_float_bet(Tmin,Tmax, 2);
                tmp_arc->time = rand_float_bet(Wmin, Wmax, 2);
                Dic[index] = tmp_arc;
                Cnt_arcs++;
                cout<<Cnt_arcs<<endl;
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

        for (int i = 0; i < Nnodes; i++)
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
        

        
        for (int i = 0; i < Nnodes; i++)
        {
            delete[] Mnbr[i];
            delete[] Mchk[i];
        }
        delete[] Mnbr;
        delete[] Mchk;
    }
}


void gen_data_with_feasibility(config_t config)
{
    cout<<"gen_data_with_feasibility!!!"<<endl;
    // 1- get the address and create instance folder
    // 2- get the general informantion
        // coordination of the nodes
        // decision on the weights and costs

    // 3- decide on number of arcs
    // 4- decide on number of feasible paths
    // 5- add arcs as long as you reach to the number of arcs


    char tmp[256];
    getcwd(tmp,256); // getting the folder of the codes
    strcat(tmp, "/instances"); // add the instance to the address


    // checking if the address exists
    if (!exists(tmp))
        mkdir(tmp,0777); // if not make the folder
    
    int Ninstance = 10;
    int Nnodes = 100;
    float Farcs = 0.3; //with respect to complete graphs

    int Narcs = int(Permutation(Nnodes, 2)*Farcs);

    float Ffeasiblepath = 0.5; // number of feasible path with respect to number of nodes in the graph
    int Nfeasiblepath = int(Ffeasiblepath * Nnodes);

    float Cor_min = 0;             //min over coordination of the nodes
    float Cor_max = 1000;          //max over coordination of the nodes

    float Cchance = 0.5;        // if the chance is over the 0.5 then increase by tmore
    float Cless = 0.8;
    float Cmore = 1.2;

    int min_on_path = int(Nnodes*0.2);
    int max_on_path = int(Nnodes*0.6);
    float FNeighbor = 0.3;
    int   NNeighbor = int(FNeighbor*Nnodes);

    ofstream out_G;

    char Gname[300];
    sprintf(Gname, "%s/CSP-info.txt", tmp);
    out_G.open(Gname, std::ios_base::app);// append to the file
    
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    out_G << " ---------------------------------------------------------- "<< endl;
    out_G << "Time:   " << std::ctime(&end_time);
    out_G << "Ninstance:    " << Ninstance <<endl;
    out_G << "Nnode:    " << Nnodes <<endl;
    out_G << "Farcs:    " << Farcs <<endl;
    out_G << "Narcs:    " << Narcs <<endl;

    out_G << "Cordination_min: " << Cor_min <<endl;
    out_G << "Cordination_max: " << Cor_max <<endl;

    out_G << "Tchance: " << Cchance <<endl;
    out_G << "Tless: " << Cless <<endl;
    out_G << "Tmore: " << Cmore <<endl;

    out_G << "min_on_path: " << min_on_path <<endl;
    out_G << "max_on_path: " << max_on_path <<endl;

    out_G << "RNeighbor: " << NNeighbor <<endl;
    out_G << "Ffpath: " << Ffeasiblepath <<endl;
    out_G << "Nfpath: " << Nfeasiblepath <<endl;
    out_G.close();

    //==============================================================================    



    ofstream out;
    for (int Instance = 0; Instance < Ninstance; Instance++)
    {
        //Creating the name of the file
        //CSP-Number of nodes-fraction-instance.txt
        cout<<"starting instance (" <<Instance << ")!!"<<endl;

        nodeinfo *Nodes = new nodeinfo[Nnodes];
        for (int n = 1; n < Nnodes-1; n++)
        {
            Nodes[n].x = rand_float_bet(Cor_min,Cor_max,2);
            Nodes[n].y = rand_float_bet(Cor_min,Cor_max,2);
        }

        Nodes[0].x = Cor_min;
        Nodes[0].y = Cor_min;

        Nodes[Nnodes-1].x = Cor_max;
        Nodes[Nnodes-1].y = Cor_max;


        arcinfo **Neighbor = new arcinfo *[Nnodes];
        arcinfo **Arces = new arcinfo *[Nnodes];
        for (int i = 0; i < Nnodes; i++)
        {
            Neighbor[i] = new arcinfo[Nnodes];
            Arces[i] = new arcinfo [Nnodes];
        }

        for (int i = 0; i < Nnodes; i++)
            for (int j = i+1; j < Nnodes; j++)
            {
                Arces[i][j].time = distance(Nodes[i],Nodes[j]);
                
                Arces[i][j].st=i;
                Arces[i][j].ed=j;
                if (rand_int_bet(0,10)>5)
                    Arces[i][j].cost = Arces[i][j].time * Cmore;
                else
                    Arces[i][j].cost = Arces[i][j].time * Cless;
                
                Arces[j][i] = Arces[i][j];
                Arces[j][i].st = j;
                Arces[j][i].ed = i;
            }

        
        for (int i = 0; i < Nnodes; i++)
        for (int j = 0; j < Nnodes; j++)
            Neighbor[i][j] = Arces[i][j];
        

        
        
        // sorting the neighbors
        for (int i = 0; i < Nnodes; i++)
        {
            arcinfo time_min; 
            int index_min;
            for (int j = 0; j < Nnodes-1; j++)
            {
                time_min = Neighbor[i][j];
                index_min = j;
                
                for (int k = j+1; k < Nnodes; k++)
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
        
        if (config.testing == true)
        {
            for (int i = 0; i < Nnodes; i++)
            {
                cout <<setw(3) << i << "::";
                for (int j = 0; j < Nnodes; j++)
                {
                    cout << setw(3) << Arces[i][j].ed;
                }
                cout<<endl;
                cout <<setw(3) << i << "::";
                for (int j = 0; j < Nnodes; j++)
                {
                    cout << setw(3) << Neighbor[i][j].ed;
                }

                cout<<endl<<endl;
            }
        }
        
        


        //checking the neighbors
        if (config.testing == true)
        {
            for (int i = 0; i < Nnodes; i++)
            {
                if (Neighbor[i][0].ed!= -1)
                {
                    cout<<"if (Neighbor[i][0].ed!= -1)"<<endl;
                    exit(333);
                }
                
            }
        }
        
        /*
        for (int i = 0; i < Nfeasiblepath; i++)
        {
            Fpaths[i] = new int [Nnodes];
            Opaths[i] = new int [Nnodes];
            for (int j = 0; j < Nnodes; j++)
            {
                Fpaths[i][j] = -1;
                Opaths[i][j] = false;
            }
        }
        */
       
        int **Fpaths = new int*[Nfeasiblepath];
        bool **Opaths = new bool *[Nfeasiblepath];
        int *Npaths = new int [Nfeasiblepath];
        float *Tpaths = new float[Nfeasiblepath];
        float *Cpaths = new float[Nfeasiblepath];
        
        for (int i = 0; i < Nfeasiblepath; i++)
        {
            Npaths[i] = 0;
            Tpaths[i] = 0;
            Cpaths[i] = 0;
        }

        int Cnt_arc = 0;

        for (int p = 0; p < Nfeasiblepath; p++)
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
                bool *Tmp_B = new bool [Nnodes];

                float Tmp_C = 0;
                float Tmp_T = 0;

                for (int i = 0; i < Nnodes; i++)
                    Tmp_B[i] = false;

                int Cnt = 0;

                // starting point should be 0 
                Tmp_P[Cnt] = 0; // starting point on the path
                Tmp_B[0] = true; //starting point cannot be selected at all
                
                Cnt++;

                while (Cnt < Tmp_I - 1) //why not -2, since we are counting from 0 to n-1 then we add the ending point by ourself
                {
                    cout<<Cnt<<endl;
                    //int tmp_n = rand_int_bet(1,Nnodes-2); // no start (0) and no finish (Nnodes-1) if the rand is inclusive???
                    int tmp_n = rand_int_bet(1, NNeighbor);
                    tmp_n =  Neighbor[Tmp_P[Cnt-1]][tmp_n].ed;
                    if (tmp_n<=-1)
                    {
                        cout<<"(tmp_n==-1)"<<endl;
                        exit(331);
                    }

                    if (tmp_n >= Nnodes)
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
                            Tmp_T +=  Arces[Tmp_P[Cnt-2],Tmp_P[Cnt-1]]->time;
                            Tmp_C +=  Arces[Tmp_P[Cnt-2],Tmp_P[Cnt-1]]->cost;
                        }
                        catch(const std::exception& e)
                        {
                            std::cerr << e.what() << '\n';
                            exit(323);
                        }
                        
                        

                        if (!Arces[Tmp_P[Cnt-2],Tmp_P[Cnt-1]]->key)
                        {
                            Arces[Tmp_P[Cnt-2],Tmp_P[Cnt-1]]->key = true;
                            Cnt_arc++;
                        }
                    }
                }
                try
                {
                    Tmp_P[Cnt] = Nnodes-1; // ending point
                    Tmp_B[Nnodes-1] = true;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    cout<<"section 4"<<endl;
                    exit(224);
                }
                
                

                Cnt++;
                try
                {
                    Tmp_T +=  Arces[Tmp_P[Cnt-2],Tmp_P[Cnt-1]]->time;
                    Tmp_C +=  Arces[Tmp_P[Cnt-2],Tmp_P[Cnt-1]]->cost;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    cout<<"section 3"<<endl;
                    exit(211);
                }

                //checking the path

                Tmp_P_O = Tmp_P;
                Tmp_B_O = Tmp_B;
                Tmp_C_O = Tmp_C;
                Tmp_T_O = Tmp_T;
            } while (false);

            Fpaths[p] = Tmp_P_O;
            Opaths[p] = Tmp_B_O;
            Tpaths[p] = Tmp_T_O;
            Cpaths[p] = Tmp_C_O;
        }
        
        float max_path= -1;

        for (int i = 0; i < Nfeasiblepath; i++)
            if (max_path < Tpaths[i])
                max_path = Tpaths[i];
        
        
        while (Cnt_arc < Narcs)
        {
            
            int pointA = rand_int_bet(0, Nnodes-1);
            int pointB = rand_int_bet(0, Nnodes-1);
        
            if (!Arces[pointA,pointB]->key)
            {
                Arces[pointA,pointB]->key = true;
                Cnt_arc++;
            }
        }

        char name[300];
        sprintf(name, "%s/CSP-%d-%2d-%d-f.txt", tmp, Nnodes, int(Farcs*100), Instance);

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

        out << "Nodes:  " << Nnodes << endl;
        out << "Narcs:  " << Narcs << endl;
        
        int startpoint;
        int pointA;
        int pointB;


        out << "Snode:  " << 0 << endl;
        out << "Enode:  " << Nnodes-1 << endl;
        
        

        int Cnt_test = 0;
        for (int i = 0; i < Nnodes; i++)
        for (int j = 0; j < Nnodes; j++)
        {
            if (Arces[i][j].key)
            {
                out << setw(5) << Cnt_test;
                out << setw(5) << i ;
                out << setw(5) << j ;
                out << setw(10) << Arces[i][j].cost ;
                out << setw(10) << Arces[i][j].time <<endl;
                Cnt_test++;
            }
        }
                
        out << endl << endl;

        for (int i = 0; i < Nnodes; i++)
        {
            bool find_test = false;
            for (int j = 0; j < Nnodes; j++)
            {
                if (Arces[i][j].key)
                {
                    find_test = true;
                }
                
            }

            if (find_test)
            {
                out << setw(4) << i;
                for (int j = 0; j < Nnodes; j++)
                {
                    if (Arces[i][j].key)
                    {
                        out << setw(4) << Arces[i][j].ed;
                    }
                    
                }
                out<<endl;
            }
        }

        out<<endl;
        out<<endl;
        out<<endl;

        for (int p = 0; p < Nfeasiblepath; p++)
        {
            out << setw(4) << p ;
            out << setw(4) << Npaths[p] ;
            out << setw(4) << Tpaths[p] ;
            out << setw(4) << Cpaths[p] ;
            out << setw(4) << ":" ;

            for (int j = 0; j < Npaths[p]; j++)
            {
                out << setw(4) << Fpaths[p][j] ;
            }
            
        }
        out.close();
    }
}

#endif