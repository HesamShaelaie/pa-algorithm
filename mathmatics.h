#ifndef _mathmatics_h
#define _mathmatics_h
#include"variables.h"

long long Factorial(int);

long long Combination(int, int);
long long Permutation(int, int);

int rand_int_bet(int min, int max);
float rand_float_bet(float min, float max, int precision);
float distance(nodeinfo, nodeinfo);

#endif