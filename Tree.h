//
// Created by karol on 20.11.2023.
//

#ifndef ZADANIE3_TREE_H
#define ZADANIE3_TREE_H

#include <vector>
#include "Node.h"
#include <sstream>

using namespace std;

template<typename T>
class Tree {
private:


    vector<string> expressionVector;
    vector<string> variables;
    vector<T> values;
    Node<T> root;
    bool mistakeFound{};

    Node<T> createTree(Node<T> &node);

    int iSOperation(const string &word);

    T getCalculable(const string &word);

    static int getNumberOfOperands(const string &word);

    bool isVariableName(const string &word);

    void fillVariables();

    void printVector(vector<string> &vector);

    vector<T> fillValues(const vector<string> &expression);

    bool isCalculable(const string &word);

    bool isPositiveDouble(const string &basicString);

public:
    Tree();

    Tree(vector<string> expressionInit);
    Tree(const Tree<T> &other);
    Tree(Tree<T> &&other) ;
    void traverseTree();

    void printVariables(vector <string> variables);

    void compile(vector<string> expression);

    Tree operator=(const Tree &other)  ;
    Tree operator=(Tree &&other)  ;
    Tree operator+(const Tree &tree);


};

template<typename T>
Tree<T> Tree<T>::operator=(Tree &&other) {
    expressionVector = std::move(other.expressionVector);

    // Move variables
    variables = std::move(other.variables);

    // Move values
    values = std::move(other.values);

    // Move the root by creating a new tree with the same expression
    root = std::move(other.root);

    // Move mistakeFound
    mistakeFound = std::move(other.mistakeFound);


    return *this;
}


template<typename T>
Tree<T> Tree<T>::operator=(const Tree &other) {
    expressionVector = other.expressionVector;

    // Move variables
    variables = other.variables;

    // Move values
    values = other.values;

    // Move the root by creating a new tree with the same expression
    root = other.root;

    // Move mistakeFound
    mistakeFound = other.mistakeFound;
    return *this;

}

template<typename T>
Tree<T>::Tree(Tree<T> &&other) {

    // Move expressionVector
    expressionVector = std::move(other.expressionVector);

    // Move variables
    variables = std::move(other.variables);

    // Move values
    values =std::move (other.values);

    // Move the root by creating a new tree with the same expression
    root = std::move(other.root);

    // Move mistakeFound
    mistakeFound = std::move(other.mistakeFound);

}

template<typename T>
Tree<T>::Tree(const Tree<T> &other) {
    // Copy expressionVector
    expressionVector = other.expressionVector;

    // Copy variables
    variables = other.variables;

    // Copy values
    values = other.values;

    // Copy the root by creating a new tree with the same expression
    root = other.root;

    // Copy mistakeFound
    mistakeFound = other.mistakeFound;

}




// Sprawdza, czy słowo jest operacją
template<typename T>
inline int Tree<T>::iSOperation(const string &word) {
    return word == "+" || word == "-" || word == "*" || word == "/" || word == "sin" || word == "cos";
}

template<>
inline int Tree<string>::iSOperation(const string &word) {
    return word == "+" || word == "-" || word == "*" || word == "/";
}


//sprawdza czy słowo jest liczbą albo stringiem traktowanym za wartość
template<typename T>
inline bool Tree<T>::isCalculable(const string &word) {
    if (getCalculable(word) != -1)
        return true;
    return false;
}

template<>
inline bool Tree<string>::isCalculable(const string &word) {
    if (word[0] == '"' && word[word.size() - 1] == '"')
        return true;
    return false;
}



// Podaj liczbę argumentów danego operatora
template<typename T>
int Tree<T>::getNumberOfOperands(const string &word) {
    if (word == "+" || word == "-" || word == "*" || word == "/") {
        return 2;
    } else if (word == "sin" || word == "cos") {
        return 1;
    } else {
        return -1;
    }
}

//sprawdza czy string jest liczbą zmiennoprzecinkową
template<typename T>
bool Tree<T>::isPositiveDouble(const string &basicString) {
    int dotCount = 0;
    for (char i: basicString) {
        if (i == '.') {
            dotCount++;
            if (dotCount > 1)
                return false;
        } else if (i < '0' || i > '9')
            return false;
    }
    return true;
}


