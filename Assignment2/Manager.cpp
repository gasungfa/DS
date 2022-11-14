#include "Manager.h"
#include<fstream>
#include<set>
#include<list>

void Manager::run(const char* command)
{
	fin.open(command);
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
    	char* ptr1 = strtok(text, " ");
		char* ptr2 = new char[100];
		char* ptr3 = new char[100];
		char* ptr4 = new char[100];
		if(strcmp(ptr1,"LOAD") == 0){
			if(strtok(NULL," ") != NULL){
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
		else if(strcmp(ptr1, "BTLOAD") == 0){
			if(strtok(NULL," ") != NULL){
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
		else if(strcmp(ptr1, "PRINT_ITEMLIST") == 0){
			if(PRINT_ITEMLIST() == false){
				flog << "========PRINT_ITEMLIST========" << endl;
				printErrorCode(300);
			}
			continue;
		}
		else if(strcmp(ptr1, "PRINT_FPTREE") == 0){
			if(PRINT_FPTREE() == false){
				flog << "========PRINT_FPTREE========" << endl;
				printErrorCode(400);
			}
			continue;
		}
		else if(strcmp(ptr1,"PRINT_BPTREE") == 0){
			int bporder;
			ptr2 = strtok(NULL," ");
			if(ptr2 == nullptr){
				flog << "========PRINT_BPTREE========" << endl;
				printErrorCode(500);
				continue;
			}
			ptr3 = strtok(NULL," ");
			if(ptr3 == nullptr){
				flog << "========PRINT_BPTREE========" << endl;
				printErrorCode(500);
				continue;
			}
			bporder = atoi(ptr3);
			if(PRINT_BPTREE(ptr2, bporder) == false){
				flog << "========PRINT_BPTREE========" << endl;
				printErrorCode(500);
			}
		}
		else if(strcmp(ptr1, "PRINT_CONFIDENCE") == 0){
			double confidence;
			ptr2 = strtok(NULL," ");
			if(ptr2 == nullptr){
				flog << "========PRINT_CONFIDENCE========" << endl;
				printErrorCode(600);
				continue;
			}
			ptr3 = strtok(NULL," ");
			if(ptr3 == nullptr){
				flog << "========PRINT_CONFIDENCE========" << endl;
				printErrorCode(600);
				continue;
			}
			if(atof(ptr3) == 0){
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
	while(!fread.eof()){
		fread.getline(data,300);
		if(data == nullptr){
			printErrorCode(100);
			return false;
		}
		count = 0;
		while(true){	
			if(count == 0){
				ptr = strtok(data,"\t");
				if(ptr == nullptr){
					break;
				}
				if(compare.count(ptr) != 0){
					compare.insert(ptr);
					fpgrowth->createTable(0,ptr);
				}
				else{
					compare.insert(ptr);
					fpgrowth->createTable(1,ptr);
				}
				count++;
			}
			else if(count != 0){
				ptr = strtok(NULL,"\t");
				if(ptr == nullptr){
					break;
				}
				if(compare.count(ptr) != 0){
					fpgrowth->createTable(0,ptr);
					continue;
				}
				else{
					compare.insert(ptr);
					fpgrowth->createTable(1,ptr);
					continue;
				}	
			}
		}
	}
	fpgrowth->getHeaderTable()->descendingIndexTable();
	fread.close();
	fread.open("./market.txt");
	while(!fread.eof()){
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
		fpgrowth->createFPtree(fpgrowth->getTree(),fpgrowth->getHeaderTable(),tmp,0);
		int TmpSize = tmp.size();
		for(int i = 0;i<TmpSize;i++){
			tmp.pop_back();
		}
	}
	fread.close();
	delete []data;
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
		if(data == nullptr){
			printErrorCode(200);
			return false;
		}
		if(count == 0){
			//fread>>key;
			ptr = strtok(data,"\t");
			key = atoi(ptr);
			count++;
		}
		while(data){
			ptr = strtok(NULL,"\t");
			if(ptr == nullptr){
				break;
			}
			set.insert(ptr);
		}
		count = 0;
		bptree->Insert(key,set);
		set.clear();
	}
	delete[] data;
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
	int count = 0;
	if(bptree->getRoot() == nullptr){
		return false;
	}
	BpTreeNode* CurNode = bptree->getRoot();
	while(CurNode->getMostLeftChild()){
		CurNode = CurNode->getMostLeftChild();
	}
	while(CurNode){
		map<int,FrequentPatternNode*>::iterator it;
		it = CurNode->getDataMap()->begin();
		for(it;it!=CurNode->getDataMap()->end();it++){
			for(auto list:it->second->getList()){
				if(list.second.find(item) != list.second.end()){
					count++;
				}
			}
		}
		CurNode = CurNode->getNext();
	}
	if(count == 0){
		return false;
	}
	double mul = count * rate;
	if(bptree->printConfidence(item,mul,rate) == false){
		return false;
	}
	return true;
}

bool Manager::PRINT_RANGE(char* item, int start, int end) {
	
}

void Manager::printErrorCode(int n) {//ERROR CODE PRINT
	flog << "ERROR " << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

