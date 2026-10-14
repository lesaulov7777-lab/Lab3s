#include "Database.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void Database::execute(const vector<string>& tokens) {
    if (tokens.empty()) return;
    
    string cmd = tokens[0];
    
    if (cmd == "MPUSH") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        arrays[name].pushBack(value);
        cout << "OK" << endl;
    }
    else if (cmd == "MGET") {
        string name = tokens[1];
        int index = stoi(tokens[2]);
        int value = arrays[name].getAt(index);
        cout << value << endl;
    }
    else if (cmd == "MDEL") {
        string name = tokens[1];
        int index = stoi(tokens[2]);
        arrays[name].removeAt(index);
        cout << "OK" << endl;
    }
    else if (cmd == "MSET") {
        string name = tokens[1];
        int index = stoi(tokens[2]);
        int value = stoi(tokens[3]);
        arrays[name].setAt(index, value);
        cout << "OK" << endl;
    }
    else if (cmd == "MSIZE") {
        string name = tokens[1];
        cout << arrays[name].GetSize() << endl;
    }
    else if (cmd == "MPRINT") {
        string name = tokens[1];
        arrays[name].print();
    }

    else if (cmd == "SPUSH"){
        string name = tokens[1];
        int value = stoi(tokens[2]);
        stacks[name].push(value);
        cout << "OK" << endl;
    }
    else if (cmd == "SPOP"){
        string name = tokens[1];
        int value = stacks[name].pop();
        cout << value << endl;
    }
    else if (cmd == "SSIZE") {
        string name = tokens[1];
        cout << stacks[name].getSize() << endl;
    }
    else if (cmd == "SPRINT") {
        string name = tokens[1];
        stacks[name].print();
    }

    else if (cmd == "QPUSH") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        queues[name].push(value);
        cout << "OK" << endl;
    }
    else if (cmd == "QPOP") {
        string name = tokens[1];
        int value = queues[name].pop();
        cout << value << endl;
    }
    else if (cmd == "QSIZE") {
        string name = tokens[1];
        cout << queues[name].getSize() << endl;
    }
    else if (cmd == "QPRINT") {
        string name = tokens[1];
        queues[name].print();
    }

    else if (cmd == "FPUSH") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        singlyLists[name].pushFront(value);
        cout << "OK" << endl;
    }
    else if (cmd == "FAPPEND") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        singlyLists[name].pushBack(value);
        cout << "OK" << endl;
    }
    else if (cmd == "FDEL") {
        string name = tokens[1];
        singlyLists[name].popFront();
        cout << "OK" << endl;
    }
    else if (cmd == "FREMOVE") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        singlyLists[name].removeByValue(value);
        cout << "OK" << endl;
    }
    else if (cmd == "FGET") {
        string name = tokens[1];
        int index = stoi(tokens[2]);
        int value = singlyLists[name].getAt(index);
        cout << value << endl;
    }
    else if (cmd == "FFIND") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        SinglyNode* node = singlyLists[name].find(value);
        cout << (node != nullptr ? "TRUE" : "FALSE") << endl;
    }
    else if (cmd == "FSIZE") {
        string name = tokens[1];
        cout << singlyLists[name].GetSize() << endl;
    }
    else if (cmd == "FPRINT") {
        string name = tokens[1];
        singlyLists[name].print();
    }

    else if (cmd == "LPUSH") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        doublyLists[name].pushFront(value);
        cout << "OK" << endl;
    }
    else if (cmd == "LAPPEND") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        doublyLists[name].pushBack(value);
        cout << "OK" << endl;
    }
    else if (cmd == "LDEL") {
        string name = tokens[1];
        doublyLists[name].popFront();
        cout << "OK" << endl;
    }
    else if (cmd == "LREMOVE") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        doublyLists[name].removeByValue(value);
        cout << "OK" << endl;
    }
    else if (cmd == "LGET") {
        string name = tokens[1];
        int index = stoi(tokens[2]);
        int value = doublyLists[name].getAt(index);
        cout << value << endl;
    }
    else if (cmd == "LFIND") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        DoublyNode* node = doublyLists[name].find(value);
        cout << (node != nullptr ? "TRUE" : "FALSE") << endl;
    }
    else if (cmd == "LSIZE") {
        string name = tokens[1];
        cout << doublyLists[name].getSize() << endl;
    }
    else if (cmd == "LPRINT") {
        string name = tokens[1];
        doublyLists[name].print();
    }

    else if (cmd == "TINSERT") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        trees[name].insert(value);
        cout << "OK" << endl;
    }
    else if (cmd == "TFIND") {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        bool found = trees[name].find(value);
        cout << (found ? "TRUE" : "FALSE") << endl;
    }
    else if (cmd == "TCOMPLETE") {
        string name = tokens[1];
        bool complete = trees[name].isComplete();
        cout << (complete ? "TRUE" : "FALSE") << endl;
    }
    else if (cmd == "TSIZE") {
        string name = tokens[1];
        cout << trees[name].getSize() << endl;
    }
    else if (cmd == "TPRINT") {
        string name = tokens[1];
        trees[name].print();
    }

    else if (cmd == "PRINT") {
        // Массивы
        for (auto& pair : arrays) {
            cout << "ARRAY " << pair.first << ":" << endl;
            pair.second.print();
        }
        // Стеки
        for (auto& pair : stacks) {
            cout << "STACK " << pair.first << ":" << endl;
            pair.second.print();
        }
        // Очереди
        for (auto& pair : queues) {
            cout << "QUEUE " << pair.first << ":" << endl;
            pair.second.print();
        }
        // Односвязные списки
        for (auto& pair : singlyLists) {
            cout << "SLIST " << pair.first << ":" << endl;
            pair.second.print();
        }
        // Двусвязные списки
        for (auto& pair : doublyLists) {
            cout << "DLIST " << pair.first << ":" << endl;
            pair.second.print();
        }
        // Деревья
        for (auto& pair : trees) {
            cout << "TREE " << pair.first << ":" << endl;
            pair.second.print();
        }
    }
    else {
        cout << "Неизвестная команда: " << cmd << endl;
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
                int value = stoi(tokens[3 + i]);
                arrays[name].pushBack(value);
            }
        }
        else if (type == "STACK") {
            for (int i = count - 1; i >= 0; i--) {
                int value = stoi(tokens[3 + i]);
                stacks[name].push(value);
            }
        }
        else if (type == "QUEUE") {
            for (int i = 0; i < count; i++) {
                int value = stoi(tokens[3 + i]);
                queues[name].push(value);
            }
        }
        else if (type == "SLIST") {
            for (int i = count - 1; i >= 0; i--) {
                int value = stoi(tokens[3 + i]);
                singlyLists[name].pushFront(value);
            }
        }
        else if (type == "DLIST") {
            for (int i = count - 1; i >= 0; i--) {
                int value = stoi(tokens[3 + i]);
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