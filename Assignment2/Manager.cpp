#include "Manager.h"
#include<fstream>
#include<set>
#include<list>

void Manager::run(const char* command)//first start when program start
{
	fin.open(command);//open the command.txt
	if(!fin.is_open())
	{
		return;
	}
	char* text = new char[100];
	while (!fin.eof())
	{
		fin.getline(text, 100);
		if(text == nullptr){
			printErrorCode(100);
			continue;
		}
    	char* ptr1 = strtok(text, "\t");
		char* ptr2 = new char[100];
		char* ptr3 = new char[100];
		char* ptr4 = new char[100];
		if(strcmp(ptr1,"LOAD") == 0){//if command is LOAD
			if(strtok(NULL,"\t") != NULL){
				printErrorCode(100);
				continue;
			}
			if(LOAD() == true){
				flog << "========LOAD========" << endl;
				printSuccessCode();
			}
			else{
				flog << "========LOAD========" << endl;
				printErrorCode(100);
			}
		}
		else if(strcmp(ptr1, "BTLOAD") == 0){//if command is BTLOAD
			if(strtok(NULL,"\t") != NULL){
				printErrorCode(200);
				continue;
			}
			if(bptree->getRoot() != nullptr){
				flog << "========BTLOAD========" << endl;
				printErrorCode(200);
				continue;
			}
			if(BTLOAD() == true){
				flog << "========BTLOAD========" << endl;
				printSuccessCode();
			}
			else{
				flog << "========BTLOAD========" << endl;
				printErrorCode(200);
			}
		}
		else if(strcmp(ptr1, "PRINT_ITEMLIST") == 0){//if command is PRINT_ITEMLIST
			if(PRINT_ITEMLIST() == false){
				flog << "========PRINT_ITEMLIST========" << endl;
				printErrorCode(300);
			}
			continue;
		}
		else if(strcmp(ptr1, "PRINT_FPTREE") == 0){//if commnad is PRINT_FPTREE
			if(PRINT_FPTREE() == false){
				flog << "========PRINT_FPTREE========" << endl;
				printErrorCode(400);
			}
			continue;
		}
		else if(strcmp(ptr1,"PRINT_BPTREE") == 0){//if command is PRINT_BPTREE
			int bporder;
			ptr2 = strtok(NULL,"\t");
			if(ptr2 == nullptr){
				flog << "========PRINT_BPTREE========" << endl;
				printErrorCode(500);
				continue;
			}
			if(isdigit(ptr2[0]) != 0){//is ptr2 string?
				flog << "========PRINT_BPTREE========" << endl;
				printErrorCode(500);
				continue;
			}
			ptr3 = strtok(NULL,"\t");
			if(ptr3 == nullptr){
				flog << "========PRINT_BPTREE========" << endl;
				printErrorCode(500);
				continue;
			}
			if(isdigit(ptr3[0]) == 0){//is ptr2 string?
				flog << "========PRINT_BPTREE========" << endl;
				printErrorCode(500);
				continue;
			}
			bporder = atoi(ptr3);//char* -> int
			if(PRINT_BPTREE(ptr2, bporder) == false){
				flog << "========PRINT_BPTREE========" << endl;
				printErrorCode(500);
			}
		}
		else if(strcmp(ptr1, "PRINT_CONFIDENCE") == 0){//if command is PRINT_CONFIDENCE
			double confidence;
			ptr2 = strtok(NULL,"\t");
			if(ptr2 == nullptr){
				flog << "========PRINT_CONFIDENCE========" << endl;
				printErrorCode(600);
				continue;
			}
			if(isdigit(ptr2[0]) != 0){
				flog << "========PRINT_CONFIDENCE========" << endl;
				printErrorCode(600);
				continue;
			}
			ptr3 = strtok(NULL,"\t");
			if(ptr3 == nullptr){
				flog << "========PRINT_CONFIDENCE========" << endl;
				printErrorCode(600);
				continue;
			}
			if(isdigit(ptr3[0]) == 0){
				flog << "========PRINT_CONFIDENCE========" << endl;
				printErrorCode(600);
				continue;
			}
			confidence = atof(ptr3);
			if(PRINT_CONFIDENCE(ptr2,confidence) == false){
				flog << "========PRINT_CONFIDENCE========" << endl;
				printErrorCode(600);
			}
		}
		else if(strcmp(ptr1, "PRINT_RANGE") == 0){//if command is PRINT_RANGE
			ptr2 = strtok(NULL,"\t");
			if(ptr2 == nullptr){
				flog << "========PRINT_RANGE========" << endl;
				printErrorCode(700);
				continue;
			}
			if(isdigit(ptr2[0]) != 0){
				flog << "========PRINT_RANGE========" << endl;
				printErrorCode(700);
				continue;
			}
			ptr3 = strtok(NULL,"\t");
			if(ptr3 == nullptr){
				flog << "========PRINT_RANGE========" << endl;
				printErrorCode(700);
				continue;
			}
			if(isdigit(ptr3[0]) == 0){
				flog << "========PRINT_RANGE========" << endl;
				printErrorCode(700);
				continue;
			}
			ptr4 = strtok(NULL,"\t");
			if(ptr4 == nullptr){
				flog << "========PRINT_RANGE========" << endl;
				printErrorCode(700);
				continue;
			}
			if(isdigit(ptr4[0]) == 0){
				flog << "========PRINT_RANGE========" << endl;
				printErrorCode(700);
				continue;
			}
			int min, max;
			min = atoi(ptr3);
			max = atoi(ptr4);
			if(PRINT_RANGE(ptr2,min,max) == false){
				flog << "========PRINT_RANGE========" << endl;
				printErrorCode(700);
			}
		}
		else if(strcmp(ptr1, "SAVE") == 0){//if command is SAVE
			
		}
		else if(strcmp(ptr1,"EXIT") == 0){//if command is EXIT
			flog << "========EXIT========" << endl;
			printSuccessCode();
			return;
		}
		else{
			flog<<"Wrong Command!"<<endl;
			return;
		}
	}
	fin.close();
	return;
}

