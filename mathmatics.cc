#ifndef _mathmatics_c
#define _mathmatics_c

#include"mathmatics.h"
#include<iostream>
#include<math.h>
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


float distance(nodeinfo const &A, nodeinfo const &B)
{
    return sqrt(pow((A.x-B.x),2) + pow((A.y-B.y),2));
}


#endif