// Sprawdza, czy słowo jest poprawną nazwą zmiennej
template<typename T>
inline bool Tree<T>::isVariableName(const string &word) {
    if (isCalculable(word))
        return false;

    for (char i: word)
        if (i < 'a' || i > 'z')
            if (i < '0' || i > '9')
                return false;

    return true;
}

template<>
inline bool Tree<string>::isVariableName(const string &word) {
    if (word[0] != '"' && word[word.size() - 1] != '"')
        return true;
    return false;
}



//zwraca wartosc liczby albo stringa
template<>
inline double Tree<double>::getCalculable(const string &word) {
    if (isPositiveDouble(word))
        return stod(word);
    return -1;
}
template<>
inline int Tree<int>::getCalculable(const string &word) {
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

template<>
inline string Tree<string>::getCalculable(const string &word) {
    string withoutFirstAndLast;
    for (int i = 1; i < word.size() - 1; i++)
        withoutFirstAndLast += word[i];

    return withoutFirstAndLast;
}


// Rekurencyjnie tworzy drzewo wyrażenia
template<typename T>
Node<T> Tree<T>::createTree(Node<T> &node) {
    if (expressionVector.empty()) {
        mistakeFound = true;
        return Node<T>();
    }

    string item = expressionVector.back();
    expressionVector.pop_back();
    if (iSOperation(item)) {

        // Jeśli element to operacja, tworzy węzeł i dodaje dzieci
        node = Node<T>(true, item);
        for (int i = 0; i < getNumberOfOperands(item); ++i) {
            Node<T> nowy;
            node.addChild(createTree(nowy));
        }
        return node;
    } else if (isVariableName(item))
        return Node<T>(false, item);
    else if (isCalculable(item))
        return Node<T>(getCalculable(item));
    else {
        mistakeFound = true;
        return createTree(node);
    }
}

// Przechodzi przez drzewo używając notacji prefiksowej
template<typename T>
void Tree<T>::traverseTree() {
    root.prefixTraverse(root);
}

// Wypełnia wektor zmiennych
template<typename T>
void Tree<T>::fillVariables() {
    root.addVariables(variables);
}

// Wyświetla elementy wektora
template<typename T>
void Tree<T>::printVector(vector<string> &vector) {
    for (const string &i: vector)
        cout << i << " ";
}

// Wypełnia wektor wartości na podstawie wyrażenia
template<typename T>
vector<T> Tree<T>::fillValues(const vector<string> &expression) {
    vector<T> result;
    for (const string &i: expression)
        if (isCalculable(i))
            result.push_back(getCalculable(i));
    return result;

}


// Kompiluje wyrażenie na podstawie przekazanych wartości
template<typename T>
void Tree<T>::compile(vector<string> expression) {
    fillVariables();
    values = fillValues(expression);
    if (values.size() != variables.size()) {
        cout << "Nie mozna skompilowac, zla liczba wartosci" << endl;
    } else
        cout << root.compile(root, variables, values) << endl;
}

// Wyświetla zmienne z drzewa
template<typename T>
void Tree<T>::printVariables(vector<string> variables) {
    fillVariables();
    printVector(variables);
}

// Operator dodawania drzew
template<typename T>
Tree<T> Tree<T>::operator+(const Tree &tree) {
    *root.getLeaf() = tree.root;
    return *this;
}



// Konstruktor domyślny
template<typename T>
Tree<T>::Tree() {

}



//konstruktor z wektorem stringów
template<typename T>
Tree<T>::Tree(vector<string> expressionInit) {
    mistakeFound = false;
    expressionVector = expressionInit;

    // Tworzenie drzewa i sprawdzanie błędów
    root = createTree(root);
    if (mistakeFound)
        cout << "Niepoprawne wyrazenie zostalo poprawione" << endl;
    else
        cout << "Wyrazenie jest poprawne" << endl;
}


template
class Tree<int>;

template
class Tree<double>;

template
class Tree<string>;

#endif //ZADANIE3_TREE_H
