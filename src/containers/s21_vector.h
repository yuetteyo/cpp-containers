#ifndef __S21_CONTAINERS_VECTOR_H__
#define __S21_CONTAINERS_VECTOR_H__

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>

namespace s21 {
template <class T>
class vector {
 public:
  // Vector member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  // Vector Member functions
  vector() : size_(0), capacity_(5), arrPtr_(new value_type[capacity_]{}) {}

  vector(size_type n) {
    size_ = n;
    capacity_ = n;
    if (size_ > 0) {
      arrPtr_ = new value_type[n]{};
    }
  }

  vector(std::initializer_list<value_type> const &items)
      : size_(items.size()),
        capacity_(items.size()),
        arrPtr_(new value_type[capacity_]{}) {
    std::copy(items.begin(), items.end(), arrPtr_);
  }

  vector(const vector &v)
      : size_(v.size_),
        capacity_(v.capacity_),
        arrPtr_(new value_type[capacity_]{}) {
    std::copy(v.begin(), v.end(), arrPtr_);
  }

  vector(vector &&v)
      : size_(v.size_), capacity_(v.capacity_), arrPtr_(v.arrPtr_) {
    v.size_ = 0;
    v.capacity_ = 0;
    v.arrPtr_ = nullptr;
  }

  ~vector() {
    if (arrPtr_) delete[] arrPtr_;
  }

  vector operator=(vector &&v) {
    if (this != &v) {
      if (arrPtr_) {
        delete[] arrPtr_;
      }
      size_ = v.size_;
      capacity_ = v.capacity_;
      arrPtr_ = v.arrPtr_;
      v.size_ = 0;
      v.capacity_ = 0;
      v.arrPtr_ = nullptr;
    }
    return *this;
  }

  // Vector Element access
  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Memory error: no such element");
    }
    return arrPtr_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range("Memory error: no such element");
    }
    return arrPtr_[pos];
  }

  reference operator[](size_type pos) { return arrPtr_[pos]; }

  const_reference front() const { return arrPtr_[0]; }

  const_reference back() const { return arrPtr_[size_ - 1]; }

  T *data() { return arrPtr_; }

  // Vector Iterators
  iterator begin() { return arrPtr_; }
  iterator end() { return arrPtr_ + size_; }
  const_iterator begin() const { return arrPtr_; }
  const_iterator end() const { return arrPtr_ + size_; }

  // Capacity
  size_type size() { return size_; }

  bool empty() { return size_ == 0; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(size_type);
  }

  void reserve(size_type size) {
    if (size > max_size()) {
      std::length_error("Reserve Error: max size exceeded");
    }
    if (size > capacity_) {
      iterator tmp = arrPtr_;
      arrPtr_ = new value_type[size]{};
      for (size_type i = 0; i < size_; ++i) {
        arrPtr_[i] = tmp[i];
      }
      delete[] tmp;
      capacity_ = size;
    }
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      iterator tmp = arrPtr_;
      arrPtr_ = new value_type[size_]{};
      for (size_type i = 0; i < size_; ++i) {
        arrPtr_[i] = tmp[i];
      }
      delete[] tmp;
      capacity_ = size_;
    }
  }

  // Vector Modifiers
  void clear() { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    if (capacity_ == size_) {
      size_type index = pos - begin();
      reserve(capacity_ * 2);
      pos = begin() + index;
    }
    value_type prev = value;
    for (iterator it = pos; it <= end(); ++it) {
      if (it < end()) {
        value_type curr = *it;
        *it = prev;
        prev = curr;
      } else {
        *it = prev;
      }
    }
    size_++;
    return pos;
  }

  void erase(iterator pos) {
    if (pos >= begin() && pos < end()) {
      for (iterator it = pos; it < end() - 1; ++it) {
        *it = *(it + 1);
      }
      size_--;
    }
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      reserve(capacity_ * 2);
    }
    arrPtr_[size_] = value;
    size_++;
  }

  void pop_back() {
    if (size_) size_--;
  }

  void swap(vector &other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(arrPtr_, other.arrPtr_);
  }

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args) {
    iterator new_pos = ++pos;
    auto elems = {std::forward<Args>(args)...};
    for (auto it = std::make_reverse_iterator(elems.end()),
              rend = std::make_reverse_iterator(elems.begin());
         it != rend; ++it) {
      new_pos = insert(new_pos, std::move(*it));
    }
    return new_pos;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }

 private:
  size_type size_;
  size_type capacity_;
  iterator arrPtr_;
};
};  // namespace s21

#endif  // __S21_CONTAINERS_VECTOR_H__