#ifndef _generating_data_c
#define _generating_data_c

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

long long index_creator(int, int)
{

    
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

        out << Nnodes << endl;
        out << Narcs << endl;
        
        int startpoint;
        int pointA;
        int pointB;

        do
        {
            pointA = rand_int_bet(0,Nnodes-1);
            pointB = rand_int_bet(0,Nnodes-1);
            /* code */
        } while (pointA==pointB);

        out << pointA << endl;
        out << pointB << endl;
        
        long long index;






        






        out.close();
        

    }
    





}

#endif