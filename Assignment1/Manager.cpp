#include "Manager.h"
#include "Loaded_List.h"
#include "Database_BST.h"
#include "rawreader.h"
#include<iostream>
#include<cstring>
#include<fstream>
int n = 0;

Manager::Manager()
{
    remove(RESULT_LOG_PATH);
    fout.open(RESULT_LOG_PATH,std::ios_base::out|std::ios::app);
    list = new Loaded_List();
    bst = new Database_BST();
}

Manager::~Manager()
{
    if (fout.is_open()){
        fout.close();
    }
    free(list);
    free(bst);
}

void Manager::Run(const char* filepath)
{
    fin.open(filepath);
    if(!fin.is_open()) 
	{
        PrintError(CommandFileNotExist);
        return;
	}
    char* text = new char[100];
    while(!fin.eof()){
        fin.getline(text, 100);//예외처리 해줄것
        if(text == nullptr){
            Result result = WrongInstruction;
            PrintError(result);
            continue;
        }
        char* ptr1 = strtok(text, " ");
        char* ptr2 = new char[100];
        char* ptr3 = new char[100];
        char* ptr4 = new char[100];
        if(strcmp(ptr1,"LOAD") == 0){
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(LoadFileNotExist);
                continue;
            }
            Result result = Load("./img_files/filesnumbers.csv",list);
            if(result != Success){
                PrintError(result);
                continue;
            }
        }
        else if(strcmp(ptr1,"ADD") == 0){
            ptr2 = strtok(NULL, " ");
            if(ptr2 == nullptr){
                PrintError(AddError);
                continue;
            }
            ptr3 = strtok(NULL, " ");
            if(ptr3 == nullptr){
                PrintError(AddError);
                continue;
            }
            if(list->GetHead() == nullptr){
                Result result = AddError;
                PrintError(result);
                continue;
            }
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(AddError);
                continue;
            }
            Result result = Add(ptr2,ptr3,list);
            if(result == Success){
                PrintAdd();
            }
            else{
                PrintError(result);
                continue;
            }
        }
        else if(strcmp(ptr1,"MODIFY") == 0){
            ptr2 = strtok(NULL, " ");
            if(ptr2 == nullptr){
                PrintError(ModifyError);
                continue;
            }
            ptr3 = strtok(NULL, "\"");
            if(ptr3 == nullptr){
                PrintError(ModifyError);
                continue;
            }
            ptr4 = strtok(NULL, " ");
            if(ptr4 == nullptr){
                PrintError(ModifyError);
                continue;
            }
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(ModifyError);
                continue;
            }
            char* end;
            while(isspace(*ptr4)) ptr4++;
            //앞에 " "비우기
            if(*ptr4 == 0){
                //배열 전체가 공백일 때
                PrintError(ModifyError);
            }
            end = ptr4 + strlen(ptr4) -1;
            while(end > ptr4&&isspace(*end)) end--;
            *(end+1) = 0;
            Result result = Modify(ptr2,ptr3,ptr4);
            if(result != Success){
                PrintError(result);
            }
            else{
                PrintModify();
            }
        }
        else if(strcmp(ptr1,"MOVE") == 0){
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(MoveError);
                continue;
            }
            Result result = Move(list);
            if(result != Success){
                PrintError(result);
                continue;
            }
            else if(result == Success){
                PrintMove();
            }
        }
        else if(strcmp(ptr1,"PRINT") == 0){
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(Print_Error);
                continue;
            }
            Result result = Print(bst);
            if(result != Success){
                PrintError(result);
            }
        }
        else if(strcmp(ptr1,"SEARCH") == 0){
            ptr2 = strtok(NULL,"\"");
            if(ptr2 == nullptr){
                PrintError(Search_Error);
                continue;
            }
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(Search_Error);
                continue;
            }
            char* end;
            while(isspace(*ptr2)) ptr2++;
            if(*ptr2 == 0){
                PrintError(Search_Error);
            }
            end = ptr2 + strlen(ptr2) -1;
            while(end > ptr2&&isspace(*end)) end--;
            *(end+1) = 0;
            Result result = SEARCH(ptr2);
            if(result != Success&&result != CloseNum){
                PrintError(result);
                continue;
            }
            if(result == Success){
                fout<<  "====================="<<std::endl;
            }
            if(result == CloseNum){
                PrintError(Search_Error);
                continue;
            }
        }
        else if(strcmp(ptr1,"SELECT") == 0){
            ptr2 = strtok(NULL,"\n");
            if(ptr2 == nullptr){
                PrintError(Select_Error);
                continue;
            }
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(Select_Error);
                continue;
            }
            Result result = Select(ptr2);
            if(result != Success){
                PrintError(Select_Error);
            }
            else{
                PrintSelect();
                continue;
            }
        }
        else if(strcmp(ptr1,"EDIT") == 0){
            if(bst->GetRoot() == nullptr){
                PrintError(EditError);
                continue;
            }
            ptr2 = strtok(NULL," ");
            if(ptr2 == nullptr){
                PrintError(EditError);
                continue;
            }
            if(strcmp(ptr2,"-f") == 0){
                if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(EditError);
                continue;
                }
                Symmetry(Image);
                PrintEdit();
            }
            else if(strcmp(ptr2,"-l") == 0){
                ptr3 = strtok(NULL," ");
                if(ptr3 == nullptr){
                    PrintError(EditError);
                    continue;
                }
                if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(EditError);
                continue;
                }
                Light(ptr3,Image);
                PrintEdit();
            }
            else if(strcmp(ptr2,"-r") == 0){
                if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(EditError);
                continue;
                }
                Reduction(Image);
                PrintEdit();
            }
        }
        else if(strcmp(ptr1,"EXIT") == 0){
            PrintExit();
            return;
        }
        else{
            Result result = WrongInstruction;
            PrintError(result);
        }
    }
    fin.close();
    
}
void Manager::PrintError(Result result)
{
    fout << "========ERROR========" <<std::endl<< result << std::endl;
    fout<<  "====================="<<std::endl;
}
Result Manager::Load(const char* filepath,Loaded_List* list)
{
    std::ifstream Load_input;
    Load_input.open(filepath);
    if(!Load_input.is_open()){
        return Result::LoadFileNotExist;
    }
    if(Load_input.eof()){
        return Result::LoadFileNotExist;
    }
    std::string num;
    std::string Name;
    std::string garbage;
    while(!Load_input.eof()){
        if(n>99){
            if(list->GetHead() == nullptr){
                n =0;
            }
            else{
                list->Load_Delete();
                n--;
            }
        }
        getline(Load_input,num,',');
        if(num == "\0"){
            return Result::LoadFileNotExist;
        }
        getline(Load_input,Name,'.');
        getline(Load_input,garbage,'\n');
        list->Load(num, Name);
        n++;
    }
    list->Print_Loaded_List();
    Load_input.close();
    return Result::Success;
}
Result Manager::Add(const char* Dir, const char* filepath,Loaded_List* list)
{
    if(list->GetHead() == nullptr){
        return AddError;
    }
    std::string num;
    std::string Name;
    std::string garbage;
    std::ifstream Add_input;
    Add_input.open(filepath);
    if(!Add_input.is_open()){
        return Result::AddError;
    }
    if(Add_input.eof()){
        return Result::AddError;
    }
    if(list->GetHead() == nullptr){
        return Result::AddError;
    }
    while(!Add_input.eof()){
        if(n>99){
            list->Load_Delete();
            n--;
        }
        getline(Add_input,num,',');
        getline(Add_input,Name,'.');
        getline(Add_input,garbage,'\n');
        if(list->Add(num,Name,Dir) == nullptr){
            return Result::AddError;
        }
        n++;
    }
    Add_input.close();
    return Result::Success;
}
Result Manager::Modify(const char* Dir,const char* filename, std::string num)
{
    if(list->Modify(Dir,filename,num) ==  nullptr){
        return ModifyError;
    }
    return Result::Success;
}
 void Manager::PrintAdd()
 {
    fout << "========ADD========" <<std::endl<< "SUCCESS" << std::endl;
    fout<<  "====================="<<std::endl;
 }
 void Manager::PrintModify(){
    fout << "========MODIFY========" <<std::endl<< "SUCCESS" << std::endl;
    fout<<  "====================="<<std::endl;
 }
