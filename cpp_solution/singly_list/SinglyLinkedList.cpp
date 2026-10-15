#include "SinglyLinkedList.h"
#include <iostream>
using namespace std;

SinglyNode::SinglyNode(string val) : value(val), next(nullptr) {} //узел

SinglyLinkedList::SinglyLinkedList() { //конструктор
    head = nullptr;
    size = 0;
}

SinglyLinkedList::~SinglyLinkedList() { //деструктор
    SinglyNode* current = head;
    while (current != nullptr) {
        SinglyNode* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
}

int SinglyLinkedList::GetSize() const { //вернуть размер
    return size;
}

void SinglyLinkedList::print() const { //вывести массив
    SinglyNode* current = head;
    cout<<"[";
    while (current != nullptr) {
        cout << current->value;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout<<"]"<<endl;
}

void SinglyLinkedList::pushFront(string value){ //добавление в начало
    SinglyNode* new_node = new SinglyNode(value);
    new_node->next = head;
    head = new_node;
    size++;
}

void SinglyLinkedList::pushBack(string value){ //добавление в конец
    SinglyNode* new_node = new SinglyNode(value);
    if(head==nullptr){
        head = new_node;
    }else{
        SinglyNode* current = head;
        while(current->next!=nullptr){
            current = current->next;
        }
        current->next=new_node;
    }
    size++;
}

void SinglyLinkedList::popFront(){ //удаление в начале
    if(head==nullptr){
        cout<<"Список пуст йоу"<<endl;
        return;
    }else{
        SinglyNode* current = head;
        head = current->next;
        delete current;
        size--;
    }
}

void SinglyLinkedList::popBack(){ //удаление в конце
    if(head==nullptr){
        cout<<"Список пуст йоу"<<endl;
        return;
    }
    if(head->next==nullptr){
        delete head;
        head=nullptr;
        size--;
        return;
    }
    SinglyNode* current = head;
    while(current->next->next!=nullptr){
        current = current->next;
    }
    delete current->next;
    current->next=nullptr;
    size--;
}

SinglyNode* SinglyLinkedList::find(string value) const { //поиск адреса узла по значению
    SinglyNode* current = head;
    while(current!=nullptr){
        if(current->value == value){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void SinglyLinkedList::insertAfter(string target, string value){ //вставка после узла с заданным значением
    SinglyNode* node = find(target);
    if(node == nullptr){
        cout<<"Узел с таким значением не найден"<<endl;
        return;
    }
    SinglyNode* new_node = new SinglyNode(value);
    new_node->next = node->next;
    node->next = new_node;
    size++;
}

void SinglyLinkedList::insertBefore(string target, string value){ //вставка до узла с заданным значением
    SinglyNode* node = find(target);
    if(node == nullptr){
        cout<<"Узел с таким значением не найден"<<endl;
        return;
    }
    if(node == head){
        pushFront(value);
        return;
    }
    SinglyNode* new_node = new SinglyNode(value);
    SinglyNode* current = head;
    while(current != nullptr && current->next!=node){
        current=current->next;
    }
    new_node->next=current->next;
    current->next=new_node;
    size++;
}

void SinglyLinkedList::removeByValue(string value){ //удаление по значению
    removeNode(value);
}

void SinglyLinkedList::removeNode(string value){ //удаление узла по значению
    if(head==nullptr){
        cout<<"Список пуст йоу"<<endl;
        return;
    }
    if(head->value == value){
        popFront();
        return;
    }
    SinglyNode* current = head;
    while(current->next!=nullptr && current->next->value!=value){
        current = current->next;
    }
    if(current->next == nullptr){
        cout<<"Значение не найдено"<<endl;
        return;
    }
    SinglyNode* tmp = current->next;
    current->next=current->next->next;
    delete tmp;
    size--;
}

void SinglyLinkedList::removeAfter(string target){ //удаление узла, стоящего после заданного
    SinglyNode* node = find(target);
    if(node==nullptr){
        cout<<"Узел с таким значением не найден"<<endl;
        return;
    }
    if(node->next==nullptr){
        cout<<"После заданного узла нет узла"<<endl;
        return;
    }
    SinglyNode* tmp = node->next;
    node->next = tmp->next;
    delete tmp;
    size--;
}

void SinglyLinkedList::removeBefore(string target){ //удаление узла, стоящего до заданного
    SinglyNode* node = find(target);
    if(node==nullptr){
        cout<<"Узел с таким значением не найден"<<endl;
        return;
    }
    if(node==head){
        cout<<"Перед заданным узлом нет узла"<<endl;
        return;
    }
    SinglyNode* prev = head;
    while(prev->next!=node){
        prev=prev->next;
    }
    if(prev==head){
        popFront();
        return;
    }
    SinglyNode* prevPrev = head;
    while(prevPrev->next!=prev){
        prevPrev=prevPrev->next;
    }
    prevPrev->next=node;
    delete prev;
    size--;
}

string SinglyLinkedList::getAt(int index) const{ //Вернуть элемент по индексу
    if(index < 0 || index >= size){
        cout<<"Ошибка, индекс за пределами диапозона"<<endl;
        return "";
    }
    SinglyNode* current = head;
    for(int i=0; i<index; i++){
        current=current->next;
    }
    return current->value;
}
