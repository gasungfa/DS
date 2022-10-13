#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL    0
#endif
#define VALUE 256*256
#include <iostream>
#include<string>
#include<cstring>

class RawQueue//for RawReader.h
{
public:
    int front;
    int rear;
    int size;
    unsigned char* light;

    RawQueue(){//set the value
        size = VALUE;
        light = new unsigned char[VALUE];
        front = 0;
        rear = 0;
    }
    ~RawQueue(){
        delete[]light;
    }
    bool isFull(){//if queue is Full?
        if((rear+1)%size == front){
            return true;
        }
        else{
            return false;
        }
    }
    bool empty(){//if queue is empty?
        if(rear == front){
            return true;
        }
        else{
            return false;
        }
    }
    void push(char Light){//insert data in queue
        if(!isFull()){
            light[rear] = Light;
            rear = (rear+1)%size;
        }
        else{
            return;
            //Queue Full
        }
    }
    unsigned char pop(){//delete the data in queue
        if(!empty()){
            front = (front+1) %size;
            return light[front];
        }
        else{
            return '\0';
        }
    }
};



#endif