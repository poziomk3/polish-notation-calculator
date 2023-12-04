//
// Created by karol on 21.11.2023.
//

#ifndef ZADANIE3_INTERFACE_H
#define ZADANIE3_INTERFACE_H
#include <vector>
#include "Tree.h"

using namespace std;
class Interface {
private:
    vector<string> convertToVector(string expression);
public:
    Interface();
    void start();

    template<typename T>
    void looper(Tree<T> &tree);

    template<typename T>
    Tree<T> executeCommand(string &command, vector<string> &line, Tree<T> &tree);
};


#endif //ZADANIE3_INTERFACE_H
