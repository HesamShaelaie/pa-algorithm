#ifndef _variabels_h
#define _variabels_h

struct arcinfo
{
    int st;
    int ed;
    float cost;
    float weight;
    arcinfo()
    {
        st = -1;
        ed = -1;
        cost = 0;
        weight = 0;

    } 
};




#endif