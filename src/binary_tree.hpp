#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>

template <typename T> struct Node {
  Node *left{};
  Node *right{};
  Node *parent{};
  T value;

  Node(Node *p, T v) : parent(p), value(v) {}

  auto operator<=>(const Node &node) const { return value <=> node.value; }

  auto operator<=>(const T v) const { return value <=> v; }
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

template <typename T> Node<T> *find_last(Node<T> *root, T value) {
  Node<T> *curr = root;
  Node<T> *prev = nullptr;

  while (curr != nullptr) {
    prev = curr;
    auto comp = *curr <=> value;

    if (comp > 0) {
      std::cout << curr->value << " greater than " << value << '\n';
      curr = curr->left;
    } else if (comp < 0) {
      std::cout << curr->value << " less than " << value << '\n';
      curr = curr->right;
    } else {
      std::cout << curr->value << " equal to " << value << '\n';
      return curr;
    }
  }

  return prev;
}

template <typename T> bool add_child(Node<T> *parent, Node<T> *child) {
  if (parent == nullptr || child == nullptr) {
    return false;
  }

  auto comp = *parent <=> *child;

  if (comp < 0) {
    parent->right = child;
  } else if (comp > 0) {
    parent->left = child;
  } else {
    return false;
  }

  child->parent = parent;

  return true;
}

template <typename T> bool add(Node<T> *root, T value) {
  Node<T> *parent = find_last(root, value);
  // FIXME: This is a memory leak!
  return add_child(parent, new Node<T>{nullptr, value});
}
