#ifndef _exitence_c
#define _exitence_c

#include<fstream>
#include"exitence.h"

//using std::filesystem::is_directory;
//using std::filesystem::exists;


bool exists (const char* name)
{
    if (FILE *file = fopen(name, "r")) 
    {
        fclose(file);
        return true;
    } 
    else 
    {
        return false;
    }   
}


#endif