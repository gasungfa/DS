#include "BpTree.h"

bool BpTree::Insert(int key, set<string> set) {//insert BpTreeNode
	FrequentPatternNode* NewNode = new FrequentPatternNode();//new node for FrequentPatternNode
	NewNode->setFrequency(set.size());//NewNode's frequency is set.size()
	NewNode->InsertList(set);//NewNode's List is set<string>
	if(root == nullptr){//if root is nullptr
		root = new BpTreeDataNode();
		root->insertDataMap(key,NewNode);//insert
		return true;
	}
	BpTreeNode* searchNode = searchDataNode(key);
	if(searchNode != nullptr){//if key is exist in map then, insert the corresponding node
		map<int,FrequentPatternNode*>::iterator iter;
		iter = searchNode->getDataMap()->begin();
		for(iter;iter!= searchNode->getDataMap()->end();iter++){
			if(iter->first == key){//if key's value is same with the map
				iter->second->InsertList(set);//insert
				break;
			}
		}
		return true;
	}
	//key is not exist in the map node
	BpTreeNode* CurNode = root;
	while(CurNode->getMostLeftChild()){//Is CurNode's MostLeftChild exist?
		map<int,BpTreeNode*> ::iterator index;
		index = CurNode->getIndexMap()->begin();
		for(index;index != CurNode->getIndexMap()->end();index++){
			if(index->first > key){//Is index's key bigger than key?
				if(index == CurNode->getIndexMap()->begin()){//if map data is same with CurNode's Index
					CurNode = CurNode->getMostLeftChild();
					break;
				}
				CurNode = (--index)->second;
				break;
			}
			else if(index == --(CurNode->getIndexMap()->end())){//Is index reach end node?
				CurNode = index->second;
				break;
			}
		}
	}
	CurNode->insertDataMap(key,NewNode);//Insert DataMap
	if(excessDataNode(CurNode) == true){//Is DataNode's count > bporder?
		splitDataNode(CurNode);//then, split
	}
	return true;
}

