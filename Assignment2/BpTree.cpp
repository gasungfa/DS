#include "BpTree.h"

bool BpTree::Insert(int key, set<string> set) {
	FrequentPatternNode* NewNode = new FrequentPatternNode();
	NewNode->setFrequency(set.size());
	NewNode->InsertList(set);
	if(root == nullptr){
		root = new BpTreeDataNode();
		root->insertDataMap(key,NewNode);
		return true;
	}
	BpTreeNode* searchNode = searchDataNode(key);
	if(searchNode != nullptr){
		map<int,FrequentPatternNode*>::iterator iter;
		iter = searchNode->getDataMap()->begin();
		for(iter;iter!= searchNode->getDataMap()->end();iter++){
			if(iter->first == key){
				iter->second->InsertList(set);
				break;
			}
		}
		return true;
	}
	BpTreeNode* CurNode = root;
	while(CurNode->getMostLeftChild()){
		map<int,BpTreeNode*> ::iterator index;
		index = CurNode->getIndexMap()->begin();
		for(index;index != CurNode->getIndexMap()->end();index++){
			if(index->first > key){
				if(index == CurNode->getIndexMap()->begin()){
					CurNode = CurNode->getMostLeftChild();
					break;
				}
				CurNode = (--index)->second;
				break;
			}
			else if(index == --(CurNode->getIndexMap()->end())){
				CurNode = index->second;
				break;
			}
		}
	}
	CurNode->insertDataMap(key,NewNode);
	if(excessDataNode(CurNode) == true){
		splitDataNode(CurNode);
	}
	return true;
}

BpTreeNode* BpTree::searchDataNode(int n) {
	BpTreeNode* pCur = root;
	if(pCur == nullptr){
		return nullptr;
	}
	while(pCur->getMostLeftChild() != nullptr){
		map<int,BpTreeNode*>::iterator it = pCur->getIndexMap()->begin();
		for(it;it != pCur->getIndexMap()->end();it++){
			if(it->first > n){
				if(it == pCur->getIndexMap()->begin()){
					pCur = pCur->getMostLeftChild();
					break;
				}
				pCur = (--it)->second;
				break;
			}
			else if(it->first == n){
				pCur = it->second;
				break;
			}
			else if(it == --(pCur->getIndexMap()->end())){
				pCur = it->second;
				break;
			}
		}
	}
	map<int,FrequentPatternNode*>::iterator data;
	data = pCur->getDataMap()->begin();
	for(data;data!= pCur->getDataMap()->end();data++){
		if(data->first == n){
			return pCur;
		}
	}
	return nullptr;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	BpTreeNode* LeftChild = new BpTreeDataNode();
	if(pDataNode == root){
		map<int,FrequentPatternNode*>::iterator data = pDataNode->getDataMap()->begin();
		BpTreeNode* NewIndex = new BpTreeIndexNode();
		int bpsize = 1;
		while(bpsize != (order/2) +1){
			LeftChild->insertDataMap(data->first,data->second);
			pDataNode->getDataMap()->erase(data);
			data = pDataNode->getDataMap()->begin();
			bpsize++;
		}
		root = NewIndex;
		NewIndex->setMostLeftChild(LeftChild);
		NewIndex->insertIndexMap(data->first,pDataNode);
		LeftChild->setNext(pDataNode);
		pDataNode->setPrev(LeftChild);
		LeftChild->setParent(NewIndex);
		pDataNode->setParent(NewIndex);
		return;
	}
	BpTreeNode* Parent = pDataNode->getParent();
	map<int,FrequentPatternNode*>::iterator data = pDataNode->getDataMap()->begin();
	int bpsize = 1;
	while(bpsize != (order/2) +1){
		LeftChild->insertDataMap(data->first,data->second);
		pDataNode->getDataMap()->erase(data);
		data = pDataNode->getDataMap()->begin();
		bpsize++;
	}
	Parent->insertIndexMap(data->first,pDataNode);
	if(Parent->getMostLeftChild() == pDataNode){
		Parent->setMostLeftChild(LeftChild);
		LeftChild->setParent(Parent);
	}
	map<int,BpTreeNode*>::iterator index = Parent->getIndexMap()->begin();
	while(index != Parent->getIndexMap()->end()){
		if(index->second == pDataNode){
			index->second= LeftChild;
			LeftChild->setParent(Parent);
			break;
		}
		index++;
	}
	if(pDataNode->getPrev()){
		pDataNode->getPrev()->setNext(LeftChild);
		LeftChild->setPrev(pDataNode->getPrev());
	}
	LeftChild->setNext(pDataNode);
	pDataNode->setPrev(LeftChild);
	if(excessIndexNode(Parent) == true) splitIndexNode(Parent);
	return;
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	if(!pIndexNode->getParent()){//parent is exist
		BpTreeNode* LeftChild = new BpTreeIndexNode();
		BpTreeNode* ParentNode = new BpTreeIndexNode();
		map<int,BpTreeNode*>::iterator index = pIndexNode->getIndexMap()->begin();
		int bpsize = 1;
		while(bpsize != (order/2) +1){
			LeftChild->insertIndexMap(index->first,index->second);
			pIndexNode->getIndexMap()->erase(index);
			index = pIndexNode->getIndexMap()->begin();
			bpsize++;
		}
		root = ParentNode;
		ParentNode->setMostLeftChild(LeftChild);
		LeftChild->setParent(ParentNode);
		LeftChild->setMostLeftChild(pIndexNode->getMostLeftChild());
		pIndexNode->setParent(ParentNode);
		pIndexNode->setMostLeftChild(index->second);
		index->second->setParent(pIndexNode);
		ParentNode->insertIndexMap(index->first, pIndexNode);
		pIndexNode->getIndexMap()->erase(index);
		return;
	}
	BpTreeNode* LeftChild = new BpTreeIndexNode();
	BpTreeNode* parent = pIndexNode->getParent();
	map<int,BpTreeNode*>::iterator index = pIndexNode->getIndexMap()->begin();
	int bpsize = 1;
	while(bpsize != (order/2) +1){
		LeftChild->insertIndexMap(index->first,index->second);
		pIndexNode->getIndexMap()->erase(index);
		index = pIndexNode->getIndexMap()->begin();
		bpsize++;
	}
	//index->second->setParent(LeftChild);
	LeftChild->setMostLeftChild(pIndexNode->getMostLeftChild());
	pIndexNode->getMostLeftChild()->setParent(LeftChild);
    parent->insertIndexMap(index->first,pIndexNode);
	pIndexNode->setMostLeftChild(index->second);
	pIndexNode->getIndexMap()->erase(pIndexNode->getIndexMap()->begin());
	if(parent->getMostLeftChild() == pIndexNode){
		parent->setMostLeftChild(LeftChild);
		LeftChild->setParent(parent);
	}
	map<int,BpTreeNode*>::iterator PIndex;
	PIndex = parent->getIndexMap()->begin();
	for(PIndex;PIndex!= parent->getIndexMap()->end();PIndex++){
		if(PIndex->second == pIndexNode){
			PIndex->second = LeftChild;
			LeftChild->setParent(parent);
			break;
		}
	}
	if(excessIndexNode(parent) == true){
		splitIndexNode(parent);
	}
	return;
}
bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}


