#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

struct DoublyNode {
    int value;
    DoublyNode* next;
    DoublyNode* prev;
    DoublyNode(int val);
};

class DoublyLinkedList {
private:
    DoublyNode* head;
    DoublyNode* tail;
    int size;

public:
    // Конструктор и деструктор
    DoublyLinkedList();
    ~DoublyLinkedList();

    // Размер
    int getSize() const;

    // Добавление
    void pushFront(int value);
    void pushBack(int value);
    void insertAfter(DoublyNode* node, int value);
    void insertBefore(DoublyNode* node, int value);

    // Удаление
    void popFront();
    void popBack();
    void removeByValue(int value);
    void removeNode(DoublyNode* node);

    // Поиск и чтение
    DoublyNode* find(int value) const;
    int getAt(int index) const;
    void print() const;
};

#endif