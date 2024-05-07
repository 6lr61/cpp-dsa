#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../src/linked_list.hpp"

TEST_CASE("Initialize a new list") {
  LinkedList<int> list;

  REQUIRE(list.empty());
}

TEST_CASE("Add element to list") {
  LinkedList<int> list;
  list.push_front(123);

  REQUIRE(list.front() == 123);
}

TEST_CASE("Move element to list") {
  LinkedList<std::string> list;
  std::string string{"Hello, Twitch!"};
  list.push_front(std::move(string));

  REQUIRE(list.front() == "Hello, Twitch!");
  REQUIRE(string == "");
}

TEST_CASE("Clear list") {
  LinkedList<int> list;
  list.push_front(123);
  list.push_front(234);
  list.push_front(345);
  list.clear();

  REQUIRE(list.empty());
}

TEST_CASE("Create value and push to list") {
  LinkedList<std::string> list;
  std::string string = list.emplace_front("Hello, Twitch!");

  REQUIRE(string == "Hello, Twitch!");
  REQUIRE(list.front() == "Hello, Twitch!");
}

TEST_CASE("Pop a single element") {
  LinkedList<int> list;
  list.push_front(123);

  REQUIRE(!list.empty());

  list.pop_front();

  REQUIRE(list.empty());
}

TEST_CASE("Print content") {
  LinkedList<int> list;
  list.push_front(123);
  list.push_front(234);
  list.push_front(345);

  std::vector<int> vector;
  vector.assign(list.begin(), list.end());

  REQUIRE(vector == std::vector{345, 234, 123});
}
