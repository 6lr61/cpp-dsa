#include <algorithm>
#include <cstddef>

template <typename T> struct Node {
  Node *left{};
  Node *right{};
  Node *parent{};
  T value;

  Node(Node *p, T v) : parent(p), value(v) {}
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

bool search(auto *node, auto function) {
  decltype(node) curr = node;
  decltype(node) prev = nullptr;
  decltype(node) next;

  while (curr != nullptr) {
    if (prev == curr->parent) {
      bool match = function(curr);

      if (match) {
        return match;
      }

      if (curr->left != nullptr) {
        next = curr->left;
      } else if (curr->right != nullptr) {
        next = curr->right;
      } else {
        next = curr->parent;
      }
    } else if (prev == curr->left) {
      if (curr->right != nullptr) {
        next = curr->right;
      } else {
        next = curr->parent;
      }
    } else {
      next = curr->parent;
    }

    prev = curr;
    curr = next;
  }

  return false;
}
