#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

struct SinglyNode {
    int value;
    SinglyNode* next;
    SinglyNode(int val);
};

class SinglyLinkedList {
private:
    SinglyNode* head;    
    int size; 
    
public:
    SinglyLinkedList();   
    ~SinglyLinkedList();  
    
    int GetSize() const;
    void print() const;
    
    void pushFront(int value);   
    void pushBack(int value);

    void popFront();
    void popBack();
    void removeByValue(int value);
    void removeNode(SinglyNode* node);

    SinglyNode* find(int value) const;
    void insertAfter(SinglyNode* node, int value);
    void insertBefore(SinglyNode* node, int value);
    int getAt(int index) const;
};

#endif