#ifndef _generating_data_c
#define _generating_data_c

#include "variables.h"
#include "generating_data.h"
#include "config_t.h"
#include "mathmatics.h"
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
//using std::filesystem::is_directory;
//using std::filesystem::exists;



bool exists (const char* name)
{
    if (FILE *file = fopen(name, "r")) 
    {
        fclose(file);
        return true;
    } 
    else 
    {
        return false;
    }   
}

int rand_int_bet(int min, int max)
{
    int intmin, intmax;
    if (min> max)
    {
        intmin = max;
        intmax = min;
    }
    else
    {
        intmin = min;
        intmax = max;
    }
    
    
    int tmp = intmin + (rand()%(intmax-intmin+1));
    return tmp;
}

float rand_float_bet(float min, float max, int precision)
{
    float floatmin, floatmax;
    if (min> max)
    {
        floatmin = max;
        floatmax = min;
    }
    else
    {
        floatmin = min;
        floatmax = max;
    }
    
    
    
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
    float tmp = floatmin + r*(floatmax-floatmin);
    tmp = int(tmp * pow(10,precision));

    tmp = tmp/pow(10,precision);
    return tmp;
}



long long index_creator(int Nnodes, int from, int to)
{
    int tens = ceil(log10(Nnodes))+1;

    long long tmp = (from * pow(10,tens)) + to;

    return tmp;
}


void gen_data(config_t config)
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
        sprintf(name, "%s/CSP-%d-%2d-%d", tmp, Nnodes,int(Farcs*100),Instance);

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
            out << setw(10) << myPair.second->time<<endl;
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

#endif