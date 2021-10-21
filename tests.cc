#ifndef _test_c
#define _test_c

#include <iostream>
#include <lemon/list_graph.h>
#include <cassert>

#include "tests.h"

#include "mathmatics.h"
#include "config_t.h"

using namespace std;
using namespace lemon;


void testing_Declaration(sections sec, string tmp = "")
{
    if (sec==First)
    {
        cout<<"======================================="<<endl;
        cout<<" function name: " << tmp << endl;
        cout<<"---------------------------------------"<<endl;
    }
    else if(sec==Second)
    {
        cout<<"---------------------------------------"<<endl;
        cout<<"Done"<<endl;
        cout<<"======================================="<<endl<<endl<<endl<<endl;
    }    
}


void testing_config(config_t *config)
{
    testing_Declaration(First, "Configurations");
    try
    {
        if(config->threads<=0)
            throw string("Threads can not get negative values!");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    testing_Declaration(Second);
}

void testing_Nodes()
{
    testing_Declaration(First, "Nodes");

    ListDigraph g;
    ListDigraph::Node u = g.addNode();
    ListDigraph::Node v = g.addNode();
    ListDigraph::Arc  a = g.addArc(u, v);

    cout << "Hello World! This is LEMON library here." << endl;
    cout << "We have a directed graph with " << countNodes(g) << " nodes "
        << "and " << countArcs(g) << " arc." << endl;
    
    testing_Declaration(Second, "Nodes");
}

void testing_Factorial()
{
    testing_Declaration(First ,"Factorial");
    try
    {
        if( Factorial(7)!= 5040)
            throw string("Something is wrong in Factorial function v1.");
        if( Factorial(10)!= 3628800)
            throw string("Something is wrong in Factorial function v2.");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    testing_Declaration(Second);
}
void testing_Permutation()
{
    testing_Declaration(First ,"Permutation");
    try
    {
        if (Permutation(10,4)!=5040)
            throw string("Someting is wrong with Permutation function v1.");
        if (Permutation(20,4)!= 116280)
            throw string("Someting is wrong with Permutation function v2 and the value is  "+ to_string(Permutation(20,4)));
        if (Permutation(100,2)!= 990)
            throw string("Someting is wrong with Permutation function v2 and the value is  "+ to_string(Permutation(100,2)));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const std::string& e)
    {
        std::cout<<e<<endl;
    }
    testing_Declaration(Second);
}

void testing_Combination()
{
    testing_Declaration(First, "Combination");
    try
    {
        if (Combination(10,4)!=210)
            throw string("Someting is wrong with Combination function v1.");
        if (Combination(20,4)!= 4845)
            throw string("Someting is wrong with Combination function v2 and the value is  " + to_string(Combination(20,4)));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const std::string& e)
    {
        std::cout<<e<<endl;
    }
    testing_Declaration(Second);
}

void testing(sections Section, config_t *config)
{
    switch (Section)
    {
    case First:
        testing_config(config);
        break;
    case Second:
        
        testing_Nodes();
        testing_Factorial();
        testing_Permutation();
        testing_Combination();

        break;

    case Third:

        
        break;
    
    default:
        break;
    }

}


#endif