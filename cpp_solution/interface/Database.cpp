#include "Database.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

static const map<string, Command> COMMANDS = {
    {"MPUSH", Command::MPUSH}, {"MGET", Command::MGET}, {"MDEL", Command::MDEL},
    {"MSET", Command::MSET}, {"MSIZE", Command::MSIZE}, {"MCAPACITY", Command::MCAPACITY},
    {"MINSERT", Command::MINSERT}, {"MPRINT", Command::MPRINT},
    {"SPUSH", Command::SPUSH}, {"SPOP", Command::SPOP}, {"STOP", Command::STOP},
    {"SEMPTY", Command::SEMPTY}, {"SGET", Command::SGET}, {"SSIZE", Command::SSIZE},
    {"SPRINT", Command::SPRINT},
    {"QPUSH", Command::QPUSH}, {"QPOP", Command::QPOP}, {"QFRONT", Command::QFRONT},
    {"QEMPTY", Command::QEMPTY}, {"QGET", Command::QGET}, {"QSIZE", Command::QSIZE},
    {"QPRINT", Command::QPRINT},
    {"FPUSH", Command::FPUSH}, {"FAPPEND", Command::FAPPEND}, {"FDEL", Command::FDEL},
    {"FDELBACK", Command::FDELBACK}, {"FREMOVE", Command::FREMOVE},
    {"FREMOVE_NODE", Command::FREMOVE_NODE}, {"FREMOVE_AFTER", Command::FREMOVE_AFTER},
    {"FREMOVE_BEFORE", Command::FREMOVE_BEFORE}, {"FGET", Command::FGET},
    {"FFIND", Command::FFIND}, {"FINSERT_AFTER", Command::FINSERT_AFTER},
    {"FINSERT_BEFORE", Command::FINSERT_BEFORE}, {"FSIZE", Command::FSIZE},
    {"FPRINT", Command::FPRINT},
    {"LPUSH", Command::LPUSH}, {"LAPPEND", Command::LAPPEND}, {"LDEL", Command::LDEL},
    {"LDELBACK", Command::LDELBACK}, {"LREMOVE", Command::LREMOVE},
    {"LREMOVE_NODE", Command::LREMOVE_NODE}, {"LREMOVE_AFTER", Command::LREMOVE_AFTER},
    {"LREMOVE_BEFORE", Command::LREMOVE_BEFORE}, {"LGET", Command::LGET},
    {"LFIND", Command::LFIND}, {"LINSERT_AFTER", Command::LINSERT_AFTER},
    {"LINSERT_BEFORE", Command::LINSERT_BEFORE}, {"LSIZE", Command::LSIZE},
    {"LPRINT", Command::LPRINT},
    {"TINSERT", Command::TINSERT}, {"TFIND", Command::TFIND}, {"TCOMPLETE", Command::TCOMPLETE},
    {"TSIZE", Command::TSIZE}, {"TPRINT", Command::TPRINT}, {"TVALUES", Command::TVALUES},
    {"PRINT", Command::PRINT}
};

Command parseCommand(const string& cmd) {
    auto it = COMMANDS.find(cmd);
    if (it == COMMANDS.end()) return Command::UNKNOWN;
    return it->second;
}