bool Manager::LOAD()
{
	if(fpgrowth->getTree()->getChildren().empty() == false){
		return false;
	}
	ifstream fread;
	fread.open("./market.txt");
	if(!fread.is_open()){
		return false;
	}
	char* data = new char[300];
	char* ptr = new char[50];
	std::set<string>compare;
	int count = 0;
	std::list<string> tmp;
	string str;
	while(!fread.eof()){//command is not nullptr
		fread.getline(data,300);
		if(!data[0]){
			return false;
		}
		count = 0;
		while(true){	
			if(count == 0){
				ptr = strtok(data,"\t");
				if(ptr == nullptr){
					break;
				}
				if(compare.count(ptr) != 0){//first input
					compare.insert(ptr);
					fpgrowth->createTable(0,ptr);//insert table
				}
				else{
					compare.insert(ptr);
					fpgrowth->createTable(1,ptr);//insert table
				}
				count++;
			}
			else if(count != 0){
				ptr = strtok(NULL,"\t");
				if(ptr == nullptr){
					break;
				}
				if(compare.count(ptr) != 0){
					fpgrowth->createTable(0,ptr);//insert table
					continue;
				}
				else{
					compare.insert(ptr);
					fpgrowth->createTable(1,ptr);//insert table
					continue;
				}	
			}
		}
	}
	fpgrowth->getHeaderTable()->descendingIndexTable();//descending the index table
	fread.close();
	fread.open("./market.txt");
	while(!fread.eof()){//for make the Tree
		fread.getline(data,300);
		if(data == nullptr){
			printErrorCode(100);
			return false;
		}
		count = 0;
		while(1){
			if(count == 0){
				ptr = strtok(data,"\t");
				if(ptr == nullptr){
					break;
				}
				count++;
			}
			else{
				ptr = strtok(NULL,"\t");
				if(ptr == nullptr){
					break;
				}
			}
			tmp.push_back(ptr);
		}
		fpgrowth->createFPtree(fpgrowth->getTree(),fpgrowth->getHeaderTable(),tmp,0);//insert Tree
		int TmpSize = tmp.size();
		for(int i = 0;i<TmpSize;i++){//data pop
			tmp.pop_back();
		}
	}
	fread.close();
	delete []data;//free data
	delete [] ptr;
	return true;
}




bool Manager::BTLOAD()
{
	ifstream fread;
	set<string> set;
	int count = 0;
	fread.open("./result.txt");
	if(!fread.is_open()){
		return false;
	}
	char* data = new char[300];
	int key = 0;
	char* ptr = new char[50];
	while(!fread.eof()){
		fread.getline(data,300);
		if(!data[0]){
			return false;
		}
		if(count == 0){
			ptr = strtok(data,"\t");
			key = atoi(ptr);//char* to int
			count++;
		}
		while(data){
			ptr = strtok(NULL,"\t");
			if(ptr == nullptr){
				break;
			}
			set.insert(ptr);//insert ptr to set
		}
		count = 0;
		bptree->Insert(key,set);//insert the value in bptree
		set.clear();
	}
	delete[] data;//free data
	delete [] ptr;
	return true;
}

bool Manager::PRINT_ITEMLIST() {
	if(fpgrowth->getHeaderTable()->getindexTable().empty() == true){
		return false;
	}
	fpgrowth->printList();
	return true;
}

bool Manager::PRINT_FPTREE() {
	if(fpgrowth->getTree()->getChildren().empty() == true){
		return false;
	}
	fpgrowth->printTree();
	return true;
}

bool Manager::PRINT_BPTREE(char* item, int min_frequency) {
	if(bptree->getRoot() == nullptr){
		return false;
	}
	if(bptree->printFrequency(item, min_frequency) == false){
		return false;
	}
	return true;
}

bool Manager::PRINT_CONFIDENCE(char* item, double rate) {
	int count = 0;//for existing
	if(bptree->getRoot() == nullptr){//if root is nullptr then, return
		return false;
	}
	BpTreeNode* CurNode = bptree->getRoot();
	while(CurNode->getMostLeftChild()){//get the dataNode
		CurNode = CurNode->getMostLeftChild();
	}
	while(CurNode){//CUrNode is not nullptr
		map<int,FrequentPatternNode*>::iterator it;
		it = CurNode->getDataMap()->begin();
		for(it;it!=CurNode->getDataMap()->end();it++){
			for(auto list:it->second->getList()){
				if(list.second.find(item) != list.second.end()){
					count += it->first;
				}
			}
		}
		CurNode = CurNode->getNext();
	}
	if(count == 0){//if data's count is 0
		return false;
	}
	double mul = count * rate;
	if(bptree->printConfidence(item,mul,rate) == false){//print confidence
		return false;
	}
	return true;
}

bool Manager::PRINT_RANGE(char* item, int start, int end) {
	if(bptree->getRoot() == nullptr){//if root is nullptr then, return
		return false;
	}
	if(bptree->printRange(item,start,end) == false){
		return false;
	}
	return true;
}

void Manager::printErrorCode(int n) {//ERROR CODE PRINT
	flog << "ERROR " << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

