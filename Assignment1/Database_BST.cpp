#include "Database_BST.h"
#include "Loaded_List.h"
#include "Queue.h"
#include<iostream>
#include<fstream>
#include<string>
int num = 0;
int searchnum = 0;//search 처음할때 출력하기 위해서 사용
int closenum = 0;//닫는 표시 출력하기 위해서 사용
std::string Selectch;
void Database_BST::Insert(Loaded_List_Node* CurNode,Loaded_List_Node* DelNode,Database_BST_Node* bstNode,Loaded_List* list){
    if(num >299){
        std::string Min;
        Min = FindMin(m_root);
        Delete(Min);
        num--;
    }
    if(m_root == nullptr){
        m_root = new Database_BST_Node();
        m_root->setData(*CurNode);
        DelNode->SetNext(nullptr);
        free(*&CurNode);
        num++;
        return;
    }
    if(stoi(bstNode->GetNum())>stoi(CurNode->GetNum())){
        if(bstNode->getLeftNode() == nullptr){
            Database_BST_Node* NewNode= new Database_BST_Node();
            bstNode->setLeftNode(NewNode);
            NewNode->setData(*CurNode);
            DelNode->SetNext(nullptr);
            free(*&CurNode);
            num++;
            return;
        }
        else{
            Insert(CurNode,DelNode,bstNode->getLeftNode(),list);
        }
    }
    else if(stoi(bstNode->GetNum())<stoi(CurNode->GetNum())){
        if(bstNode->getRightNode() == nullptr){
            Database_BST_Node* NewNode = new Database_BST_Node();
            bstNode->setRightNode(NewNode);
            NewNode->setData(*CurNode);
            DelNode->SetNext(nullptr);
            free(*&CurNode);
            num++;
            return;
        }
        else{
            Insert(CurNode,DelNode,bstNode->getRightNode(),list);
        }
    }
    else if(bstNode->GetNum().compare(CurNode->GetNum()) == 0){
        DelNode->SetNext(nullptr);
        free(*&CurNode);
        return;
    }
    return;
}

void Database_BST::Move(Loaded_List* list){//300개 넘었을 때 삭제하는 기능 추가
    while(list->GetEnd() != nullptr){
        Loaded_List_Node* CurNode = list->GetEnd();
        Loaded_List_Node* DelNode = list->FindDel(CurNode);
        if(CurNode->GetNum().compare("\0") == 0){
            Loaded_List_Node* headNode = list->GetHead();
            Loaded_List_Node* PrevheadNode = new Loaded_List_Node();
            while(headNode->GetDown()){
                PrevheadNode = headNode;
                headNode = headNode->GetDown();
            }
            PrevheadNode->SetDown(nullptr);
            free(headNode);
            CurNode = list->GetEnd();
            DelNode = list->FindDel(CurNode);
        }
        if(DelNode->GetNext() == nullptr){
            CurNode = DelNode;
            DelNode= list->FindDel(CurNode);
        }
        Database_BST_Node* bstNode = m_root;
        Insert(CurNode,DelNode,bstNode,list);
    }
    Loaded_List_Node* headHead = list->GetHead();
    free(*&headHead);
    list->SetHead(nullptr);
    return;
}
std::string Database_BST::FindMin(Database_BST_Node* m_root){
    if(m_root == nullptr){
        return "\0";
    }
    else if(m_root->getLeftNode() == nullptr){
        return m_root->GetNum();
    }
    else{
        return FindMin(m_root->getLeftNode());
    }
}
Database_BST_Node* Database_BST::Successor(Database_BST_Node* start){//확실한지 검증 필요
    auto current = start->getRightNode();
    while(current && current->getLeftNode()){
        current = current->getLeftNode();
    }
    return current;
}
void Database_BST::Delete(std::string value){
    m_root = delete_implement(m_root,value);
}
Database_BST_Node* Database_BST::delete_implement(Database_BST_Node* start, std::string value){
    if(!start){
        return nullptr;
    }
    if(stoi(value)<stoi(start->GetNum())){
        start->setLeftNode(delete_implement(start->getLeftNode(), value));
    }
    else if(stoi(value)>stoi(start->GetNum())){
        start->setRightNode(delete_implement(start->getRightNode(),value));
    }
    else{
        if(!start->getLeftNode()){
            auto tmp = start->getRightNode();
            delete start;
            return tmp;
        }
        if(!start->getRightNode()){
            auto tmp = start->getLeftNode();
            delete start;
            return tmp;
        }
        auto succ = Successor(start);
        start->setNum(succ->GetNum());/////////
        start->setRightNode(delete_implement(start->getRightNode(),succ->GetNum()));
    }
    return start;
}

int Database_BST::Max(int a, int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
void Database_BST::BoyerMooreSearch(char* ch,char* name,std::string num){
    int lengch = strlen(ch);
    int lengname = strlen(name);
    
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
        if(j<0){
            std::ofstream fout;
            fout.open("log.txt",std::ios::app);
            if(searchnum == 0){
                fout << "========SEARCH========"<< std::endl;
                searchnum++;
            }
            if(fout.is_open() == true){
                fout << "\""<<ch<<"\""<<"/"<<num<<std::endl;
            }
            closenum++;
            return;
        }
        else{
            s +=Max(1,j-badchar[(int)ch[s+j]]);
        }
    }
    return;
}

void Database_BST::InsertQueue(Database_BST_Node* node){
    // return if the tree is empty
    if(node == nullptr){
        return;
    }
    // create an empty stack and push the root node
    std::stack<Database_BST_Node*> s;
    s.push(node);
    std::stack<std::string>s1;
    std::stack<std::string>s2;
    // loop till stack is empty
    while(!s.empty()){
        // pop a node from the stack and push the data into the output stack
        Database_BST_Node* Cur = s.top();
        s.pop();
        s1.push(Cur->GetFileName());
        s2.push(Cur->GetNum());
        //queue.push(Cur->GetFileName(), Cur->GetNum());
        // push the left and right child of the popped node into the stack
        if(Cur->getLeftNode()){
            s.push(Cur->getLeftNode());
        }
        if(Cur->getRightNode()){
            s.push(Cur->getRightNode());
        }
    }
    while(!s1.empty()){
        queue.push(s1.top(),s2.top());
        s1.pop();
        s2.pop();
    }
    return;
}


int Database_BST::Search(std::string ptr2,Database_BST_Node* node){
    searchnum = 0;
    while(queue.empty() != true){
        std::string name = queue.EndValue_name();
        std::string num = queue.EndValue_num();
        char* Fname = new char[100];
        char* search = new char[100];
        strcpy(Fname,name.c_str());
        strcpy(search,ptr2.c_str());
        BoyerMooreSearch(Fname,search,num);
        queue.pop();
    }
    return closenum;
}
std::string Database_BST::Inorder(Database_BST_Node* root,std::string key){
    Selectch == "\0";
    InorderSelect(root, key);
    return Selectch;
}
void Database_BST::InorderSelect(Database_BST_Node* root, std::string key){
    if (root != nullptr) {
        Inorder(root->getLeftNode(),key);
        if(root->GetNum().compare(key) == 0){
            Selectch = root->GetFileName();
            return;
        }
        Inorder(root->getRightNode(),key);
    }
}