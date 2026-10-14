#include"Stack.h"
#include<iostream>
using namespace std;

Stack::Stack(){}; //создается список
Stack::~Stack(){} //деструктор

void Stack::push(int value){ //вставка элемента
    list.pushFront(value);
}

bool Stack::isEmpty() const {
    return list.GetSize() == 0;
}

int Stack::getAt(int index) const {
    if (index < 0 || index >= getSize()) {
        cout << "Ошибка, индекс за пределами диапазона" << endl;
        return -1;
    }
    return list.getAt(index);
}

int Stack::pop(){
    if (!isEmpty()) {
        int val = list.getAt(0); //вернуть верхний элемент
        list.popFront();
        return val;
    }
    return -1;
}

int Stack::top() const{
    if(isEmpty()){
        cout<<"Стэк пуст"<<endl;
        return -1;
    }
    return list.getAt(0);
} 

int Stack::getSize() const{
    return list.GetSize();
}

void Stack::print() const{
    list.print();
}
