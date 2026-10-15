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

enum class Command {
    UNKNOWN,
    MPUSH, MGET, MDEL, MSET, MSIZE, MCAPACITY, MINSERT, MPRINT,
    SPUSH, SPOP, STOP, SEMPTY, SGET, SSIZE, SPRINT,
    QPUSH, QPOP, QFRONT, QEMPTY, QGET, QSIZE, QPRINT,
    FPUSH, FAPPEND, FDEL, FDELBACK, FREMOVE, FREMOVE_NODE, FREMOVE_AFTER, FREMOVE_BEFORE,
    FGET, FFIND, FINSERT_AFTER, FINSERT_BEFORE, FSIZE, FPRINT,
    LPUSH, LAPPEND, LDEL, LDELBACK, LREMOVE, LREMOVE_NODE, LREMOVE_AFTER, LREMOVE_BEFORE,
    LGET, LFIND, LINSERT_AFTER, LINSERT_BEFORE, LSIZE, LPRINT,
    TINSERT, TFIND, TCOMPLETE, TSIZE, TPRINT, TVALUES,
    PRINT
};

Command parseCommand(const std::string& cmd);

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