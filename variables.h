#ifndef _variabels_h
#define _variabels_h

struct arcinfo
{
    int st;
    int ed;
    float cost;
    float time;
    arcinfo()
    {
        st = -1;
        ed = -1;
        cost = 0;
        time = 0;
    } 
};


#endif