#pragma once

#include<string>
#include<iostream>

class Loaded_List_Node{
private:
    Loaded_List_Node* next;//next pointer
    Loaded_List_Node* down;//down pointer
    std::string f_name;//file name
    std::string dir;//directory
    std::string u_num;//unique num
public:
    Loaded_List_Node(){//constructor
        next = nullptr;
        down = nullptr;
    }
    std::string GetFileName();
    std::string GetDir();
    std::string GetNum();
    Loaded_List_Node GetHead();
    void SetFname(std::string F);
    void SetDir(std::string D);
    void SetNum(std::string N);
    Loaded_List_Node* GetNext(){return this->next;}
    void SetNext(Loaded_List_Node* node){this->next = node;}
    Loaded_List_Node* GetDown(){return this->down;}
    void SetDown(Loaded_List_Node* node){this->down = node;}
};