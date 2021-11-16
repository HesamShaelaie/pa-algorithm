#ifndef _pa_algorithm_c
#define _pa_algorithm_c

#include "pa_algorithm.h"

// Time is 0
// Cost is 1

// Constraint is on time



void Solve_PA(InstanceInfo *Info)
{
    int st = Info->start;
    traverseinfo * start = new traverseinfo (Info->Nnodes, &Info->nodes[st]);
    start->SltN++;
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
        //check start
        // if pruned substitude
        // else continue start

        //prune rule one
        if (start->lable >  start->Node->lable)
        {
            tmp = start->next;
            start->deallocate();
            start = tmp;
            continue;
        }
        
        //prune rule two
        if (start->obj > Upper)
        {
            tmp = start->next;
            start->deallocate();
            start = tmp;
            continue;
        }


        //prune rule three
        fr = start->Node->index;
        if (start->lable.time > Info->Dijk_f[Time][fr])
        {
            tmp = start->next;
            start->deallocate();
            start = tmp;
            continue;
        }


        if ( start->lable <  start->Node->lable)
            start->Node->lable = start->lable;
        

        tmpnode = start -> Node;
        keyfirst = false;

        for (int x = 0; x < tmpnode->Nnbr ; x++)
        {
            if (!start->SltB[x])
            {
                if (!keyfirst)
                {
                    keyfirst = true;
                    saveindex = x;
                    /* code */
                }else
                {
                    to = tmpnode->nbr[x];
                    tmparc = Info->FindEdgeM(fr,to);
                    tmp = new traverseinfo(Info->Nnodes, &Info->nodes[to]);

                    tmp->lable = start->lable;
                    tmp->lable += tmparc;
                    tmp->obj = start->obj + tmparc->cost;
                    tmp->SltN = start->SltN;
                    for (int y = 0; y < tmp->SltN; y++)
                        tmp->SltL[y] = start->SltL[y];
                    tmp->SltN++;
                    tmp->SltL[tmp->SltN] = to;

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
            start->lable += tmparc;
            start->obj = start->obj + tmparc->cost;  
            start->SltN++;
            start->SltL[start->SltN] = to;
            start->SltL[to] = true;
        }
    }
    
}

#endif