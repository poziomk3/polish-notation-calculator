//
// Created by karol on 20.11.2023.
//
#include <iostream>
#include "Tree.h"
#include <vector>

using namespace std;


Tree::Tree(vector<string> expressionInit) {
    mistakeFound = false;
    expressionVector = expressionInit;

    root = createTree(root);
    if (mistakeFound)
        cout << "Niepoprawne wyrazenie zostalo poprawione" << endl;
    else
        cout << "Wyrazenie jest poprawne" << endl;
}


bool Tree::isVariableName(const string &word) {
    if (getPositiveNumber(word) != -1)
        return false;

    for (char i: word)
        if (i < 'a' || i > 'z')
            if (i < '0' || i > '9')
                return false;


    return true;
}

int Tree::iSOperation(const string &word) {
    return word == "+" || word == "-" || word == "*" || word == "/" || word == "sin" || word == "cos";
}

int Tree::getPositiveNumber(const string &word) {
    int number = 0;
    for (char i: word) {
        if (i >= '0' && i <= '9') {
            number = number * 10 + (i - '0');
        } else {
            return -1;
        }
    }
    return number;
}

int Tree::getNumberOfOperands(const string &word) {
    if (word == "+" || word == "-" || word == "*" || word == "/") {
        return 2;
    } else if (word == "sin" || word == "cos") {
        return 1;
    } else {
        return -1;
    }
}


Node Tree::createTree(Node &node) {
    if (expressionVector.empty()) {
        mistakeFound = true;
        return {1, false};
    }

    string item = expressionVector.back();
    expressionVector.pop_back();
    if (iSOperation(item)) {

        node = Node(-1, true, item);
        for (int i = 0; i < getNumberOfOperands(item); ++i) {

            Node nowy;
            node.addChild(createTree(nowy));

        }
        return node;
    } else if (isVariableName(item))
        return {-1, false, item};
    else if (getPositiveNumber(item) != -1)
        return Node(getPositiveNumber(item), false);
    else {
        mistakeFound = true;
        return createTree(node);
    }
}

void Tree::traverseTree() {
    root.prefixTraverse(root);
}

void Tree::fillVariables() {
    root.addVariables(variables);
}

void Tree::printVector(vector<string> &vector) {
    for (const string &i: vector)
        cout << i << " ";

}

vector<int> Tree::fillValues(const vector<string>& expression) {
    vector<int> result;
    for (const string &i: expression)
        if (getPositiveNumber(i) != -1)
            result.push_back(getPositiveNumber(i));
    return result;

}

Tree::Tree() {

}

void Tree::compile(vector<string> expression) {
    fillVariables();
    values = fillValues(expression);
    if (values.size() != variables.size()) {
        cout << "Nie mozna skompilowac, zla liczba wartosci" << endl;
    } else
        cout << root.compile(root, variables, values) << endl;

}

void Tree::printVariables(vector<string> expression) {
    fillVariables();
    printVector(variables);
}



Tree Tree::operator+(const Tree& tree) {
    *root.getLeaf()=tree.root;
    return *this;
}





