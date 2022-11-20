#include "FPGrowth.h"


FPGrowth::~FPGrowth() {//clear the frequentPatterns
	frequenctPatterns.clear();
}

void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency) {
	//create FP Growth
	FPNode* RootNode = root;
	list<pair<int,string>> item;
	for(auto iter = item_array.begin();iter!=item_array.end();iter++){
		item.push_back(make_pair(0,iter->data()));
	}
	for(auto item_iter = item.begin();item_iter != item.end();item_iter++){
		item_iter->first = table->find_frequency(item_iter->second);
	}
	item.sort(greater<pair<int,string>>());//sort the items
	auto list = item.begin();
	int ListSize = item_array.size();

	while(ListSize>0){
		bool FPCheck = false;//for check the FPTree
		map<string,FPNode*>Cur = RootNode->getChildren();
		int FPSize = Cur.size();
		map<string,FPNode*>::iterator FP = Cur.begin();
		while(FPSize >0){//if FPSize >0?
			if(list->second.compare(FP->second->getItem()) == 0){//compare the value 
				//two component is same
				RootNode = FP->second;
				RootNode->updateFrequency(1);//up the Frequency 1
				FPCheck = true;//exist FPCheck
				break;
			}
			FP++;FPSize--;
		}
		if(!FPCheck){//FPCheck is 0
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
	//connect with table and FPTree
	FPNode* CurNode = table->getNode(item);
	if(CurNode->getNext() == nullptr){//if CurNode's next is nullptr
		CurNode->setNext(node);//set the node CurNode's next
		return;
	}
	//CurNode's next is not nullptr
	CurNode = CurNode->getNext();
	while(CurNode->getNext()){
		CurNode = CurNode->getNext();
	}
	CurNode->setNext(node);//set the node next to the CurNode
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

bool FPGrowth::printList() {//print List
	*fout << "========PRINT_ITEMLIST========"<<endl;
	*fout <<"Item	Frequency"<<endl;
	for(pair<int,string>iter : table->getindexTable()){
		*fout<<iter.second<<" ";
	 	*fout<<iter.first<<endl;
	}
	*fout<< "================================"<<endl<<endl;
	return true;
}
bool FPGrowth::printTree() {//print Tree
	table->ascendingIndexTable(); //ascending the indexTable
	*fout << "======= PRINT_FPTREE ========" << endl;
	*fout<< "{StandardItem.Frequency} (Path_Itme.Frequency)" << endl;
	list<pair<int, string> > indexTable = table->getindexTable();
	auto it = indexTable.begin();
	auto size = indexTable.size();
	while(size){//size >0
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
	*fout << "==========================" << endl<<endl;
	return true;
}
void FPGrowth::saveFrequentPatterns(){

}
