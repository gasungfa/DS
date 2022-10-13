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

	Stack()//set the value
	{
		size = MAXVALUE;
		values = new T[size];
		top = -1;
	}
	~Stack()//delete the stack's data
	{
		delete[] values;
	}

	void push(T value)//insert data
	{
		if(!isFull())
			values[++top] = value;
		else 
			return;
	}

	void pop()//delete the data
	{
		if(!empty())
			top--;
		else 
			return;
	}

	T Top()//stack's top data return
	{
		if(!empty())
			return values[top];
		else
			return '\0';
	}

	bool empty()//stack is empty?
	{
		if(top < 0)
			return true;
		else 
			return false;
	}

	bool isFull()//stack is Full?
	{
		if(top+1 == size) 
			return true;
		else 
			return false;
	}
};

#endif
