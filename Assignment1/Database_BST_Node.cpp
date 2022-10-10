#include "Database_BST_Node.h"

void Database_BST_Node::setLeftNode(Database_BST_Node* L){
    m_left = L;
}
void Database_BST_Node::setRightNode(Database_BST_Node* R){
    m_right = R;
}
void Database_BST_Node::setData(Loaded_List_Node Data){
    m_data.SetDir(Data.GetDir());
    m_data.SetFname(Data.GetFileName());
    m_data.SetNum(Data.GetNum());
}
void Database_BST_Node::setNum(std::string num){
    m_data.SetNum(num);
}