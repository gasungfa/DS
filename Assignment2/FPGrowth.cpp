#include "FPGrowth.h"


FPGrowth::~FPGrowth() {

}

void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency) {
	FPNode* RootNode = root;
	list<pair<int,string>> item;
	auto iter = item_array.begin();
	for(iter;iter!=item_array.end();iter++){
		item.push_back(make_pair(0,iter->data()));
	}
	auto item_iter = item.begin();
	for(item_iter;item_iter != item.end();item_iter++){
		item_iter->first = table->find_frequency(item_iter->second);
	}
	item.sort(greater<pair<int,string>>());
	//auto list = item_array.begin();
	auto list = item.begin();
	int ListSize = item_array.size();

	while(ListSize>0){
		map<string,FPNode*>Cur = RootNode->getChildren();
		map<string,FPNode*>::iterator FP = Cur.begin();
		bool FPCheck = false;
		int FPSize = Cur.size();
		while(FPSize >0){
			if(list->second.compare(FP->second->getItem()) == 0){
				RootNode = FP->second;
				RootNode->updateFrequency(1);
				FPCheck = true;
				break;
			}
			FP++;FPSize--;
		}
		if(FPCheck == false){
			FPNode* NewNode = new FPNode();
			NewNode->setParent(RootNode);
			string str = list->second;
			NewNode->setItem(str.c_str());
			NewNode->updateFrequency(1);
			RootNode->pushchildren(list->second, NewNode);
			connectNode(table, list->second, NewNode);//table <-> FPTree
			RootNode = NewNode;
		}
		list++;ListSize--;
	}
	return;
}

void FPGrowth::connectNode(HeaderTable* table, string item, FPNode* node) {
	FPNode* CurNode = table->getNode(item);
	if(CurNode->getNext() == nullptr){
		CurNode->setNext(node);
		return;
	}
	CurNode = CurNode->getNext();
	while(CurNode->getNext()){
		CurNode = CurNode->getNext();
	}
	CurNode->setNext(node);
	return;
}

bool FPGrowth::contains_single_path(FPNode* pNode) {
	if (pNode->getChildren().size() == 0) return true;
	else if (pNode->getChildren().size() > 1) return false;
	return contains_single_path(pNode->getChildren().begin()->second);
}

map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable* pTable, FPNode* pTree) {

	return {};
}



void FPGrowth::powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* ptr, int depth) {
	if (data.size() == depth) {
		set<string> set; set.insert(item);
		for (int i = 0; i < data.size(); i++) { if (ptr[i] == 1) set.insert(data[i]); }
		FrequentPattern->insert(make_pair(set, frequency)); return;
	}
	ptr[depth] = 1;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
	ptr[depth] = 0;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
}

bool FPGrowth::printList() {
	//std::list<pair<int,string>>::iterator it = table->getindexTable().begin();
	*fout << "========PRINT_ITEMLIST========"<<endl;
	*fout <<"Item	Frequency"<<endl;
	for(pair<int,string>iter : table->getindexTable()){
		*fout<<iter.second<<" ";
	 	*fout<<iter.first<<endl;
	}
	*fout<< "================================"<<endl;
	return true;
}
bool FPGrowth::printTree() {
	table->ascendingIndexTable(); //ascending sort for lowest rank node
	*fout << "======= PRINT_FPTREE ========" << endl;
	*fout<< "{StandardItem.Frequency} (Path_Itme.Frequency)" << endl;
	// if (fpTree->getChildren().empty() == true){
	// 	return false;
	// }
	list<pair<int, string> > indexTable = table->getindexTable();
	auto it = indexTable.begin();
	auto size = indexTable.size();
	while(size){
		if (it->first >= threshold) {
			FPNode* CurNode = table->getNode(it->second)->getNext();
			*fout << "{" << it->second << '.' << it->first << "}" << endl; //all frequency in item

			FPNode* NextNode = CurNode; //checking all node
			while (NextNode != nullptr)
			{
				while (CurNode != fpTree) // if root?
				{
					*fout << "(" << CurNode->getItem() << "." << CurNode->getFrequency() << ") ";
					CurNode = CurNode->getParent();
				}
				*fout << endl;
				NextNode = NextNode->getNext();
				CurNode = NextNode;
			}
		}
		it++;size--;
	}
	*fout << "==========================" << endl;
	return true;
}
void FPGrowth::saveFrequentPatterns(){

}