void Database::execute(const vector<string>& tokens) {
    if (tokens.empty()) return;

    Command cmd = parseCommand(tokens[0]);

    switch (cmd) {
        case Command::MPUSH: {
            string name = tokens[1];
            string value = tokens[2];
            arrays[name].pushBack(value);
            cout << "OK" << endl;
            break;
        }
        case Command::MGET: {
            string name = tokens[1];
            int index = stoi(tokens[2]);
            string value = arrays[name].getAt(index);
            cout << value << endl;
            break;
        }
        case Command::MDEL: {
            string name = tokens[1];
            int index = stoi(tokens[2]);
            arrays[name].removeAt(index);
            cout << "OK" << endl;
            break;
        }
        case Command::MSET: {
            string name = tokens[1];
            int index = stoi(tokens[2]);
            string value = tokens[3];
            arrays[name].setAt(index, value);
            cout << "OK" << endl;
            break;
        }
        case Command::MSIZE: {
            string name = tokens[1];
            cout << arrays[name].GetSize() << endl;
            break;
        }
        case Command::MCAPACITY: {
            string name = tokens[1];
            cout << arrays[name].getCapacity() << endl;
            break;
        }
        case Command::MINSERT: {
            string name = tokens[1];
            int index = stoi(tokens[2]);
            string value = tokens[3];
            arrays[name].insertAt(index, value);
            cout << "OK" << endl;
            break;
        }
        case Command::MPRINT: {
            string name = tokens[1];
            arrays[name].print();
            break;
        }

        case Command::SPUSH: {
            string name = tokens[1];
            string value = tokens[2];
            stacks[name].push(value);
            cout << "OK" << endl;
            break;
        }
        case Command::SPOP: {
            string name = tokens[1];
            string value = stacks[name].pop();
            cout << value << endl;
            break;
        }
        case Command::SSIZE: {
            string name = tokens[1];
            cout << stacks[name].getSize() << endl;
            break;
        }
        case Command::STOP: {
            string name = tokens[1];
            cout << stacks[name].top() << endl;
            break;
        }
        case Command::SEMPTY: {
            string name = tokens[1];
            cout << (stacks[name].isEmpty() ? "TRUE" : "FALSE") << endl;
            break;
        }
        case Command::SGET: {
            string name = tokens[1];
            int index = stoi(tokens[2]);
            cout << stacks[name].getAt(index) << endl;
            break;
        }
        case Command::SPRINT: {
            string name = tokens[1];
            stacks[name].print();
            break;
        }

        case Command::QPUSH: {
            string name = tokens[1];
            string value = tokens[2];
            queues[name].push(value);
            cout << "OK" << endl;
            break;
        }
        case Command::QPOP: {
            string name = tokens[1];
            string value = queues[name].pop();
            cout << value << endl;
            break;
        }
        case Command::QSIZE: {
            string name = tokens[1];
            cout << queues[name].getSize() << endl;
            break;
        }
        case Command::QFRONT: {
            string name = tokens[1];
            cout << queues[name].getFront() << endl;
            break;
        }
        case Command::QEMPTY: {
            string name = tokens[1];
            cout << (queues[name].isEmpty() ? "TRUE" : "FALSE") << endl;
            break;
        }
        case Command::QGET: {
            string name = tokens[1];
            int index = stoi(tokens[2]);
            cout << queues[name].getAt(index) << endl;
            break;
        }
        case Command::QPRINT: {
            string name = tokens[1];
            queues[name].print();
            break;
        }

        case Command::FPUSH: {
            string name = tokens[1];
            string value = tokens[2];
            singlyLists[name].pushFront(value);
            cout << "OK" << endl;
            break;
        }
        case Command::FAPPEND: {
            string name = tokens[1];
            string value = tokens[2];
            singlyLists[name].pushBack(value);
            cout << "OK" << endl;
            break;
        }
        case Command::FDEL: {
            string name = tokens[1];
            singlyLists[name].popFront();
            cout << "OK" << endl;
            break;
        }
        case Command::FDELBACK: {
            string name = tokens[1];
            singlyLists[name].popBack();
            cout << "OK" << endl;
            break;
        }
        case Command::FREMOVE: {
            string name = tokens[1];
            string value = tokens[2];
            singlyLists[name].removeByValue(value);
            cout << "OK" << endl;
            break;
        }
        case Command::FREMOVE_NODE: {
            string name = tokens[1];
            string value = tokens[2];
            singlyLists[name].removeNode(value);
            cout << "OK" << endl;
            break;
        }
        case Command::FREMOVE_AFTER: {
            string name = tokens[1];
            string value = tokens[2];
            singlyLists[name].removeAfter(value);
            cout << "OK" << endl;
            break;
        }
        case Command::FREMOVE_BEFORE: {
            string name = tokens[1];
            string value = tokens[2];
            singlyLists[name].removeBefore(value);
            cout << "OK" << endl;
            break;
        }
        case Command::FGET: {
            string name = tokens[1];
            int index = stoi(tokens[2]);
            string value = singlyLists[name].getAt(index);
            cout << value << endl;
            break;
        }
        case Command::FFIND: {
            string name = tokens[1];
            string value = tokens[2];
            SinglyNode* node = singlyLists[name].find(value);
            cout << (node != nullptr ? "TRUE" : "FALSE") << endl;
            break;
        }
        case Command::FINSERT_AFTER: {
            string name = tokens[1];
            string value = tokens[2];
            string newValue = tokens[3];
            singlyLists[name].insertAfter(value, newValue);
            cout << "OK" << endl;
            break;
        }
        case Command::FINSERT_BEFORE: {
            string name = tokens[1];
            string value = tokens[2];
            string newValue = tokens[3];
            singlyLists[name].insertBefore(value, newValue);
            cout << "OK" << endl;
            break;
        }
        case Command::FSIZE: {
            string name = tokens[1];
            cout << singlyLists[name].GetSize() << endl;
            break;
        }
        case Command::FPRINT: {
            string name = tokens[1];
            singlyLists[name].print();
            break;
        }

        case Command::LPUSH: {
            string name = tokens[1];
            string value = tokens[2];
            doublyLists[name].pushFront(value);
            cout << "OK" << endl;
            break;
        }
        case Command::LAPPEND: {
            string name = tokens[1];
            string value = tokens[2];
            doublyLists[name].pushBack(value);
            cout << "OK" << endl;
            break;
        }
        case Command::LDEL: {
            string name = tokens[1];
            doublyLists[name].popFront();
            cout << "OK" << endl;
            break;
        }
        case Command::LDELBACK: {
            string name = tokens[1];
            doublyLists[name].popBack();
            cout << "OK" << endl;
            break;
        }
        case Command::LREMOVE: {
            string name = tokens[1];
            string value = tokens[2];
            doublyLists[name].removeByValue(value);
            cout << "OK" << endl;
            break;
        }
        case Command::LREMOVE_NODE: {
            string name = tokens[1];
            string value = tokens[2];
            doublyLists[name].removeNode(value);
            cout << "OK" << endl;
            break;
        }
        case Command::LREMOVE_AFTER: {
            string name = tokens[1];
            string value = tokens[2];
            doublyLists[name].removeAfter(value);
            cout << "OK" << endl;
            break;
        }
        case Command::LREMOVE_BEFORE: {
            string name = tokens[1];
            string value = tokens[2];
            doublyLists[name].removeBefore(value);
            cout << "OK" << endl;
            break;
        }
        case Command::LGET: {
            string name = tokens[1];
            int index = stoi(tokens[2]);
            string value = doublyLists[name].getAt(index);
            cout << value << endl;
            break;
        }
        case Command::LFIND: {
            string name = tokens[1];
            string value = tokens[2];
            DoublyNode* node = doublyLists[name].find(value);
            cout << (node != nullptr ? "TRUE" : "FALSE") << endl;
            break;
        }
        case Command::LINSERT_AFTER: {
            string name = tokens[1];
            string value = tokens[2];
            string newValue = tokens[3];
            doublyLists[name].insertAfter(value, newValue);
            cout << "OK" << endl;
            break;
        }
        case Command::LINSERT_BEFORE: {
            string name = tokens[1];
            string value = tokens[2];
            string newValue = tokens[3];
            doublyLists[name].insertBefore(value, newValue);
            cout << "OK" << endl;
            break;
        }
        case Command::LSIZE: {
            string name = tokens[1];
            cout << doublyLists[name].getSize() << endl;
            break;
        }
        case Command::LPRINT: {
            string name = tokens[1];
            doublyLists[name].print();
            break;
        }

        case Command::TINSERT: {
            string name = tokens[1];
            int value = stoi(tokens[2]);
            trees[name].insert(value);
            cout << "OK" << endl;
            break;
        }
        case Command::TFIND: {
            string name = tokens[1];
            int value = stoi(tokens[2]);
            bool found = trees[name].find(value);
            cout << (found ? "TRUE" : "FALSE") << endl;
            break;
        }
        case Command::TCOMPLETE: {
            string name = tokens[1];
            bool complete = trees[name].isComplete();
            cout << (complete ? "TRUE" : "FALSE") << endl;
            break;
        }
        case Command::TSIZE: {
            string name = tokens[1];
            cout << trees[name].getSize() << endl;
            break;
        }
        case Command::TPRINT: {
            string name = tokens[1];
            trees[name].print();
            break;
        }
        case Command::TVALUES: {
            string name = tokens[1];
            vector<int> values = trees[name].getValues();
            for (int i = 0; i < (int)values.size(); i++) {
                cout << values[i];
                if (i < (int)values.size() - 1) cout << " ";
            }
            cout << endl;
            break;
        }

        case Command::PRINT: {
            for (auto& pair : arrays) {
                cout << "ARRAY " << pair.first << ":" << endl;
                pair.second.print();
            }
            for (auto& pair : stacks) {
                cout << "STACK " << pair.first << ":" << endl;
                pair.second.print();
            }
            for (auto& pair : queues) {
                cout << "QUEUE " << pair.first << ":" << endl;
                pair.second.print();
            }
            for (auto& pair : singlyLists) {
                cout << "SLIST " << pair.first << ":" << endl;
                pair.second.print();
            }
            for (auto& pair : doublyLists) {
                cout << "DLIST " << pair.first << ":" << endl;
                pair.second.print();
            }
            for (auto& pair : trees) {
                cout << "TREE " << pair.first << ":" << endl;
                pair.second.print();
            }
            break;
        }

        case Command::UNKNOWN:
        default:
            cout << "Неизвестная команда: " << tokens[0] << endl;
            break;
    }
}

