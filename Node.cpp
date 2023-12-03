#include <algorithm>
#include <string>
#include <iostream>
#include "Node.h"
#include <vector>
#include <cmath>
using namespace std;


//klasa obsługująca węzły drzewa

// Konstruktor dla węzła, który jest operacją
Node::Node(int valueInit, bool isOperationInit, string &operationInit) {
    value = valueInit;
    isOperation = isOperationInit;
    opvar = operationInit;
}

// Konstruktor dla węzła, który nie jest operacją
Node::Node(int valueInit, bool isOperationInit) {
    value = valueInit;
    isOperation = isOperationInit;
}

// Konstruktor domyślny
Node::Node() {
    value = -1;
    isOperation = false;
}

// Dodaje dziecko do węzła
void Node::addChild(Node child) {
    children.push_back(child);
}

// Zwraca wektor dzieci węzła
const vector<Node> &Node::getChildren() const {
    return children;
}

// Konwertuje węzeł na string
string Node::toString() {
    if (isOperation)
        return opvar;
    if (value == -1)
        return opvar;
    return to_string(value);
}

// Przechodzi przez drzewo w notacji prefiksowej
void Node::prefixTraverse(Node &node) {
    cout << node.toString() << " ";
    for (Node child : node.getChildren())
        prefixTraverse(child);
}

// Sprawdza, czy węzeł reprezentuje zmienną
bool Node::isVariable() {
    return !isOperation && value == -1;
}

// Dodaje zmienne do wektora zmiennych
void Node::addVariables(vector<string> &variables) {
    if (isVariable() && variables.end() == find(variables.begin(), variables.end(), opvar))
        variables.push_back(opvar);
    for (Node child : children)
        child.addVariables(variables);
}

// Kompiluje drzewo i oblicza wartość
double Node::compile(Node &node, vector<string> &variables, vector<int> &values) {
    if (value != -1)
        return value;

    if (isVariable())
        for (int i = 0; i < variables.size(); ++i)
            if (variables[i] == opvar)
                return values[values.size() - i - 1];

    if (isOperation) {
        return calculate(children, variables, values);
    }
}

// Oblicza wartość operacji
double Node::calculate(vector<Node> &nodeValues, vector<string> &variables, vector<int> &values) {
    if (opvar == "+")
        return nodeValues[0].compile(nodeValues[0], variables, values) + nodeValues[1].compile(nodeValues[1], variables, values);
    if (opvar == "-")
        return nodeValues[0].compile(nodeValues[0], variables, values) - nodeValues[1].compile(nodeValues[1], variables, values);
    if (opvar == "*")
        return nodeValues[0].compile(nodeValues[0], variables, values) * nodeValues[1].compile(nodeValues[1], variables, values);
    if (opvar == "/")
        return nodeValues[0].compile(nodeValues[0], variables, values) / nodeValues[1].compile(nodeValues[1], variables, values);
    if (opvar == "sin")
        return sin(nodeValues[0].compile(nodeValues[0], variables, values));
    if (opvar == "cos")
        return cos(nodeValues[0].compile(nodeValues[0], variables, values));
}

// Zwraca wskaźnik do liścia drzewa
Node* Node::getLeaf() {
    if (children.empty())
        return this;
    return children[0].getLeaf();
}