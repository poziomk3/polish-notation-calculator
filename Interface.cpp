#include <iostream>
#include "Interface.h"
#include "Tree.h"
#include <vector>

using namespace std;

// Konstruktor interfejsu
Interface::Interface() {

}

// Rozpoczyna działanie interfejsu
void Interface::start() {

    while(true){
    cout << "Wybierz typ drzewa:" << endl;
    cout << "1. String" << endl;
    cout << "2. Double" << endl;
    cout << "3. Int" << endl;
    cout << "4. Wyjscie" << endl;
    string type;
    cin>>type;
    if(type=="1"){
        Tree<string> tree;
        looper(tree);
    }
    else if(type=="2"){
        Tree<double> tree;
        looper(tree);
    }
    else if(type=="3"){
        Tree<int> tree;
        looper(tree);
    }
    else if(type=="4"){
        return;
    }
    else{
        cout<<"Niepoprawny wybór"<<endl;

    }
}}

// Konwertuje wyrażenie na wektor słów
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



template<typename T>
void Interface::looper(Tree<T> &tree) {
    while (true) {
        cout << "Wpisz polecenie::" << endl;
        string expression;
        while (expression.empty())
            getline(cin, expression);
        {


            vector<string> line = convertToVector(expression);
            string word;
            word = line.back();
            line.pop_back();

            if (word == "exit")
                return;


            tree = executeCommand(word, line, tree);

        }
    }
}




// Wykonuje polecenie na drzewie i zwraca zmodyfikowane drzewo
template <typename T>
Tree<T> Interface::executeCommand(string &command, vector<string> &line, Tree<T> &tree) {
    if (command == "enter") {
        Tree<T> nowy(line);
        nowy.traverseTree();
//        Tree<T> tree2(nowy);
        return nowy;
    } else if (command == "print")
        tree.traverseTree();
    else if (command == "comp")
        tree.compile(line);
    else if (command == "join") {
        tree = tree + Tree<T>(line);
        tree.traverseTree();
    } else if (command == "vars")
        tree.printVariables(line);

    else
        cout << "Niepoprawna komenda" << endl;
    return tree;
}