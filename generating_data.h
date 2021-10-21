#ifndef _generating_data_h
#define _generating_data_h

#include "config_t.h"

bool exists_test1 (const char*);
void gen_data(config_t config);

int rand_int_bet(int, int); //inclusive

float rand_float_bet(float, float, int);

long long index_creator(int Nnodes, int from, int to);


#endif