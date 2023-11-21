//
// Created by karol on 21.11.2023.
//

#include <iostream>
#include "Interface.h"
#include "Tree.h"
#include <vector>

using namespace std;

Interface::Interface() {

}


void Interface::start() {
    Tree tree;
    while (true) {
        cout << "Wpisz polecenie:" << endl;
        string expression;
        getline(cin, expression);

        vector<string> line = convertToVector(expression);
        string word;
        word = line.back();
        line.pop_back();

        tree = executeCommand(word, line, tree);
    }


}


vector<string> Interface::convertToVector(string expression) {
    vector<string> table;
    size_t iterator = 0;
    while (iterator < expression.size()) {
        string part;
        while (iterator < expression.size() && expression[iterator] != ' ') {
            part += expression[iterator++];
        }
        iterator++;
        if (!part.empty()) {
            table.insert(table.begin(), part);
        }

    }

    return table;
}

Tree Interface::executeCommand(string &command, vector<string> &line, Tree &tree) {
    if (command == "enter") {
        Tree nowy(line);
        nowy.traverseTree();
        return nowy;
    } else if (command == "print")
        tree.traverseTree();
    else if (command == "comp")
        tree.compile(line);
    else if (command == "join") {
        tree = tree + Tree(line);
        tree.traverseTree();
    } else if (command == "vars")
        tree.printVariables(line);
    else
        cout << "Niepoprawna komenda" << endl;
    return tree;

}




