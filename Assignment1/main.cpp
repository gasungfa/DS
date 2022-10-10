#include "Manager.h"
#include<iostream>
int main()
{
    const char* commandFilepath = "./command.txt";
    Manager m;
    m.Run(commandFilepath);
    return 0;
}