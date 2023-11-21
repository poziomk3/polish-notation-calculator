//
// Created by karol on 20.11.2023.
//

#ifndef ZADANIE3_TREE_H
#define ZADANIE3_TREE_H

#include <vector>
#include "Node.h"

using namespace std;

class Tree {
private:


    vector<string> expressionVector;
    vector<string> variables;
    vector<int> values;
    Node root;
    bool mistakeFound;

    Node createTree(Node &node);

    int iSOperation(const string &word);

    int getPositiveNumber(const string &word);

    static int getNumberOfOperands(const string &word);

    bool isVariableName(const string &word);

    void fillVariables();

    void printVector(vector<string> &vector);

    vector<int> fillValues(const vector<string>& expression);

public:
    Tree();

    Tree(vector<string> expressionInit);

    void traverseTree();

    void printVariables(vector<string> expression);

    void compile(vector<string> expression);


    Tree operator+(const Tree &tree);
};


#endif //ZADANIE3_TREE_H
