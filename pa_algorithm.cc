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
    traverseinfo * tmp;
    float Upper = std::numeric_limits<float>::max();
    int n;

    while (start)
    {
        //check start
        // if pruned substitude
        // else continue start

        if (start->lable >  start->Node->lable)
        {
            // delete the start and go next
            //continue
        }
        
        if (start->obj > Upper)
        {
            // delete the start and go next
            //continue
        }
        n = start->Node->index;
        if (start->lable.time > Info->Dijk_f[Time][n])
        {
            // delete the start and go next
            //continue
        }
        
        



        if ( start->lable <  start->Node->lable)
        {
            start->Node->lable = start->lable;
        }
        
        
        

        for (int n = 0; n < start->SltN ; n++)
        {
            /* code */
        }
        
         

    }
    

    

    
}

#endif