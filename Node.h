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
    Node();
    Node(int valueInit, bool isOperationInit,string operationInit);
    Node(int valueInit, bool isOperationInit);
    void addChild(Node child);
    bool isVariable();
    string toString();
    void prefixTraverse(Node &node);
    const vector<Node> &getChildren() const;
    void addVariables(vector<string> &variables);

    Node* getLeaf();



    float compile(Node &node, vector<string> &variables, vector<int> &values);

    float calculate(vector<Node> &nodeValues, vector<string> &variables, vector<int> &values);
};


#endif //ZADANIE3_NODE_H
