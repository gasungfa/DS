#include "Manager.h"
#include<iostream>
int main()
{
    const char* commandFilepath = "./command.txt";//command file is this
    Manager m;//declare manager object
    m.Run(commandFilepath);//object's implement with command file
    return 0;
}