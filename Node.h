//
// Created by karol on 20.11.2023.
//

#ifndef ZADANIE3_NODE_H
#define ZADANIE3_NODE_H
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

template <typename T> class Node {
private:


    bool isOperation;
    T value;
    string opvar;
    vector<Node<T>> children;//vector of children
    bool isValue = false;


public:
    string removelastS2fromS1(string string1, string string2);
    void addChild(Node child);
    bool isVariable();
    string toString();
    void prefixTraverse(Node &node);
    const vector<Node> &getChildren() const;
    void addVariables(vector<string> &variables);
    Node();
    Node(T valueInit);
    Node(bool isOperationInit, string &operationInit);
    Node* getLeaf();
    string multiply(string string1, string string2);
    string divider(string string1, string string2);

    T compile(Node &node, vector<string> &variables, vector<T> &values);

    T calculate(vector<Node> &nodeValues, vector<string> &variables, vector<T> &values);
};

template<typename T>
string Node<T>::divider(string string1, string string2) {
    while(string1.find(string2) != string::npos)
        string1.erase(string1.find(string2), string2.length());
    return string1;
}

template<typename T>
string Node<T>::multiply(string string1, string string2) {
    string result;
    for(int i = 0; i < string1.length(); ++i) {
        if(string1[i]==string2[0])
            result+=string2;
        else{
            result+=string1[i];
        }
    }
    return result;
}

template<typename T>
string Node<T>::removelastS2fromS1(string string1, string string2) {
    if(string1.find(string2) == string::npos)
        return string1;
    string1.erase(string1.rfind(string2), string2.length());
    return string1;
}

template<typename T>
Node<T>::Node(T valueInit) {
    value = valueInit;
    isOperation = false;
    isValue = true;

}
template<typename T>
Node<T>::Node(bool isOperationInit, string &operationInit) {
    isOperation = isOperationInit;
    opvar = operationInit;
    isValue = false;
}





// Konstruktor domyślny
template <typename T>
inline Node<T>::Node() {
    isOperation = false;
    isValue= true;
    value=1;
}

template <>
inline Node<string>::Node() {
    isOperation = false;
    isValue= true;
    value="defuatl_vlajsdiue";
}



// Dodaje dziecko do węzła
template <typename T>
void Node<T>::addChild(Node<T> child) {
    children.push_back(child);
}

// Zwraca wektor dzieci węzła
template <typename T>
const vector<Node<T>> &Node<T>::getChildren() const {
    return children;
}

// Konwertuje węzeł na string
template <typename T>
string Node<T>::toString() {
    if (isOperation)
        return opvar;
    if (isValue == false)
        return opvar;
    else
    {
        ostringstream ss;
        ss << value;
        return ss.str();
    }
}

// Przechodzi przez drzewo w notacji prefiksowej
template <typename T>
void Node<T>::prefixTraverse(Node<T> &node) {
    cout << node.toString() << " ";
    for (Node child : node.getChildren())
        prefixTraverse(child);
}

// Sprawdza, czy węzeł reprezentuje zmienną
template <typename T>
bool Node<T>::isVariable() {
    return !isOperation && !isValue;
}

// Dodaje zmienne do wektora zmiennych
template <typename T>
void Node<T>::addVariables(vector<string> &variables) {
    if (isVariable() && variables.end() == find(variables.begin(), variables.end(), opvar))
        variables.push_back(opvar);
    for (Node child : children)
        child.addVariables(variables);
}

// Kompiluje drzewo i oblicza wartość
template <typename T>
T Node<T>::compile(Node<T> &node, vector<string> &variables, vector<T> &values) {
    if (isValue)
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
template <>
inline string Node<string>::calculate(vector<Node<string>> &nodeValues, vector<string> &variables, vector<string> &values)
{
    if(opvar == "+")
        return nodeValues[0].compile(nodeValues[0], variables, values) + nodeValues[1].compile(nodeValues[1], variables, values);
    if(opvar == "-")
       return removelastS2fromS1(nodeValues[0].compile(nodeValues[0], variables, values),
                                 nodeValues[1].compile(nodeValues[1], variables, values));
    if(opvar == "*")
        return multiply(nodeValues[0].compile(nodeValues[0], variables, values),
                        nodeValues[1].compile(nodeValues[1], variables, values));
    if(opvar == "/")
        return divider(nodeValues[0].compile(nodeValues[0], variables, values),
                       nodeValues[1].compile(nodeValues[1], variables, values));
}

template <typename T>
inline T Node<T>::calculate(vector<Node<T>> &nodeValues, vector<string> &variables, vector<T> &values) {

        if (opvar == "+")
            return nodeValues[0].compile(nodeValues[0], variables, values) +
                   nodeValues[1].compile(nodeValues[1], variables, values);
        if (opvar == "-")
            return nodeValues[0].compile(nodeValues[0], variables, values) -
                   nodeValues[1].compile(nodeValues[1], variables, values);
        if (opvar == "*")
            return nodeValues[0].compile(nodeValues[0], variables, values) *
                   nodeValues[1].compile(nodeValues[1], variables, values);
        if (opvar == "/")
            return nodeValues[0].compile(nodeValues[0], variables, values) /
                   nodeValues[1].compile(nodeValues[1], variables, values);
        if (opvar == "sin")
            return sin(nodeValues[0].compile(nodeValues[0], variables, values));
        if (opvar == "cos")
            return cos(nodeValues[0].compile(nodeValues[0], variables, values));

}

// Zwraca wskaźnik do liścia drzewa
template <typename T>
Node<T>* Node<T>::getLeaf() {
    if (children.empty())
        return this;
    return children[0].getLeaf();
}

template class Node<int>;
template class Node<double>;
template class Node<string>;
#endif //ZADANIE3_NODE_H
