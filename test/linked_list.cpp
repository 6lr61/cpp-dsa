#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <functional>
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

TEST_CASE("Assign to vector using iterators") {
  LinkedList<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);

  std::vector<int> vector;
  vector.assign(list.begin(), list.end());

  REQUIRE(vector == std::vector{3, 2, 1});
}

TEST_CASE("Print content") {
  LinkedList<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);

  list.reverse();

  std::vector<int> vector;
  vector.assign(list.begin(), list.end());

  REQUIRE(vector == std::vector{1, 2, 3});
}

TEST_CASE("Sort a list of numbers") {
  LinkedList<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  list.push_front(5);

  list.sort();

  std::vector<int> vector;
  vector.assign(list.begin(), list.end());

  REQUIRE(vector == std::vector{1, 2, 3, 4, 5});
}

TEST_CASE("Sort a list of strings") {
  LinkedList<std::string> list;
  list.push_front("A");
  list.push_front("C");
  list.push_front("D");
  list.push_front("B");
  list.push_front("E");

  list.sort();

  std::vector<std::string> vector;
  vector.assign(list.begin(), list.end());

  REQUIRE(vector == std::vector<std::string>{"A", "B", "C", "D", "E"});
}

TEST_CASE("Sort a list of numbers using a supplied comparsion function") {
  LinkedList<int> list;
  list.push_front(5);
  list.push_front(4);
  list.push_front(3);
  list.push_front(2);
  list.push_front(1);

  list.sort(std::greater<int>{});

  std::vector<int> vector;
  vector.assign(list.begin(), list.end());

  REQUIRE(vector == std::vector{5, 4, 3, 2, 1});
}

TEST_CASE("Sort a list with a single element") {
  LinkedList<int> list;
  list.push_front(1);

  list.sort();

  REQUIRE(list.front() == 1);
}
