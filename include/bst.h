// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <vector>
#include <string>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct TreeNode {
  T key;
  int freq;
  TreeNode* left;
  TreeNode* right;
  explicit TreeNode(const T& k) : key(k), freq(1), left(nullptr), right(nullptr) {}
  };
  TreeNode* treeRoot;
  TreeNode* insertRec(TreeNode* node, const T& value) {
    if (!node) return new TreeNode(value);

    if (value < node->key) node->left = insertRec(node->left, value);

    else if (value > node->key)
      node->right = insertRec(node->right, value);

    else node->freq++;

    return node;
  }
  TreeNode* findRec(TreeNode* node, const T& value) const {
    if (!node) return nullptr;
    if (value == node->key) return node;
    if (value < node->key) return findRec(node->left, value);
    return findRec(node->right, value);
  }

  int heightRec(TreeNode* node) const {
    if (!node) return -1;
    int leftH = heightRec(node->left);
    int rightH = heightRec(node->right);
    return 1 + (leftH > rightH ? leftH : rightH);
  }

  void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
  void gatherNodes(TreeNode* node, std::vector<TreeNode*>& container) const {
    if (!node) return;
    gatherNodes(node->right, container);
    container.push_back(node);
    gatherNodes(node->left, container);
  }

 public:
  BST() : treeRoot(nullptr) {}
  ~BST() {
    deleteTree(treeRoot);
  }
  void add(const T& value) {
    treeRoot = insertRec(treeRoot, value);
  }
  int getFrequency(const T& value) const {
    TreeNode* node = findRec(treeRoot, value);
    return node ? node->freq : 0;
  }
  int getHeight() const {
    return heightRec(treeRoot);
  }

  bool isEmpty() const {
    return treeRoot == nullptr;
  }
  std::vector<TreeNode*> getNodesByFrequency() const {
    std::vector<TreeNode*> nodes;
    gatherNodes(treeRoot, nodes);
    std::sort(nodes.begin(), nodes.end(),
      [](const TreeNode* a, const TreeNode* b) {
        if (a->freq != b->freq)
          return a->freq > b->freq;
        return a->key < b->key;
      });
    return nodes;
  }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

#endif  // INCLUDE_BST_H_
