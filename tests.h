#ifndef _test_h
#define _test_h

#include "config_t.h"
enum sections{First, Second, Third};

void testing_Declaration(sections, std::string) ;

void testing(sections, config_t *);

void testing_Nodes();
void testing_Permutation();
void testing_Combination();
void testing_Factorial();


#endif