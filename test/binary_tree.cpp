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
