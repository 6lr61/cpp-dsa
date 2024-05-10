#include <algorithm>
#include <cstddef>

template <typename T> struct Node {
  Node *left{};
  Node *right{};
  Node *parent{};
};

template <typename T> std::size_t size(Node<T> *node) {
  if (node == nullptr) {
    return 0;
  }

  return 1 + size(node->left) + size(node->right);
}

template <typename T> int height(Node<T> *node) {
  if (node == nullptr) {
    return -1;
  }

  return 1 + std::max(height(node->left), height(node->right));
}
