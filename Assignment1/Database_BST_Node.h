#pragma once

#include "Loaded_List_Node.h"
#include "Loaded_List.h"
#include <iostream>

class Database_BST_Node
{
private:
	Loaded_List_Node m_data;
	Database_BST_Node* m_left;
	Database_BST_Node* m_right;
public:
	Database_BST_Node(){
		m_data.SetDir("\0");
		m_data.SetFname("\0");
		m_data.SetNum("\0");
        m_left = nullptr;
        m_right = nullptr;
    }
	~Database_BST_Node(){
		m_left = nullptr;
		m_right = nullptr;
	}
	// Database_BST_Node(Loaded_List_Node& data){
	// 	this->m_data = data;
	// }
	// Database_BST_Node(Loaded_List_Node & data, Database_BST_Node* left = NULL, Database_BST_Node* right = NULL)
	// {
	// 	this->m_data = data;
	// 	this->m_left = left;
	// 	this->m_right = right;
	// }
	
	Database_BST_Node* getLeftNode() const { return m_left; }
	Database_BST_Node* getRightNode() const { return m_right; }
	std::string GetNum(){return m_data.GetNum();}
	std::string GetFileName(){return m_data.GetFileName();}
	std::string GetDir(){return m_data.GetDir();}
	void setLeftNode(Database_BST_Node* L);
	void setRightNode(Database_BST_Node* R);
	void setData(Loaded_List_Node Data);
	void setNum(std::string num);

	// friend std::ostream& operator<<(std::ostream& os, const Database_BST_Node* node)
	// {
	// 	if(node != NULL)
	// 		os << node->m_data;
	// 	return os;
	// }
};
