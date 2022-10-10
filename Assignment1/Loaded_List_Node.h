#pragma once

#include<string>
#include<iostream>

class Loaded_List_Node{
private:
    Loaded_List_Node* next;
    Loaded_List_Node* down;
    std::string f_name;
    std::string dir;
    std::string u_num;
public:
    Loaded_List_Node(){
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