//#pragma once
#ifndef MANAGER_H
#define MANAGER_H
#include "FPGrowth.h"
#include "BpTree.h"
#include "cstring"

class Manager
{
private:
	char* cmd;
	FPGrowth* fpgrowth;
	BpTree* bptree;
public:
	Manager(int threshold, int bpOrder)	//constructor
	{
		remove("./log.txt");
		flog.open("./log.txt",std::ios_base::out|std::ios::app);
		fpgrowth = new FPGrowth(&flog,threshold);
		bptree = new BpTree(&flog, bpOrder);
	}


	~Manager()//destructor
	{
		if(flog.is_open()){
			flog.close();
		}
		free(fpgrowth);
		free(bptree);
		/* You must fill here */
	}

	ifstream fin;
	ofstream flog;
	

	void run(const char* command);
	bool LOAD();
	bool BTLOAD();
	
	bool PRINT_ITEMLIST();
	bool PRINT_FPTREE();

	bool PRINT_RANGE(char* item, int start, int end);
	bool PRINT_CONFIDENCE(char* item, double rate);
	bool PRINT_BPTREE(char* item, int min_frequency);


	void printErrorCode(int n);
	void printSuccessCode();

};

#endif
