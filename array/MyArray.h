#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>
using namespace std;

class MyArray {
private:
    int* data;
    int capacity;
    int size;

public:
    MyArray(int cap = 2);
    ~MyArray();

    int GetSize() const;
    int getCapacity() const;
    void pushBack(int value);
    void insertAt(int index, int value);
    int getAt(int index) const;
    void setAt(int index, int value);
    void removeAt(int index);
    void print() const;
};

#endif