// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

int main() {
    const char* filename = "war_peace.txt";
    BST<std::string> wordTree;
    makeTree(wordTree, filename);
    int treeHeight = wordTree.getHeight();
    std::cout << (treeHeight == 35) << std::endl;
    printFreq(wordTree);
    return 0;
}
