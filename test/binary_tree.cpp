#include <catch2/catch_test_macros.hpp>
#include <cstddef>

#include "../src/binary_tree.hpp"

TEST_CASE("Intialize a tree of size 3 and height 2") {
  Node<int> root{nullptr, 1};
  Node<int> left{&root, 2};
  Node<int> right{&root, 3};
  Node<int> left_left{&left, 4};

  root.left = &left;
  root.right = &right;

  left.left = &left_left;

  REQUIRE(size(&root) == 4);
  REQUIRE(height(&root) == 2);
}

TEST_CASE("Traverse and count number nodes") {
  Node<int> root{nullptr, 1};
  Node<int> left{&root, 2};
  Node<int> right{&root, 3};
  Node<int> left_left{&left, 4};

  root.left = &left;
  root.right = &right;

  left.left = &left_left;

  std::size_t n_nodes = 0;
  auto count = [&n_nodes](auto *) {
    n_nodes++;
    return false;
  };

  search(&root, count);

  REQUIRE(size(&root) == n_nodes);
}

TEST_CASE("Traverse and sum all values") {
  Node<int> root{nullptr, 1};
  Node<int> left{&root, 2};
  Node<int> right{&root, 3};
  root.left = &left;
  root.right = &right;

  int sum = 0;
  auto function = [&sum](auto *node) {
    sum += node->value;
    return false;
  };

  search(&root, function);

  REQUIRE(sum == 6);
}

TEST_CASE("Find a specific node") {
  Node<int> root{nullptr, 1};
  Node<int> left{&root, 2};
  Node<int> right{&root, 3};
  root.left = &left;
  root.right = &right;

  REQUIRE(search(&root, [](auto *node) { return node->value == 3; }));
}

TEST_CASE("Find the last node") {
  Node<int> root{nullptr, 5};
  Node<int> left{&root, 3};
  Node<int> right{&root, 7};
  root.left = &left;
  root.right = &right;

  REQUIRE(find_last(&root, 2)->value == 3);
  REQUIRE(find_last(&root, 8)->value == 7);
  REQUIRE(find_last(&root, 3)->value == 3);
}

TEST_CASE("Add smaller child to left branch") {
  Node<int> parent{nullptr, 3};
  Node<int> child{nullptr, 1};

  REQUIRE(add_child(&parent, &child));
  REQUIRE(child.parent == &parent);
  REQUIRE(parent.left == &child);
}

TEST_CASE("Add bigger child to right branch") {
  Node<int> parent{nullptr, 3};
  Node<int> child{nullptr, 5};

  REQUIRE(add_child(&parent, &child));
  REQUIRE(child.parent == &parent);
  REQUIRE(parent.right == &child);
}

TEST_CASE("Don't add equal child to any branch") {
  Node<int> parent{nullptr, 3};
  Node<int> child{nullptr, 3};

  REQUIRE(!add_child(&parent, &child));
  REQUIRE(child.parent == nullptr);
  REQUIRE(parent.left == nullptr);
  REQUIRE(parent.right == nullptr);
}

TEST_CASE("Build a binary tree") {
  Node<int> parent{nullptr, 5};

  REQUIRE(add<int>(&parent, 3));
  REQUIRE(add<int>(&parent, 7));
  REQUIRE(add<int>(&parent, 2));

  REQUIRE(parent.left->value == 3);
  REQUIRE(parent.left->left->value == 2);
  REQUIRE(parent.right->value == 7);
}
