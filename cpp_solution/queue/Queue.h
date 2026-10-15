#ifndef QUEUE_H
#define QUEUE_H

#include <string>

// Очередь (FIFO) на односвязных узлах с указателями на голову и хвост.
// push, pop, getFront, isEmpty, getSize — O(1).
// getAt, print — O(n).
struct QueueNode {
    std::string value;
    QueueNode* next;
    QueueNode(std::string val);
};

class Queue {
private:
    QueueNode* head;   // откуда извлекаем
    QueueNode* tail;   // куда добавляем
    int size;

public:
    Queue();
    ~Queue();

    // Очередь владеет узлами, копирование запрещено (иначе двойное удаление)
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void push(std::string value);      // O(1)
    std::string pop();                 // O(1)
    std::string getFront() const;      // O(1)
    bool isEmpty() const;              // O(1)
    int getSize() const;               // O(1)

    std::string getAt(int index) const; // O(n)
    void print() const;                 // O(n)
};

#endif
