//
// Created by karol on 20.11.2023.
//
#include <algorithm>
#include <string>
#include <iostream>
#include "Node.h"
#include <vector>
using namespace std;
Node::Node(int valueInit, bool isOperationInit, string operationInit) {
    value=valueInit;
    isOperation=isOperationInit;
    opvar=operationInit;
}

Node::Node(int  valueInit,bool isOperationInit) {
    value=valueInit;
    isOperation=isOperationInit;
}

Node::Node() {
    value=-1;
    isOperation=false;
}

void Node::addChild(Node child) {
    children.push_back(child);
}


const vector<Node> &Node::getChildren() const {
    return children;
}


string Node::toString() {
    if (isOperation)
        return opvar;
    if (value==-1)
        return opvar;
    return to_string(value);
}

void Node::prefixTraverse(Node &node) {
    cout<<node.toString()<< " ";
    for (Node child:node.getChildren())
        prefixTraverse(child);

}

bool Node::isVariable() {
    return !isOperation && value == -1;
}
void Node::addVariables(vector<string> &variables) {
    if (isVariable() && variables.end() == find(variables.begin(), variables.end(), opvar))
        variables.push_back(opvar);
    for (Node child:children)
        child.addVariables(variables);
}

float Node::compile(Node &node, vector<string> &variables, vector<int> &values) {
    if (value != -1)
        return value;
    if (isVariable())
        return values[distance(variables.begin(), find(variables.begin(), variables.end(), opvar))];

    if (isOperation) {
            return calculate(children, variables, values);
        }

}

float Node::calculate(vector<Node> &nodeValues, vector<string> &variables, vector<int> &values) {
    if(opvar=="+")
        return nodeValues[0].compile(nodeValues[0],variables,  values) + nodeValues[1].compile(nodeValues[1],variables,  values);
    if(opvar=="-")
        return nodeValues[0].compile(nodeValues[0],variables,  values) - nodeValues[1].compile(nodeValues[1],variables,  values);
    if(opvar=="*")
        return nodeValues[0].compile(nodeValues[0],variables,  values) * nodeValues[1].compile(nodeValues[1],variables,  values);
    if(opvar=="/")
        return nodeValues[0].compile(nodeValues[0],variables,  values) / nodeValues[1].compile(nodeValues[1],variables,  values);
    if(opvar=="sin")
        return nodeValues[0].compile(nodeValues[0],variables,  values);
    if(opvar=="cos")
        return nodeValues[0].compile(nodeValues[0],variables,  values);

}

Node* Node::getLeaf() {
    if(children.empty())
        return  this;
    return children[0].getLeaf();
}




