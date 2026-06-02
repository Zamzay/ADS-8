// Copyright 2021 NNTU-CS
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream readFile(filename);
  if (!readFile.is_open()) return;
  std::string curWord;
  char ch;
  while (readFile.get(ch)) {
    if (ch >= 0 && ch <= 127 && std::isalpha(static_cast<unsigned char>(ch))) {
      curWord.push_back(std::tolower(static_cast<unsigned char>(ch)));
    } else {
      if (!curWord.empty()) {
        tree.add(curWord);
        curWord.clear();
      }
    }
  }
  if (!curWord.empty()) {
    tree.add(curWord);
  }
  readFile.close();
}

void printFreq(BST<std::string>& container) {
  auto items = container.getNodesByFrequency();

  std::ofstream outFile("freq.txt");

  for (auto* node : items) {
    std::string line = node->key + " " + std::to_string(node->freq);
    std::cout << line << '\n';
    if (outFile) outFile << line << '\n';
  }
  outFile.close();
}
