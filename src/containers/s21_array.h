#ifndef __S21_CONTAINERS_ARRAY_H__
#define __S21_CONTAINERS_ARRAY_H__

#include <iostream>
#include <utility>

#include "s21_iterator.h"

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  friend ArrayIterator<T, N>;
  // Member type
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using cons_iterator = const value_type *;
  using size_type = size_t;

  // Member functions
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a) = default;
  array(array &&a) = default;
  ~array() = default;
  array &operator=(array &&a) = default;

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() { return data_[0]; };
  const_reference back() { return data_[N - 1]; };
  iterator data() { return begin(); };

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty() { return !size_; };
  size_type size() { return size_; };
  size_type max_size() { return size(); };

  // Modifiers
  void swap(array &other);
  void fill(const_reference value);

 private:
  value_type data_[N];
  size_type size_ = N;
  ArrayIterator<T, N> iter_;
};

template <typename T, size_t N>
array<T, N>::array() : iter_(ArrayIterator<T, N>(&(data_[0]))) {
  for (size_t i = 0; i < N; i++) data_[i] = T();
};

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items)
    : array<T, N>::array() {
  auto it = begin();
  for (auto &item : items) *it++ = item;
};

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("No such element exists");
  return data_[pos];
};

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
};

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return iter_.begin();
};

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return iter_.end();
};

template <typename T, size_t N>
void array<T, N>::swap(array &other) {
  std::swap(data_, other.data_);
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; i++) data_[i] = value;
};

}  // namespace s21

#endif