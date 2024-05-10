#include <catch2/catch_test_macros.hpp>

#include "../src/binary_tree.hpp"

TEST_CASE("Intialize a tree of size 3 and height 2") {
  Node<int> root;
  Node<int> left;
  Node<int> right;
  Node<int> left_left;

  root.left = &left;
  root.right = &right;

  left.left = &left_left;

  REQUIRE(size(&root) == 4);
  REQUIRE(height(&root) == 2);
}