void Database::save(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл для записи: " << filename << endl;
        return;
    }

    // Сохраняем массивы
    for (auto& pair : arrays) {
        string name = pair.first;
        MyArray& arr = pair.second;

        file << "ARRAY " << name << " " << arr.GetSize();
        for (int i = 0; i < arr.GetSize(); i++) {
            file << " " << arr.getAt(i);
        }
        file << endl;
    }

    // Сохраняем стеки
    for (auto& pair : stacks) {
        string name = pair.first;
        Stack& st = pair.second;

        file << "STACK " << name << " " << st.getSize();
        for (int i = 0; i < st.getSize(); i++) {
            file << " " << st.getAt(i);
        }
        file << endl;
    }

    // Сохраняем очереди
    for (auto& pair : queues) {
        string name = pair.first;
        Queue& q = pair.second;

        file << "QUEUE " << name << " " << q.getSize();
        for (int i = 0; i < q.getSize(); i++) {
            file << " " << q.getAt(i);
        }
        file << endl;
    }

    // Сохраняем односвязные списки
    for (auto& pair : singlyLists) {
        string name = pair.first;
        SinglyLinkedList& lst = pair.second;

        file << "SLIST " << name << " " << lst.GetSize();
        for (int i = 0; i < lst.GetSize(); i++) {
            file << " " << lst.getAt(i);
        }
        file << endl;
    }

    // Сохраняем двусвязные списки
    for (auto& pair : doublyLists) {
        string name = pair.first;
        DoublyLinkedList& lst = pair.second;

        file << "DLIST " << name << " " << lst.getSize();
        for (int i = 0; i < lst.getSize(); i++) {
            file << " " << lst.getAt(i);
        }
        file << endl;
    }

    // Сохраняем деревья
    for (auto& pair : trees) {
        string name = pair.first;
        CompleteBinaryTree& tree = pair.second;

        vector<int> values = tree.getValues();
        file << "TREE " << name << " " << values.size();
        for (int v : values) {
            file << " " << v;
        }
        file << endl;
    }
    file.close();
}

