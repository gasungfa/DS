#include "Database_BST.h"//include header file
#include "Loaded_List.h"
#include "Queue.h"
#include<iostream>
#include<fstream>
#include<string>
int num = 0;//Use for overflow(300)
int searchnum = 0;//Use to output for search
int closenum = 0;//Use for Printing out a closing mark 
std::string Selectch;//Use for Edit(file name)
void Database_BST::Insert(Loaded_List_Node* CurNode,Loaded_List_Node* DelNode,Database_BST_Node* bstNode,Loaded_List* list){
    if(num >299){//for overflow
        std::string Min;
        Min = FindMin(m_root);
        Delete(Min);
        num--;
    }
    if(m_root == nullptr){//when BST is empty
        m_root = new Database_BST_Node();
        m_root->setData(*CurNode);
        DelNode->SetNext(nullptr);
        free(*&CurNode);//free CurNode
        num++;//Global variable++
        return;
    }
    if(stoi(bstNode->GetNum())>stoi(CurNode->GetNum())){//Comparison bstNode>CurNode(small)
        if(bstNode->getLeftNode() == nullptr){//when LeftNode is NULL
            Database_BST_Node* NewNode= new Database_BST_Node();
            bstNode->setLeftNode(NewNode);
            NewNode->setData(*CurNode);
            DelNode->SetNext(nullptr);
            free(*&CurNode);
            num++;
            return;
        }
        else{
            Insert(CurNode,DelNode,bstNode->getLeftNode(),list);//when Left is not NULL
        }
    }
    else if(stoi(bstNode->GetNum())<stoi(CurNode->GetNum())){//Comparison bstNode<CurNode(big)
        if(bstNode->getRightNode() == nullptr){//when RightNode is NULL
            Database_BST_Node* NewNode = new Database_BST_Node();
            bstNode->setRightNode(NewNode);
            NewNode->setData(*CurNode);
            DelNode->SetNext(nullptr);
            free(*&CurNode);
            num++;
            return;
        }
        else{
            Insert(CurNode,DelNode,bstNode->getRightNode(),list);//when RightNode is not NULL
        }
    }
    else if(bstNode->GetNum().compare(CurNode->GetNum()) == 0){//Comparison bstNode==CurNode(same value)
        DelNode->SetNext(nullptr);//previous node's next initialize
        free(*&CurNode);
        return;
    }
    return;
}

void Database_BST::Move(Loaded_List* list){//use for Linked List's end Node
    while(list->GetEnd() != nullptr){
        Loaded_List_Node* CurNode = list->GetEnd();
        Loaded_List_Node* DelNode = list->FindDel(CurNode);
        if(CurNode->GetNum().compare("\0") == 0){//if CurNode's unique num is NULL
            Loaded_List_Node* headNode = list->GetHead();
            Loaded_List_Node* PrevheadNode = new Loaded_List_Node();
            while(headNode->GetDown()){//find end down
                PrevheadNode = headNode;
                headNode = headNode->GetDown();
            }
            PrevheadNode->SetDown(nullptr);
            free(headNode);
            CurNode = list->GetEnd();
            DelNode = list->FindDel(CurNode);
        }
        if(DelNode->GetNext() == nullptr){//Linked List is empty
            CurNode = DelNode;
            DelNode= list->FindDel(CurNode);
        }
        Database_BST_Node* bstNode = m_root;
        Insert(CurNode,DelNode,bstNode,list);//use Insert implement
    }
    Loaded_List_Node* headHead = list->GetHead();
    free(*&headHead);
    list->SetHead(nullptr);
    return;
}
std::string Database_BST::FindMin(Database_BST_Node* m_root){//find minimum value
    if(m_root == nullptr){//if Linked List is empty
        return "\0";
    }
    else if(m_root->getLeftNode() == nullptr){//if node's left child is empty
        return m_root->GetNum();
    }
    else{
        return FindMin(m_root->getLeftNode());//Recursive function
    }
}
Database_BST_Node* Database_BST::Successor(Database_BST_Node* start){//for delete(find substitute)
    auto current = start->getRightNode();
    while(current && current->getLeftNode()){
        current = current->getLeftNode();
    }
    return current;
}
void Database_BST::Delete(std::string value){
    m_root = delete_implement(m_root,value);
}
Database_BST_Node* Database_BST::delete_implement(Database_BST_Node* start, std::string value){//find node and delete
    if(!start){
        return nullptr;
    }
    if(stoi(value)<stoi(start->GetNum())){//compare
        start->setLeftNode(delete_implement(start->getLeftNode(), value));
    }
    else if(stoi(value)>stoi(start->GetNum())){//compare
        start->setRightNode(delete_implement(start->getRightNode(),value));
    }
    else{
        if(!start->getLeftNode()){//delete
            auto tmp = start->getRightNode();
            delete start;
            return tmp;
        }
        if(!start->getRightNode()){//delete
            auto tmp = start->getLeftNode();
            delete start;
            return tmp;
        }
        auto succ = Successor(start);//find substitute
        start->setNum(succ->GetNum());//set num
        start->setRightNode(delete_implement(start->getRightNode(),succ->GetNum()));//insert node
    }
    return start;
}

