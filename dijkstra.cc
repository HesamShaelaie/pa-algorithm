#ifndef _dijkstra_c
#define _dijkstra_c

#include"variables.h"

int minDistance(int Nnodes, float dist[], bool sptSet[])
{
   
    // Initialize min value
    float min = std::numeric_limits<float>::max();
    int min_index;
 
    for (int v = 0; v < Nnodes; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

void Dijkstra(InstanceInfo *Info)
{
    Info->all_dijk();
    
    bool *Dij_S[2];
    float *Dij_f[2];
    
    Dij_S[0] = Info->Dijk_S[0]; // 0 -> time
    Dij_S[1] = Info->Dijk_S[1]; // 1 -> weight

    Dij_f[0] = Info->Dijk_f[0];
    Dij_f[1] = Info->Dijk_f[1];

    int u[2];

    int st = Info->finish;
    Dij_f[0][st] = 0;
    Dij_f[1][st] = 0;
    
    bool Keys[2];
    arcinfo * tmparc;

    for (int count = 0; count < (Info->Nnodes - 1); count++) 
    {
        // number of constraints
        u[0] = minDistance(Info->Nnodes, Dij_f[0], Dij_S[0]);
        u[1] = minDistance(Info->Nnodes, Dij_f[1], Dij_S[1]);

        Dij_S[0][u[0]] = true;
        Dij_S[1][u[1]] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < Info->Nnodes; v++)
        {

            Keys[0] = !Dij_S[0][v];
            Keys[1] = !Dij_S[1][v];


            if(Keys[0] && Dij_f[0][u[0]]<std::numeric_limits<float>::max())
                Keys[0] = true;
            else
                Keys[0] = false;


            if(Keys[1] && Dij_f[1][u[1]]<std::numeric_limits<float>::max())
                Keys[1] = true;
            else
                Keys[1] = false;


            tmparc = Info->FindEdgeM(v,u[0]);
            if(Keys[0] && ((Dij_f[0][u[0]] + tmparc->time) < (Dij_f[0][v])))
                Dij_f[0][v] = (Dij_f[0][u[0]] + tmparc->time);


            tmparc = Info->FindEdgeM(v,u[1]);
            if(Keys[1] && ((Dij_f[1][u[1]] + tmparc->cost) < (Dij_f[1][v])))
                Dij_f[1][v] = (Dij_f[1][u[1]] + tmparc->cost);
        }
    }
}

#endif