#include "HeaderTable.h"

HeaderTable::~HeaderTable() {
	indexTable.clear();
	dataTable.clear();
}


void HeaderTable::insertTable(int frequency,const char* item) {
	if(frequency == 1){//if item is not exist, then new insert indexTable
		indexTable.push_back(make_pair(frequency, item));

		FPNode* NewNode = new FPNode();
		NewNode->setItem(item);
		NewNode->updateFrequency(1);//frequency update 1
		dataTable.insert(make_pair(item, NewNode));//insert the data in dataTable
		ascendingIndexTable();
		return;
	}
	auto index = indexTable.begin();
	int size = indexTable.size();
	
	while(size > 0){
		if(index->second.compare(item) == 0){
			auto data = dataTable.find(index->second);
			index->first++;
			data->second->updateFrequency(1);	
			return;
		}
		index++;size--;
	}
	descendingIndexTable();//descending index Table
}
int HeaderTable::find_frequency(string item){//for find the item's frequency
	int frequency = 0;
	list<pair<int,string>>::iterator iter;

	for(iter = indexTable.begin();iter != indexTable.end();iter++){
		if(iter->second.compare(item) == 0){
			frequency = iter->first;
			break;
		}
	}
	return frequency;
}
