#include "HeaderTable.h"

HeaderTable::~HeaderTable() {

}


void HeaderTable::insertTable(int frequency,const char* item) {
	if(frequency == 1){
		indexTable.push_back(make_pair(frequency, item));

		FPNode* NewNode = new FPNode();
		NewNode->setItem(item);
		NewNode->updateFrequency(1);
		dataTable.insert(make_pair(item, NewNode));
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
	descendingIndexTable();
}
int HeaderTable::find_frequency(string item){
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
