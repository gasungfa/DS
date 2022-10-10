#include "Loaded_List_Node.h"
#include<string>

std::string Loaded_List_Node:: GetFileName(){
    return f_name;
}
std::string Loaded_List_Node::GetDir(){
    return dir;
}
std::string Loaded_List_Node::GetNum(){
    return u_num;
}
void Loaded_List_Node::SetFname(std::string F){
    f_name = F;
}
void Loaded_List_Node::SetDir(std::string D){
    dir = D;
}
void Loaded_List_Node::SetNum(std::string N){
    u_num = N;
}