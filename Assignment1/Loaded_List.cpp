#include<string>
#include<fstream>
#include "Loaded_List.h"
#include "Loaded_List_Node.h"
int i = 1;
bool Loaded_List::IsEmpty(){
    if(head == nullptr){
        return true;
    }
    return false;
}
Loaded_List_Node* Loaded_List::GetEnd(){
    if(head == nullptr){
        return nullptr;
    }
    Loaded_List_Node* CurNode = head;
    if(CurNode->GetNext() == nullptr){
        return nullptr;
    }
    while(CurNode->GetDown()){
        CurNode = CurNode->GetDown();
    }
    while(CurNode->GetNext()){
        CurNode = CurNode->GetNext();
    }
    return CurNode;
}
Loaded_List_Node* Loaded_List::FindDel(Loaded_List_Node* CurNode){
    Loaded_List_Node* Node = head;
    if(CurNode->GetNum() == "\0"){
        while(Node->GetDown()->GetDir().compare(CurNode->GetDir()) != 0){
            Node = Node->GetDown();
        }
        while(Node->GetNext()){
            Node = Node->GetNext();
        }
        return Node;
    }
    while(Node->GetDir().compare(CurNode->GetDir()) != 0){
        Node = Node->GetDown();
    }
    while(Node->GetNext()){
        if(Node->GetNext()->GetNum().compare(CurNode->GetNum()) == 0){
            return Node;
        }
        Node = Node->GetNext();
    }
    return nullptr;
}
Loaded_List_Node* Loaded_List::GetHead(){
    return head;
}
Loaded_List_Node* Loaded_List::Load_Delete(){//100개 넘었을 때 삭제해주는 용도
    if(head->GetNext() == nullptr){
        head = head->GetDown();
        Loaded_List_Node* node = head->GetNext();
        Loaded_List_Node* DelNode = node;
        head->SetNext(DelNode->GetNext());
        free(DelNode);
        return nullptr;
    }
    Loaded_List_Node* node = head->GetNext();
    Loaded_List_Node* DelNode = node;
    head->SetNext(DelNode->GetNext());
    free(DelNode);
    return nullptr;
}
Loaded_List_Node* Loaded_List::Load(std::string num, std::string name){//하나씩 넣는 용도
    const char* Dir_name = "img_files";
    if(head == nullptr){
        head = new Loaded_List_Node();
        head->SetDir(Dir_name);
        Loaded_List_Node* CurNode = new Loaded_List_Node();
        head->SetNext(CurNode);
        CurNode->SetNum(num);
        CurNode->SetFname(name);
        CurNode->SetDir(Dir_name);
        return CurNode;
    }
    Loaded_List_Node* CurNode = head;
    while(CurNode->GetNext() != nullptr){
        CurNode = CurNode->GetNext();
    }
    Loaded_List_Node* NewNode = new Loaded_List_Node();
    NewNode->SetNum(num);
    NewNode->SetFname(name);
    NewNode->SetDir(Dir_name);
    CurNode->SetNext(NewNode);
    return head;
}
Loaded_List_Node* Loaded_List::Add(std::string num, std::string name, const char* dir)
{
    if(IsEmpty() == true){
        return nullptr;
    }
    Loaded_List_Node* DirNode = head;
    while(DirNode){
        if(DirNode->GetDir().compare(dir) == 0){
            break;
        }
        if(DirNode->GetDown() == nullptr){
            Loaded_List_Node* node = new Loaded_List_Node();
            DirNode->SetDown(node);
            node->SetDir(dir);
            DirNode = DirNode->GetDown();
            break;
        }
        DirNode = DirNode->GetDown();
    }
    
    if(DirNode->GetNext() == nullptr){//처음 Add할때
        Loaded_List_Node* CurNode = new Loaded_List_Node();
        DirNode->SetNext(CurNode);
        CurNode->SetNum(num);
        CurNode->SetDir(dir);
        CurNode->SetFname(name);
    }
    else{
        Loaded_List_Node* NewNode = new Loaded_List_Node();
        Loaded_List_Node* CurNode = DirNode->GetNext();
        while(CurNode->GetNext()){
            CurNode = CurNode->GetNext();
        }
        CurNode->SetNext(NewNode);
        NewNode->SetNum(num);
        NewNode->SetDir(dir);
        NewNode->SetFname(name);
        return CurNode;
    }
    return DirNode;
}
void Loaded_List::Print_Loaded_List(){
    if(IsEmpty() == true){
        return;
    }
    std::ofstream Load_Result;
    Load_Result.open("log.txt",std::ios_base::app);
    Loaded_List_Node* CurNode = head->GetNext();
    Load_Result<<"==========LOAD=========="<<std::endl;
    while(CurNode){
        Load_Result<<CurNode->GetFileName()<<"/"<<CurNode->GetNum()<<std::endl;
        CurNode = CurNode->GetNext();
    }
    Load_Result<<"========================"<<std::endl;
    return;
}
Loaded_List_Node* Loaded_List::Modify(const char* Dir,const char* filename, std::string num)
{
    if(head == nullptr){
        return nullptr;
    }
    Loaded_List_Node* FindNode = new Loaded_List_Node();
    Loaded_List_Node* Node = new Loaded_List_Node();
    Node = head;
    FindNode = head->GetNext();
    while(Node){
        if(FindNode == nullptr){
            Node = Node->GetDown();
            if(Node == nullptr){
                break;
            }
            FindNode = Node->GetNext();
        }
        if(FindNode->GetNum().compare(num) == 0){
            return nullptr;
        }
        FindNode = FindNode->GetNext();
    }

    Loaded_List_Node* PrevNode = new Loaded_List_Node();
    Loaded_List_Node* CurNode = head;
    while(CurNode != nullptr){
        if(CurNode->GetDir().compare(Dir) == 0){
            PrevNode = CurNode;
            CurNode = CurNode->GetNext();
            break;
        }
        CurNode = CurNode->GetDown();
    }
    if(CurNode == nullptr){////////////제출하기 전에 modify 잘되는지 확인해보고 제출
        return nullptr;
    }
    //PrevNode->GetFileName().compare("\0") == 0&&CurNode != head
    if(CurNode->GetNext() != nullptr){
        if(CurNode->GetNext()->GetFileName().compare(filename) == 0){//헤드 다음 노드일때(고친듯?)
        Loaded_List_Node* NewNode = new Loaded_List_Node();
        NewNode->SetDir(CurNode->GetDir());
        NewNode->SetFname(CurNode->GetNext()->GetFileName());
        NewNode->SetNum(num);

        PrevNode = CurNode;
        CurNode = CurNode->GetNext();
        

        NewNode->SetNext(CurNode->GetNext());
        PrevNode->SetNext(NewNode);
        free(CurNode);
        return NewNode;
        }
    }

    while(CurNode->GetNext() != nullptr){
        if(CurNode->GetFileName().compare(filename) == 0){
            Loaded_List_Node* NewNode = new Loaded_List_Node();
            NewNode->SetDir(CurNode->GetDir());
            NewNode->SetFname(CurNode->GetFileName());
            NewNode->SetNum(num);
            NewNode->SetNext(PrevNode->GetNext()->GetNext());
            PrevNode->SetNext(NewNode);
            free(CurNode);
            return NewNode;
        }
        PrevNode = CurNode;
        CurNode = CurNode->GetNext();
    }
    if(CurNode->GetFileName().compare(filename) == 0){//마지막 노드가 대상 노드일때
        Loaded_List_Node* NewNode = new Loaded_List_Node();
        NewNode->SetDir(CurNode->GetDir());
        NewNode->SetFname(CurNode->GetFileName());
        NewNode->SetNum(num);
        NewNode->SetNext(PrevNode->GetNext()->GetNext());
        PrevNode->SetNext(NewNode);
        free(CurNode);
        return NewNode;
    }
    return nullptr;
}