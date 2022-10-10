#pragma once

#include "Database_BST_Node.h"
#include "Loaded_List.h"
#include "Queue.h"
#include <iostream>
#include<stack>

class Database_BST
{
	//friend class TreeManager;
private:
	Database_BST_Node * m_root;
public:
	Queue queue;
	Database_BST() { m_root = nullptr; }
	~Database_BST();

	Database_BST_Node* GetRoot(){
		return m_root;
	}
	void Move(Loaded_List* list); //Data
	void Insert(Loaded_List_Node* CurNode,Loaded_List_Node* DelNode,Database_BST_Node* bstNode,Loaded_List* list);
	void Print(Database_BST_Node* current,const char* filepath);
	Database_BST_Node* Successor(Database_BST_Node* start);
	void Delete(std::string value);
	Database_BST_Node* delete_implement(Database_BST_Node* start, std::string value);
	std::string FindMin(Database_BST_Node* m_root);
	int Search(std::string ptr2,Database_BST_Node* node);
	void InsertQueue(Database_BST_Node* node);
	int Max(int a, int b);
	void BoyerMooreSearch(char* ch, char* name,std::string num);
	std::string Inorder(Database_BST_Node* root,std::string key);
	void InorderSelect(Database_BST_Node* root, std::string key);
	//void deletion(  ); //unique number = key

	// friend std::ostream& operator<<(std::ostream& os, const Database_BST& tree) {

	// // fill in your code to print a node in binary search tree
	// 	return os;
	// }
};
