#ifndef STACK_H
#define STACK_H

#include "SinglyLinkedList.h"

class Stack {
private:
    SinglyLinkedList list;   // внутренний список
    
public:
    Stack();
    ~Stack();
    
    int getAt(int index) const;
    void push(int value);
    int pop();
    int top() const;
    bool isEmpty() const;
    int getSize() const;
    void print() const;
};

#endif