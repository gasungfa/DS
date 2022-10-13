#include "Manager.h"
#include "Loaded_List.h"
#include "Database_BST.h"
#include "rawreader.h"
#include<iostream>
#include<cstring>
#include<fstream>
int n = 0;

Manager::Manager()//manager class's constructor
{
    remove(RESULT_LOG_PATH);//log.txt remove
    fout.open(RESULT_LOG_PATH,std::ios_base::out|std::ios::app);//file open and use to connect previous value
    list = new Loaded_List();//linked list's object
    bst = new Database_BST();//BST's object
}

Manager::~Manager()//manager class's Destructor
{
    if (fout.is_open()){//file close
        fout.close();
    }
    free(list);
    free(bst);
}

void Manager::Run(const char* filepath)
{
    fin.open(filepath);
    if(!fin.is_open()) //file is not open
	{
        PrintError(CommandFileNotExist);
        return;
	}
    char* text = new char[100];
    while(!fin.eof()){
        fin.getline(text, 100);//예외처리 해줄것
        if(text == nullptr){//command.txt is empty
            Result result = WrongInstruction;
            PrintError(result);
            continue;
        }
        char* ptr1 = strtok(text, " ");
        char* ptr2 = new char[100];
        char* ptr3 = new char[100];
        char* ptr4 = new char[100];
        if(strcmp(ptr1,"LOAD") == 0){//if command is LOAD
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(LoadFileNotExist);
                continue;
            }
            Result result = Load("./img_files/filesnumbers.csv",list);//start Load implement
            if(result != Success){//if result is not Success
                PrintError(result);
                continue;
            }
        }
        else if(strcmp(ptr1,"ADD") == 0){//if command is ADD
            ptr2 = strtok(NULL, " ");
            if(ptr2 == nullptr){//if factor is short
                PrintError(AddError);//print error
                continue;
            }
            ptr3 = strtok(NULL, " ");
            if(ptr3 == nullptr){//if factor is short
                PrintError(AddError);
                continue;
            }
            if(list->GetHead() == nullptr){//if Linked List's head == NULL
                Result result = AddError;
                PrintError(result);
                continue;
            }
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(AddError);
                continue;
            }
            Result result = Add(ptr2,ptr3,list);//run the Add implement
            if(result == Success){
                PrintAdd();
            }
            else{
                PrintError(result);
                continue;
            }
        }
        else if(strcmp(ptr1,"MODIFY") == 0){//if command is MODIFY
            ptr2 = strtok(NULL, " ");
            if(ptr2 == nullptr){//if factor is short
                PrintError(ModifyError);
                continue;
            }
            ptr3 = strtok(NULL, "\"");
            if(ptr3 == nullptr){//if factor is short
                PrintError(ModifyError);
                continue;
            }
            ptr4 = strtok(NULL, " ");
            if(ptr4 == nullptr){//if factor is short
                PrintError(ModifyError);
                continue;
            }
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(ModifyError);
                continue;
            }
            char* end;
            while(isspace(*ptr4)) ptr4++;
            //in front of " " emptying
            if(*ptr4 == 0){
                //when the entire array is blank
                PrintError(ModifyError);
            }
            end = ptr4 + strlen(ptr4) -1;
            while(end > ptr4&&isspace(*end)) end--;
            *(end+1) = 0;
            Result result = Modify(ptr2,ptr3,ptr4);//run the implement MOdify
            if(result != Success){//if the result is not Success
                PrintError(result);
            }
            else{
                PrintModify();
            }
        }
        else if(strcmp(ptr1,"MOVE") == 0){//if command is MOVE
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(MoveError);
                continue;
            }
            Result result = Move(list);//run the implement Move with linked list
            if(result != Success){//if result is not Success
                PrintError(result);
                continue;
            }
            else if(result == Success){
                PrintMove();
            }
        }
        else if(strcmp(ptr1,"PRINT") == 0){//if command is PRINT
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(Print_Error);
                continue;
            }
            Result result = Print(bst);//run the implement Print with binary search tree
            if(result != Success){
                PrintError(result);
            }
        }
        else if(strcmp(ptr1,"SEARCH") == 0){//if Command is SEARCH
            ptr2 = strtok(NULL,"\"");
            if(ptr2 == nullptr){//if factor is short
                PrintError(Search_Error);
                continue;
            }
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(Search_Error);
                continue;
            }
            char* end;//in front of " " emptying
            while(isspace(*ptr2)) ptr2++;
            if(*ptr2 == 0){
                //when the entire array is blank
                PrintError(Search_Error);
            }
            end = ptr2 + strlen(ptr2) -1;
            while(end > ptr2&&isspace(*end)) end--;
            *(end+1) = 0;
            Result result = SEARCH(ptr2);//run the implement SEARCH
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
        else if(strcmp(ptr1,"SELECT") == 0){//if Command is SELECT
            ptr2 = strtok(NULL,"\n");
            if(ptr2 == nullptr){//if factor is short
                PrintError(Select_Error);
                continue;
            }
            if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(Select_Error);
                continue;
            }
            Result result = Select(ptr2);//run the implement Select
            if(result != Success){//if result is not Success
                PrintError(Select_Error);
            }
            else{
                PrintSelect();
                continue;
            }
        }
        else if(strcmp(ptr1,"EDIT") == 0){//if Command is EDIT
            if(bst->GetRoot() == nullptr){//if bst is empty
                PrintError(EditError);
                continue;
            }
            ptr2 = strtok(NULL," ");
            if(ptr2 == nullptr){//if factor is short
                PrintError(EditError);
                continue;
            }
            if(strcmp(ptr2,"-f") == 0){//if command is -f
                if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(EditError);
                continue;
                }
                Symmetry(Image);//Point Symmetry the image
                PrintEdit();
            }
            else if(strcmp(ptr2,"-l") == 0){//if command is -l
                ptr3 = strtok(NULL," ");
                if(ptr3 == nullptr){
                    PrintError(EditError);
                    continue;
                }
                if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(EditError);
                continue;
                }
                Light(ptr3,Image);//raise the brightness
                PrintEdit();
            }
            else if(strcmp(ptr2,"-r") == 0){//if command is -r
                if(strtok(NULL," ") != NULL){//if factor is over
                PrintError(EditError);
                continue;
                }
                Reduction(Image);//resize the image
                PrintEdit();
            }
        }
        else if(strcmp(ptr1,"EXIT") == 0){//if command is EXIT
            free(text);
            PrintExit();
            return;
        }
        else{
            Result result = WrongInstruction;//wrong instruction
            PrintError(result);
        }
    }
    fin.close();//file close
    
}
void Manager::PrintError(Result result)
{
    fout << "========ERROR========" <<std::endl<< result << std::endl;
    fout<<  "====================="<<std::endl;
}
Result Manager::Load(const char* filepath,Loaded_List* list)//Load the data
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
    while(!Load_input.eof()){//end of file
        if(n>99){//if n is over 99
            if(list->GetHead() == nullptr){
                n =0;
            }
            else{
                list->Load_Delete();//delete the Linked List's data
                n--;
            }
        }
        getline(Load_input,num,',');//receive input
        if(num == "\0"){
            return Result::LoadFileNotExist;
        }
        getline(Load_input,Name,'.');//receive input
        getline(Load_input,garbage,'\n');//receive input
        list->Load(num, Name);//run the implement Load
        n++;
    }
    list->Print_Loaded_List();//Print the Linked List
    Load_input.close();//file close
    return Result::Success;//return success
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
    if(list->GetHead() == nullptr){//if linked list is empty
        return Result::AddError;
    }
    while(!Add_input.eof()){
        if(n>99){//if n is over 99
            list->Load_Delete();//delete the linked list's data
            n--;//global variable --
        }
        getline(Add_input,num,',');//receive input
        getline(Add_input,Name,'.');//receive input
        getline(Add_input,garbage,'\n');//receive garbage value
        if(list->Add(num,Name,Dir) == nullptr){//run the implement Add
            return Result::AddError;
        }
        n++;//global variable++
    }
    Add_input.close();
    return Result::Success;
}
Result Manager::Modify(const char* Dir,const char* filename, std::string num)
{
    if(list->Modify(Dir,filename,num) ==  nullptr){//run the implement Modify
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
    if(list->IsEmpty() == true){//Linked List's object is not empty
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
    bst->InsertQueue(bst->GetRoot());//bst's data for insert queue
    if(bst->Search(ptr2,bst->GetRoot()) == 0){
        return CloseNum;
    }
    return Success;
}
Result Manager::Select(std::string ptr2){//if Command is SELECT
    std::string FName;
    if(bst->Inorder(bst->GetRoot(),ptr2).compare("\0") == 0){
        return Select_Error;
    }
    else{
        FName = bst->Inorder(bst->GetRoot(),ptr2);//Find the value with Inorder
    }
    std::string path = "./images/";
    std::string raw = ".RAW";
    FName = path+FName;//put together path and Fname
    FName = FName + raw;//put together raw and Fname
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