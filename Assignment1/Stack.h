#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

#include<iostream>
#define MAXVALUE 2
template<class T> class Stack
{
public:
	int top;
	int size;
	T *values;

	Stack()
	{
		size = MAXVALUE;
		values = new T[size];
		top = -1;
	}
	~Stack()
	{
		delete[] values;
	}

	void push(T value)
	{
		if(!isFull())
			values[++top] = value;
		else 
			return;
	}

	void pop()
	{
		if(!empty())
			top--;
		else 
			return;
	}

	T Top()
	{
		if(!empty())
			return values[top];
		else
			return '\0';
	}

	bool empty()
	{
		if(top < 0)
			return true;
		else 
			return false;
	}

	bool isFull()
	{
		if(top+1 == size) 
			return true;
		else 
			return false;
	}
};




// class Stack
// {
// private:
//     // class StackNode
//     // {
//     // public:
//     //     char Data;
//     //     StackNode* pNext;
//     //     StackNode(){
//     //         pNext = nullptr;
//     //     }
//     //     StackNode* GetNext(){return pNext;}
//     //     char GetData(){return this->Data;}
//     //     void SetNext(StackNode* next){this->pNext = next;}
//     //     void SetData(char data){Data = data;}
//     // };
// private:
//     StackNode* top;

// public:
//     Stack(){
//         top = nullptr;
//     }
//     StackNode* GetNext(){return top->pNext;};
//     char GetData(){return top->Data;}
//     void SetNext(StackNode* next){top->pNext;}
//     void SetData(char data){top->Data = data;}
    
//     void Push(char data){
//         if(IsEmpty() == true){
//             SetData(data);
//             return;
//         }
//         else{
//             StackNode* CurNode = top;
//             while(CurNode->GetNext()){
//                 CurNode = CurNode->GetNext();
//             }
//             StackNode* NewNode = new StackNode();
//             NewNode->SetData(data);
//             CurNode->SetNext(NewNode);
//             return;
//         }
//     }
//     /// <summary>
//     /// pop(remove) the last-in data from this stack and queue
//     /// </summary>
//     void Pop(){
//         if(IsEmpty() == true){
//             return;
//         }
//         else{
//             StackNode* CurNode = top;
//             StackNode* PrevNode = new StackNode();
//             while(CurNode->GetNext()){
//                 PrevNode = CurNode;
//                 CurNode = CurNode->GetNext();
//             }
//             PrevNode->SetNext(nullptr);
//             free(CurNode);
//             return;
//         }
//     }
//     /// <summary>
//     /// get the last-in data of this stack and queue
//     /// </summary>
//     /// 
//     /// <returns>
//     /// the last-in data of this stack and queue
//     /// </returns>
//     char Top(){
//         if(IsEmpty() == true){
//             return -1;
//         }
//         else{
//             StackNode* CurNode = top;
//             while(CurNode->GetNext()){
//                 CurNode = CurNode->GetNext();
//             }
//             return CurNode->GetData();
//         }
//     }
//     /// <summary>
//     /// check whether this stack and queue is empty or not.
//     /// </summary>
//     ///
//     /// <returns>
//     /// true if this stack and queue is empty.
//     /// false otherwise.
//     /// </returns>
//     bool IsEmpty(){
//         if(top == nullptr){
//             return true;
//         }
//         return false;
//     }
// };

#endif