bool BpTree::printConfidence(string item, double item_frequency, double min_confidence)
{
	int AllFrequency = item_frequency/min_confidence;
	int count = 0;
	BpTreeNode* CurNode = root;
	while(CurNode->getMostLeftChild()){
		CurNode = CurNode->getMostLeftChild();
	}
	multimap<int,FrequentPatternNode*> subset;
	while(CurNode){
		map<int,FrequentPatternNode*>::iterator it = CurNode->getDataMap()->begin();
		for(it;it!= CurNode->getDataMap()->end();it++){
			if(it->first > item_frequency){
				for(auto list:it->second->getList()){
					if(list.second.find(item) != list.second.end()){
						subset.insert(make_pair(it->first,it->second));
						count++;
					}
				}
			}
		}
		CurNode = CurNode->getNext();
	}
	if(count == 0){
		return false;
	}
	*fout << "========"<<"PRINT_CONFIDENCE"<<"========"<<endl;
	*fout << "FrequentPattern "<<"Frequency"<<"      "<<"Confidence"<<endl;
	multimap<int,FrequentPatternNode*>::iterator sub = subset.begin();
	for(sub;sub!= subset.end();sub++){
		for(auto list:sub->second->getList()){
			*fout<<"{";
			set<string>CurPattern = list.second;
			for (set<string>::iterator it = CurPattern.begin(); it != CurPattern.end();) {
				string temp = *it++;
				*fout << temp;
				if (it == CurPattern.end()) {
					*fout << "} ";
					break;
				}
				*fout << ", ";
			}
			*fout<<sub->first<< " ";
			break;
		}
		*fout<<(double)sub->first/AllFrequency<<endl;	
	}
	return true;
}
bool BpTree::printFrequency(string item, int min_frequency)//print winratio in ascending order
{
	int count =0;
	BpTreeNode* CurNode= root;
	while(CurNode->getMostLeftChild()){
		CurNode = CurNode->getMostLeftChild();
	}
	while(CurNode){
		map<int,FrequentPatternNode*>::iterator it = CurNode->getDataMap()->begin();
		for(it;it!= CurNode->getDataMap()->end();it++){
			if(it->first < min_frequency) continue;
			for(auto list:it->second->getList()){
				if(list.second.find(item) != list.second.end()){
					if(count == 0){
						*fout << "========"<<"PRINT_BPTREE"<<"========"<<endl;
						*fout << "FrequentPattern" <<"        "<<"Frequency"<<endl;
						count++;
					}
					*fout<<"{";
					set<string>CurPattern = list.second;
					for (set<string>::iterator it = CurPattern.begin(); it != CurPattern.end();) {
						string temp = *it++;
						*fout << temp;
						if (it == CurPattern.end()) {
							*fout << "} ";
							break;
						}
						*fout << ", ";
					}
					*fout<<it->first<<endl;
					//printFrequentPatterns(list.second,item);
				}
			}
		}
        CurNode=CurNode->getNext();
	}
	if(count == 0){
		return false;
	}
	*fout << "=========================="<<endl<<endl;
	return true;
}
bool BpTree::printRange(string item, int min, int max) {

	return true;
}
void BpTree::printFrequentPatterns(set<string> pFrequentPattern, string item) {
	*fout << "{";
	set<string> curPattern = pFrequentPattern;
	curPattern.erase(item);
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) {
		string temp = *it++;
		if (temp != item) *fout << temp;
		if (it == curPattern.end()) {
			*fout << "} ";
			break;
		}
		*fout << ", ";
	}
}
