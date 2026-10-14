#ifndef QUEUE_H
#define QUEUE_H

#include "SinglyLinkedList.h"

class Queue {
private:
    SinglyLinkedList list;
    
public:
    Queue();
    ~Queue();
    
    int getAt(int index) const;
    void push(int value);
    int pop();
    int getFront() const;
    bool isEmpty() const;
    int getSize() const;
    void print() const;
};

#endif