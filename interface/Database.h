#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include <vector>
#include "MyArray.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "CompleteBinaryTree.h"

using namespace std;

class Database {
private:
    map<string, MyArray> arrays;
    map<string, SinglyLinkedList> singlyLists;
    map<string, DoublyLinkedList> doublyLists;
    map<string, Stack> stacks;
    map<string, Queue> queues;
    map<string, CompleteBinaryTree> trees;

public:
    void execute(const vector<string>& tokens);
    void save(const string& filename);
    void load(const string& filename);
};

#endif