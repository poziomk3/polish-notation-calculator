//
// Created by karol on 20.11.2023.
//

#ifndef ZADANIE3_NODE_H
#define ZADANIE3_NODE_H

#include <string>
#include <vector>

using namespace std;

class Node {
private:


    bool isOperation;
    int value;
    string opvar;
    vector<Node> children;
public:

    void addChild(Node child);
    bool isVariable();
    string toString();
    void prefixTraverse(Node &node);
    const vector<Node> &getChildren() const;
    void addVariables(vector<string> &variables);
    Node(int valueInit, bool isOperationInit, string &operationInit);
    Node();
    Node(int valueInit, bool isOperationInit);
    Node* getLeaf();



    double compile(Node &node, vector<string> &variables, vector<int> &values);

    double calculate(vector<Node> &nodeValues, vector<string> &variables, vector<int> &values);
};


#endif //ZADANIE3_NODE_H
