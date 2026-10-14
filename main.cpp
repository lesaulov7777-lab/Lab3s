#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "interface/Database.h"

using namespace std;

// Парсер строки запроса
vector<string> parseQuery(const string& query) {
    vector<string> tokens;
    istringstream iss(query);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(int argc, char* argv[]) {
    string filename = "";
    string query = "";

    // Парсер argc/argv
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == string("--file")) {
            if (i + 1 < argc) {
                filename = argv[i + 1];
                i++;
            } else {
                cout << "Ошибка: отсутствует значение для --file" << endl;
                return 1;
            }
        } else if (argv[i] == string("--query")) {
            if (i + 1 < argc) {
                query = argv[i + 1];
                i++;
            } else {
                cout << "Ошибка: отсутствует значение для --query" << endl;
                return 1;
            }
        }
    }

    // Парсинг строки запроса
    vector<string> tokens = parseQuery(query);

    // Создать Database и выполнить команду
    Database db;
    db.load(filename);
    db.execute(tokens);
    db.save(filename); 

    return 0;
}