void Database::load(const string& filename) {
    arrays.clear();
    stacks.clear();
    queues.clear();
    singlyLists.clear();
    doublyLists.clear();
    trees.clear();

    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;

        string type = tokens[0];
        string name = tokens[1];
        int count = stoi(tokens[2]);

        if (type == "ARRAY") {
            for (int i = 0; i < count; i++) {
                string value = tokens[3 + i];
                arrays[name].pushBack(value);
            }
        }
        else if (type == "STACK") {
            for (int i = count - 1; i >= 0; i--) {
                string value = tokens[3 + i];
                stacks[name].push(value);
            }
        }
        else if (type == "QUEUE") {
            for (int i = 0; i < count; i++) {
                string value = tokens[3 + i];
                queues[name].push(value);
            }
        }
        else if (type == "SLIST") {
            for (int i = count - 1; i >= 0; i--) {
                string value = tokens[3 + i];
                singlyLists[name].pushFront(value);
            }
        }
        else if (type == "DLIST") {
            for (int i = count - 1; i >= 0; i--) {
                string value = tokens[3 + i];
                doublyLists[name].pushFront(value);
            }
        }
        else if (type == "TREE") {
            for (int i = 0; i < count; i++) {
                int value = stoi(tokens[3 + i]);
                trees[name].insert(value);
            }
        }
    }

    file.close();
}