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
    Tree executeCommand(string &command, vector<string> &line, Tree &tree);
public:
    Interface();
    void start();
};


#endif //ZADANIE3_INTERFACE_H