Result Manager::Move(Loaded_List* list){
    if(list->IsEmpty() == true){
        return MoveError;
    }
    bst->Move(list);
    n = 0;
    return Success;
}
void Manager::PrintMove(){
    fout << "========Move========" <<std::endl<< "SUCCESS" << std::endl;
    fout<<  "====================="<<std::endl;
}
Result Manager::Print(Database_BST* bst){
    if(bst->GetRoot() == nullptr){
        return Print_Error;
    }
    fout << "========PRINT========"<< std::endl;
    PrintInorder(bst->GetRoot());
    fout<<  "====================="<<std::endl;
    return Success;
}
void Manager::PrintInorder(Database_BST_Node* node){
    if(node!= nullptr){
        PrintInorder(node->getLeftNode());
        fout<<node->GetDir()<<" /";
        fout<<node->GetFileName()<<" /";
        fout<<node->GetNum()<<std::endl;
        PrintInorder(node->getRightNode());
    }
}
Result Manager::SEARCH(std::string ptr2){
    if(bst->GetRoot() == nullptr){
        return Search_Error;
    }
    bst->InsertQueue(bst->GetRoot());
    if(bst->Search(ptr2,bst->GetRoot()) == 0){
        return CloseNum;
    }
    return Success;
}
Result Manager::Select(std::string ptr2){
    std::string FName;
    if(bst->Inorder(bst->GetRoot(),ptr2).compare("\0") == 0){
        return Select_Error;
    }
    else{
        FName = bst->Inorder(bst->GetRoot(),ptr2);
    }
    std::string path = "./images/";
    std::string raw = ".RAW";
    FName = path+FName;
    FName = FName + raw;
    Manager::Image = FName;
    return Success;
}
void Manager::PrintSelect(){
    fout << "========SELECT========" <<std::endl<< "SUCCESS" << std::endl;
    fout<<  "====================="<<std::endl;
}
void Manager::PrintExit(){
    fout << "========EXIT========" <<std::endl<< "SUCCESS" << std::endl;
    fout<<  "====================="<<std::endl;
}
void Manager::PrintEdit(){
    fout << "========EDIT========" <<std::endl<< "SUCCESS" << std::endl;
    fout<<  "====================="<<std::endl;
}