int Database_BST::Max(int a, int b){//find high value for voyermoore
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
void Database_BST::BoyerMooreSearch(char* ch,char* name,std::string num){//to find a word in string
    int lengch = strlen(ch);//length of ch
    int lengname = strlen(name);//length of name
    
    int badchar[256] = {-1,};
    for(int i = 0;i<lengname;i++){
        badchar[(int)name[i]] = i;
    }
    int s = 0,j;
    while(s<lengch-lengname){
        j = lengname-1;
        while(j>=0&&ch[s+j] == name[j]){
            j--;
        }
        if(j<0){//if word is exist in string
            std::ofstream fout;
            fout.open("log.txt",std::ios::app);//open file
            if(searchnum == 0){
                fout << "========SEARCH========"<< std::endl;//output
                searchnum++;
            }
            if(fout.is_open() == true){
                fout << "\""<<ch<<"\""<<"/"<<num<<std::endl;
            }
            closenum++;
            return;
        }
        else{//if word is not exist in string
            s +=Max(1,j-badchar[(int)ch[s+j]]);//move string
        }
    }
    return;
}

void Database_BST::InsertQueue(Database_BST_Node* node){//for iterative post order using two stack
    // return if the tree is empty
    if(node == nullptr){
        return;
    }
    // create an empty stack and push the root node
    std::stack<Database_BST_Node*> s;
    s.push(node);
    std::stack<std::string>s1;//declare two stack
    std::stack<std::string>s2;
    // loop till stack is empty
    while(!s.empty()){
        // pop a node from the stack and push the data into the output stack
        Database_BST_Node* Cur = s.top();
        s.pop();//pop the stack value
        s1.push(Cur->GetFileName());//insert data in node
        s2.push(Cur->GetNum());
        // push the left and right child of the popped node into the stack
        if(Cur->getLeftNode()){
            s.push(Cur->getLeftNode());
        }
        if(Cur->getRightNode()){
            s.push(Cur->getRightNode());
        }
    }
    while(!s1.empty()){//push the data in stack to queue
        queue.push(s1.top(),s2.top());
        s1.pop();//delete the data
        s2.pop();
    }
    return;
}


int Database_BST::Search(std::string ptr2,Database_BST_Node* node){//for using BoyerMooreSearch implement
    searchnum = 0;
    while(queue.empty() != true){
        std::string name = queue.EndValue_name();
        std::string num = queue.EndValue_num();
        char* Fname = new char[100];
        char* search = new char[100];
        strcpy(Fname,name.c_str());//copy the name
        strcpy(search,ptr2.c_str());//copy the string
        BoyerMooreSearch(Fname,search,num);//use implement
        queue.pop();//delete the data
    }
    return closenum;
}
std::string Database_BST::Inorder(Database_BST_Node* root,std::string key){//for Selete command
    Selectch == "\0";//for Edit file path
    InorderSelect(root, key);//using implement
    return Selectch;
}
void Database_BST::InorderSelect(Database_BST_Node* root, std::string key){//find the node's filename
    if (root != nullptr) {
        Inorder(root->getLeftNode(),key);
        if(root->GetNum().compare(key) == 0){
            Selectch = root->GetFileName();
            return;
        }
        Inorder(root->getRightNode(),key);//Recursive function
    }
}