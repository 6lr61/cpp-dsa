#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <cstring>

#define TOMBSTONE ((char*)(nullptr) + 0x1u)

template <typename T>
struct Hashmap {
  static size_t hash(const char* key, size_t n_buckets);

  Hashmap(size_t n_buckets);
  ~Hashmap();
  size_t n_entries;
  size_t n_buckets;
  const char **keys;
  T *values;
  size_t find_next_index(const char *key, bool skip_tombstone) const;
  void add(const char *key, T value);
  void clear();
  void remove(const char *key);
  T *get(const char* key) const;
  void resize(size_t size);
};

template <typename T>
Hashmap<T>::Hashmap(size_t n_buckets) {
  // A hashmap contains at least one entry
  assert(n_buckets >= 1);

  n_entries = 0;
  this->n_buckets = n_buckets;
  keys = (const char**)std::calloc(n_buckets, sizeof(char*));
  values = (T*)std::calloc(n_buckets, sizeof(T));
}

template <typename T>
Hashmap<T>::~Hashmap() {
  std::free(this->keys);
  this->keys = nullptr;
  std::free(this->values);
  this->values = nullptr;
}

template <typename T>
size_t Hashmap<T>::hash(const char* key, size_t n_buckets) {
  // Modular hashing taken from:
  // https://algs4.cs.princeton.edu/34hash/
  size_t hash = 0;
  const size_t R = 31; // A small prime integer
  
  for (size_t i = 0; key[i] != '\0'; i++) {
    hash = (R * hash + (size_t)key[i]) % n_buckets;
  } 

  return hash;
}

template <typename T>
size_t Hashmap<T>::find_next_index(const char *key, bool skip_tombstone) const {
  size_t hash = Hashmap<T>::hash(key, this->n_buckets);

  for (size_t n = 0; n < this->n_buckets; n++) {
    size_t i = (hash + n) % this->n_buckets; 

    if (this->keys[i] == TOMBSTONE) {
      if (skip_tombstone) {
        continue;
      }

      return i;
    }

    if (this->keys[i] == nullptr) {
      return i;
    }

    if (std::strcmp(this->keys[i], key) == 0) {
      return i;
    }
  }

  return (size_t)(-1);
}

template <typename T>
void Hashmap<T>::add(const char *key,
                  T value) {
  size_t i = this->find_next_index(key, false);

  assert(i != (size_t)(-1));

  if (this->keys[i] == nullptr) {
    this->n_entries++;
  }

  this->keys[i] = key; 
  this->values[i] = value;
} 

template <typename T>
T *Hashmap<T>::get(const char* key) const {
  size_t i = this->find_next_index(key, true);

  if (i == (size_t)(-1) || this->keys[i] == nullptr) {
    return nullptr;
  }

  return &(this->values[i]);
}

template <typename T>
void Hashmap<T>::clear() {
  for (size_t i = 0; i < this->n_buckets; i++) {
    this->keys[i] = nullptr;
  }

  this->n_entries = 0;
}

template <typename T>
void Hashmap<T>::resize(size_t size) {
  auto old_keys = this->keys;
  auto old_values = this->values;
  auto old_n_buckets = this->n_buckets;

  *this = { size };

  for (size_t i = 0; i < old_n_buckets; i++) {
    if (old_keys[i] == nullptr) {
      continue;
    }

    this->add(old_keys[i], old_values[i]);
  }

  free(old_keys);
  free(old_values);
}

template <typename T>
void Hashmap<T>::remove(const char *key) {
  size_t i = this->find_next_index(key, false);

  if (this->keys[i] == nullptr || this->keys[i] == TOMBSTONE) {
    return; // There's no such key
  }

  this->keys[i] = TOMBSTONE;
  this->n_entries--;
}

#endif
