#ifndef _mathmatics_c
#define _mathmatics_c

#include"mathmatics.h"
#include<iostream>

using namespace std;


long long Factorial(int x)
{
    long long output = 1;
    
    for (int i = x; i > 0; i--)
    {
        output = output * i;
    }

    return output;
}

long long FactorialUntil(int x, int y)
{
    //Y is not included in process. 
    if (y>x)
        throw string("wrong input inside the FactorialUntil");
    
    long long output = x;
    
    for (int i = x-1; i > y; i--)
    {
        output = output * i;
    }

    return output;
}


long long Combination(int items, int sel)
{
    int tmp = items - sel;
    if (tmp>sel)
    {
        long long n_s = FactorialUntil(items, tmp);
        long long r = Factorial(sel);
        return n_s/r;
    }
    else
    {
        long long n_s = FactorialUntil(items, sel);
        long long r = Factorial(sel);
        return n_s/r;
    }
    
    
    long long n = Factorial(items);
    long long r = Factorial(sel);
    
    long long n_s = Factorial(items-sel);
    return n/(r*n_s);
}


long long Permutation(int items, int sel)
{
    return FactorialUntil(items, (items-sel));
}

#endif
