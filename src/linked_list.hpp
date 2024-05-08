#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <algorithm>
#include <functional>
#include <utility>

template <typename T> class LinkedList {
private:
  struct Node {
    Node *next = nullptr;
    T value;

    Node(T v) : value(std::move(v)){};

    ~Node() = default;
  };

  Node *head = nullptr;

  class Iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using element_type = T;
    using value_type = T;
    using pointer = Node *;
    using reference = T &;

  private:
    Node *node = nullptr;
    Node *sentinel = nullptr;
    static_assert(std::sentinel_for<decltype(sentinel), decltype(node)>);

  public:
    Iterator() {}

    Iterator(pointer n) : node(n) {}

    reference operator*() const { return node->value; }

    pointer operator->() const { return node; }

    Iterator &operator++() {
      if (node != sentinel) {
        node = node->next;
      }

      return *this;
    }

    Iterator operator++(int) {
      auto old = *this;
      ++(*this);
      return old;
    }

    bool operator==(const Iterator &iterator) const {
      return node == iterator.node;
    };
  };

  static_assert(std::forward_iterator<Iterator>);

public:
  LinkedList() = default;

  ~LinkedList() { clear(); }

  void clear() {
    Node *current = head;

    while (current) {
      Node *previous = current;
      current = current->next;
      delete previous;
    }

    head = nullptr;
  }

  Iterator begin() const { return Iterator{head}; }

  Iterator end() const { return Iterator{nullptr}; }

  bool empty() { return head == nullptr; }

  T &front() { return head->value; }

  void push_front(T value) {
    Node *node = new Node(std::move(value));

    if (empty()) {
      head = node;
    } else {
      node->next = head;
      head = node;
    }
  }

  template <class... Args> T &emplace_front(Args &&...args) {
    T value(std::forward<Args>(args)...);

    push_front(std::move(value));

    return front();
  }

  void pop_front() noexcept {
    if (!empty()) {
      Node *next = head->next;
      delete head;
      head = next;
    }
  }

  void reverse() noexcept {
    Node *previous = nullptr;
    Node *current = head;
    Node *next;

    while (current) {
      next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }

    head = previous;
  }

  void sort() { sort(std::less<T>{}); }

  template <typename Compare> void sort(Compare comp) {
    if (empty()) {
      return;
    }

    Node *prev = nullptr;
    Node *curr = head;
    Node *last = nullptr;

    while (head != last) {
      curr = head;

      while (curr->next != last) {
        Node *next = curr->next;

        if (!comp(curr->value, next->value)) {
          // Swap elements
          if (head == curr) {
            head = next;
          } else {
            prev->next = next;
          }

          curr->next = next->next;
          next->next = curr;
        }

        prev = curr;
        curr = next;
      }

      last = curr;
    }
  }
};

#endif
