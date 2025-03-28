#include <catch2/catch_test_macros.hpp>
#include "../src/hash_map.hpp"


TEST_CASE("Test the hashmap") {
  Hashmap<int> map{2};
  const char *str1 = "Hello, Twitch!";
  const char *str2 = "Hello, World!";
  const char *str3 = "That's a nice segfault";

  // Test: Can add new entries and overwrite old ones
  map.add(str1, 42);
  map.add(str1, 1337);
  map.add(str2, 69);
  REQUIRE(map.n_entries == 2);

  REQUIRE(*map.get(str1) == 1337);
  REQUIRE(*map.get(str2) == 69);

  // Test: Can resize hashmap
  map.resize(4);
  REQUIRE(map.n_buckets == 4);

  // Test: Can add more entries than previously would fit
  map.add(str3, 12345);
  REQUIRE(map.n_entries == 3);
  REQUIRE(*map.get(str1) == 1337);
  REQUIRE(*map.get(str2) == 69);
  REQUIRE(*map.get(str3) == 12345);

  // Test: Can delete an entry
  map.remove(str3);
  REQUIRE(map.get(str3) == NULL);

  // Test: Can add a previously deleted entry
  map.add(str3, 1234);
  REQUIRE(*map.get(str3) == 1234);

  // Test: Can clear the hashmap
  map.clear();
  REQUIRE(map.n_entries == 0); 
  for (size_t i = 0; i < map.n_buckets; i++) {
    REQUIRE(map.keys[i] == NULL);
  }
}