BpTreeNode* BpTree::searchDataNode(int n) {//for searching DataNode
	BpTreeNode* pCur = root;
	if(pCur == nullptr){//if pCur is null, then return
		return nullptr;
	}
	while(pCur->getMostLeftChild() != nullptr){
		map<int,BpTreeNode*>::iterator it = pCur->getIndexMap()->begin();
		for(it;it != pCur->getIndexMap()->end();it++){
			if(it->first > n){//it's key is bigger than n
				if(it == pCur->getIndexMap()->begin()){
					pCur = pCur->getMostLeftChild();
					break;
				}
				pCur = (--it)->second;
				break;
			}
			else if(it->first == n){//it's key is same with n
				pCur = it->second;
				break;
			}
			else if(it == --(pCur->getIndexMap()->end())){//it is reaching end
				pCur = it->second;
				break;
			}
		}
	}
	map<int,FrequentPatternNode*>::iterator data;
	data = pCur->getDataMap()->begin();
	for(data;data!= pCur->getDataMap()->end();data++){
		if(data->first == n){//if data's key is same with n
			return pCur;
		}
	}
	return nullptr;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {//for split when, DataNode > bporder
	BpTreeNode* LeftChild = new BpTreeDataNode();
	if(pDataNode == root){//pDataNode is DataNode not indexNode
		map<int,FrequentPatternNode*>::iterator data = pDataNode->getDataMap()->begin();
		BpTreeNode* NewIndex = new BpTreeIndexNode();
		int bpsize = 1;
		while(bpsize != (order/2) +1){//if order =3 , then bpsize is 2
			LeftChild->insertDataMap(data->first,data->second);
			pDataNode->getDataMap()->erase(data);
			data = pDataNode->getDataMap()->begin();
			bpsize++;
		}
		//link each node
		root = NewIndex;
		NewIndex->setMostLeftChild(LeftChild);
		NewIndex->insertIndexMap(data->first,pDataNode);
		LeftChild->setNext(pDataNode);
		pDataNode->setPrev(LeftChild);
		LeftChild->setParent(NewIndex);
		pDataNode->setParent(NewIndex);
		return;
	}
	//index node is exist
	BpTreeNode* Parent = pDataNode->getParent();
	map<int,FrequentPatternNode*>::iterator data = pDataNode->getDataMap()->begin();
	int bpsize = 1;
	while(bpsize != (order/2) +1){//if order =3 , then bpsize is 2
		LeftChild->insertDataMap(data->first,data->second);
		pDataNode->getDataMap()->erase(data);
		data = pDataNode->getDataMap()->begin();
		bpsize++;
	}
	Parent->insertIndexMap(data->first,pDataNode);
	if(Parent->getMostLeftChild() == pDataNode){//if parentNode's leftchild is pDataNode
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
	if(pDataNode->getPrev()){//Is pDataNode's prev exist?
		pDataNode->getPrev()->setNext(LeftChild);
		LeftChild->setPrev(pDataNode->getPrev());
	}
	LeftChild->setNext(pDataNode);
	pDataNode->setPrev(LeftChild);
	if(excessIndexNode(Parent) == true) splitIndexNode(Parent);//IndexNode's count is over bporder?
	return;
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {//split IndexNode when, count > bporder
	if(!pIndexNode->getParent()){//Is parent exist?
		BpTreeNode* LeftChild = new BpTreeIndexNode();
		BpTreeNode* ParentNode = new BpTreeIndexNode();
		map<int,BpTreeNode*>::iterator index = pIndexNode->getIndexMap()->begin();
		int bpsize = 1;
		while(bpsize != (order/2) +1){//if order =3 , then bpsize is 2
			LeftChild->insertIndexMap(index->first,index->second);
			pIndexNode->getIndexMap()->erase(index);
			index = pIndexNode->getIndexMap()->begin();
			bpsize++;
		}
		//link each node
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
	while(bpsize != (order/2) +1){//if order =3 , then bpsize is 2
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
	if(excessIndexNode(parent) == true){//IndexNode's count is over bporder?
		splitIndexNode(parent);//then, split index Node
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
	int AllFrequency = 0;//item_frequency/min_confidence;
	int count = 0;
	BpTreeNode* CurNode = root;
	while(CurNode->getMostLeftChild()){//search left dataNode
		CurNode = CurNode->getMostLeftChild();
	}
	map<int,FrequentPatternNode*> subset;
	while(CurNode){//when curNode is not nullptr
		map<int,FrequentPatternNode*>::iterator it = CurNode->getDataMap()->begin();
		for(it;it!= CurNode->getDataMap()->end();it++){
			if(it->first > item_frequency){//if it's key is bigger than item_frequency
				for(auto list:it->second->getList()){
					if(list.second.find(item) != list.second.end()){
						subset.insert(make_pair(it->first,it->second));//insert data in subset
						count++;
					}
				}
			}
			for(auto list2:it->second->getList()){//find AllFrequency
				if(list2.second.find(item) != list2.second.end()){
					AllFrequency += it->first;
				}
			}
		}
		CurNode = CurNode->getNext();
	}
	if(count == 0){//if data's count is 0
		return false;
	}
	//print
	*fout << fixed;
	fout->precision(2);
	*fout << "========"<<"PRINT_CONFIDENCE"<<"========"<<endl;
	*fout << "FrequentPattern "<<"Frequency"<<"      "<<"Confidence"<<endl;
	map<int,FrequentPatternNode*>::iterator it = subset.begin();
	for(it;it!= subset.end();it++){
		for(auto list:it->second->getList()){
			if(list.second.find(item) != list.second.end()){
				printFrequentPatterns(list.second);
				*fout<<it->first << " ";
				*fout<<(double)it->first/AllFrequency<<endl;
			}
		}
	}
	*fout << "=========================="<<endl<<endl;
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
					printFrequentPatterns(list.second);
					*fout<<it->first<<endl;
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
bool BpTree::printRange(string item, int min, int max) {//print item, item's frequency is bigger than min and smaller than max
	int count = 0;
	BpTreeNode* CurNode = root;
	while(CurNode->getMostLeftChild()){
		CurNode = CurNode->getMostLeftChild();
	}
	while(CurNode){
		map<int,FrequentPatternNode*>::iterator it = CurNode->getDataMap()->begin();
		for(it;it!= CurNode->getDataMap()->end();it++){
			if(it->first >= min){
				for(auto list:it->second->getList()){
					if(list.second.find(item) != list.second.end()){
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
	*fout << "========"<<"PRINT_RANGE"<<"========"<<endl;
	*fout << "FrequentPattern "<<"Frequency"<<endl;
	BpTreeNode*rootNode = root;
	while(rootNode->getMostLeftChild()){
		rootNode = rootNode->getMostLeftChild();
	}
	while(rootNode){
		map<int,FrequentPatternNode*>::iterator it = rootNode->getDataMap()->begin();
		for(it;it!= rootNode->getDataMap()->end();it++){
			if(it->first <= max && it->first >= min){
				for(auto list:it->second->getList()){
					if(list.second.find(item) != list.second.end()){
						printFrequentPatterns(list.second);
						*fout<<it->first<<endl;
					}
				}
			}
		}
		rootNode = rootNode->getNext();
	}
	*fout << "=========================="<<endl<<endl;
	return true;
}
void BpTree::printFrequentPatterns(set<string> pFrequentPattern) {//print FrequentPatterns
	*fout << "{";
	set<string> curPattern = pFrequentPattern;
	for (set<string>::iterator it = curPattern.begin(); it != curPattern.end();) {
		string temp = *it++;
		*fout << temp;
		if (it == curPattern.end()) {
			*fout << "} ";
			break;
		}
		*fout << ", ";
	}
}
