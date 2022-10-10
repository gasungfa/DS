#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL    0
#endif
#define MAXVALUE 300
#include <iostream>
#include<string>
#include<cstring>

class Queue
{
public:
    int front;
    int rear;
    int size;
    std::string* name;
    std::string* num;

    Queue(){
        size = MAXVALUE;
        name = new std::string[size];
        num = new std::string[size];
        front = 0;
        rear = 0;
    }
    ~Queue(){
        delete[] name;
        delete[] num;
    }
    bool isFull(){
        if((rear+1)%size == front){
            return true;
        }
        else{
            return false;
        }
    }
    bool empty(){
        if(rear == front){
            return true;
        }
        else{
            return false;
        }
    }
    std::string EndValue_name(){
        return name[front];
    }
    std::string EndValue_num(){
        return num[front];
    }
    void push(std::string filename,std::string unique_num){
        if(!isFull()){
            name[rear] = filename;
            num[rear] = unique_num;
            rear = (rear+1)%size;
        }
        else{
            return;
            //Queue Full
        }
    }
    void pop(){
        if(!empty()){
            front = (front+1) %size;
        }
        else{
            return;
            //Queue empty
        }
    }
};

#endif
