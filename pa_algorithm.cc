#ifndef _pa_algorithm_c
#define _pa_algorithm_c

#include "pa_algorithm.h"

// Time is 0
// Cost is 1

// Constraint is on time



void Solve_PA(InstanceInfo *Info)
{
    int st = Info->start;
    int fn = Info->finish;
    traverseinfo * start = new traverseinfo (Info->Nnodes, &Info->nodes[st]);
    start->SltN++;
    start->allocate();
    start->SltB[st] = true;
    start->SltL[0]  = st;
    traverseinfo * tmp;
    float Upper = std::numeric_limits<float>::max();
    
    nodeinfo *tmpnode;
    arcinfo *tmparc;
    int fr;
    int to;
    bool keyfirst;
    int saveindex;

    while (start)
    {
        if ( start->lable <  start->Node->lable)
            start->Node->lable = start->lable;
        
        
        if (start->Node->index==fn)
        {
            if(start->obj<Upper)
            {
               Upper = start->obj;
               Info->sol_obj = start->obj;
               Info->sol_n = start->SltN;
               for (int k = 0; k < start->SltN; k++)
                   Info->sol_path[k] = start->SltL[k];
            }

            tmp = start->next;
            start->deallocate();
            delete start;
            start = tmp;
            continue;
        }
        
        //prune rule one
        if (start->lable >  start->Node->lable)
        {
            tmp = start->next;
            start->deallocate();
            delete start;
            start = tmp;
            continue;
        }
        
        //prune rule two
        if (start->obj > Upper)
        {
            tmp = start->next;
            start->deallocate();
            delete start;
            start = tmp;
            continue;
        }


        //prune rule three
        fr = start->Node->index;
        if ((start->lable.time + Info->Dijk_f[Time][fr]) > Info->constraint)
        {
            tmp = start->next;
            start->deallocate();
            delete start;
            start = tmp;
            continue;
        }

        tmpnode = start -> Node;
        keyfirst = false;

        for (int x = 0; x < tmpnode->Nnbr ; x++)
        {
            to = tmpnode->nbr[x]; 
            if (!start->SltB[to])
            {
                if (!keyfirst)
                {
                    keyfirst = true;
                    saveindex = x;
                    /* code */
                }else
                {
                    tmparc = Info->FindEdgeM(fr,to);
                    tmp = new traverseinfo(Info->Nnodes, &Info->nodes[to]);
                    tmp->allocate();
                    tmp->lable = start->lable;
                    tmp->lable += tmparc;
                    tmp->obj = start->obj + tmparc->cost;
                    tmp->SltN = start->SltN;
                    for (int y = 0; y < tmp->SltN; y++)
                        tmp->SltL[y] = start->SltL[y];
                    
                    tmp->SltL[tmp->SltN] = to;
                    tmp->SltN++;

                    for (int y = 0; y < start->Nnodes; y++)
                        tmp->SltB[y] = start->SltB[y];

                    tmp->SltL[to] = true;
                    tmp->next = start->next;
                    start->next = tmp;
                }
            }
        }

        if (keyfirst)
        {
            to = tmpnode->nbr[saveindex];
            tmparc = Info->FindEdgeM(fr,to);
            start->Node = &Info->nodes[to];
            start->lable += tmparc;
            start->obj = start->obj + tmparc->cost;  
            
            start->SltL[start->SltN] = to;
            start->SltN++;
            
            start->SltL[to] = true;
        }
    }
}

#endif