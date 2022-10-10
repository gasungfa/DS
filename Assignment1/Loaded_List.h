#pragma once
#include "Loaded_List_Node.h"
#include<iostream>
#include<string>

class Loaded_List{
private:
    Loaded_List_Node* head = nullptr;
public:
    Loaded_List(){head = nullptr;}
    bool IsEmpty();
    Loaded_List_Node* FindDel(Loaded_List_Node* CurNode);
    Loaded_List_Node* GetEnd();
    Loaded_List_Node* GetHead();
    Loaded_List_Node* Load_Delete();
    Loaded_List_Node* Load(std::string num, std::string name);
    Loaded_List_Node* Add(std::string num, std::string name, const char* dir);
    Loaded_List_Node* Modify(const char* Dir,const char* filename, std::string num);
    void Print_Loaded_List();
    void SetHead(Loaded_List_Node* node){this->head = node;}
};