#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include "Result.h"
#include "Loaded_List.h"
#include "Database_BST.h"
#include <fstream>

class Manager
{
private:
    std::ofstream fout;
    std::ifstream fin;
    Loaded_List* list;
    Database_BST* bst;
public:
    std::string Image;
    const char* RESULT_LOG_PATH = "log.txt";
    Manager();
    ~Manager();
    void Run(const char* filepath);
    void PrintError(Result result);
private:
    Result Load(const char* filepath,Loaded_List* list);
    Result Add(const char* Dir,const char* filepath,Loaded_List* list);
    Result Modify(const char* Dir,const char* filename, std::string num);
    Result Move();
    void PrintAdd();
    void PrintModify();
    Result Move(Loaded_List* list);
    void PrintMove();
    void PrintInorder(Database_BST_Node* node);
    Result SEARCH(std::string ptr2);
    Result Print(Database_BST* bst);
    Result Select(std::string ptr2);
    void PrintSelect();
    void PrintEdit();
    void PrintExit();
};

#endif
