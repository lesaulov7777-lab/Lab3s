#include"Queue.h"
#include<iostream>
using namespace std;

Queue::Queue(){} //конструктор
Queue::~Queue(){} //деструктор

void Queue::push(int value){
    list.pushBack(value);
}

int Queue::pop(){
    if(isEmpty()){
        return -1;
    }
    int val = list.getAt(0);
    list.popFront();
    return val;
}

int Queue::getAt(int index) const {
    if (index < 0 || index >= getSize()) {
        cout << "Ошибка, индекс за пределами диапазона" << endl;
        return -1;
    }
    return list.getAt(index);
}

int Queue::getFront() const{
    if(isEmpty()){
        cout<<"Очередь пуста"<<endl;
        return -1;
    }
    return list.getAt(0);
}

bool Queue::isEmpty() const{
    return list.GetSize()==0;
}

int Queue::getSize() const{
    return list.GetSize();
}

void Queue::print() const{
    list.print();
}