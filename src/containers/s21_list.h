#ifndef __S21_CONTAINERS_LIST_H__
#define __S21_CONTAINERS_LIST_H__

#include <iostream>
#include <limits>
#include <utility>

namespace s21 {
template <typename T>
class list {
 public:
  template <typename U>
  struct ListNode {
    T value_ = T();
    ListNode* previous_ = nullptr;
    ListNode* next_ = nullptr;
    explicit ListNode(T value = T(), ListNode* previous = nullptr,
                      ListNode* next = nullptr)
        : value_(value), previous_(previous), next_(next) {}
  };

  template <typename U>
  class ListIterator {
   public:
    using ListNode = typename s21::list<T>::ListNode<U>*;
    ListIterator(ListNode node) : current_(node) {}
    T& operator*() { return current_->value_; }
    ListIterator& operator++() {
      current_ = current_->next_;
      return *this;
    }
    ListIterator& operator--() {
      current_ = current_->previous_;
      return *this;
    }
    bool operator==(const ListIterator& other) const {
      return current_ == other.current_;
    }
    bool operator!=(const ListIterator& other) const {
      return !(*this == other);
    }
    ListNode current_;
  };

  template <typename U>
  class ListConstIterator {
   public:
    using ListNode = const typename s21::list<T>::ListNode<T>*;
    ListConstIterator(ListNode node) : current_(node) {}
    const T& operator*() const { return current_->value_; }
    ListConstIterator& operator++() {
      current_ = current_->next_;
      return *this;
    }
    ListConstIterator& operator--() {
      current_ = current_->previous_;
      return *this;
    }
    bool operator==(const ListConstIterator& other) const {
      return current_ == other.current_;
    }
    bool operator!=(const ListConstIterator& other) const {
      return !(*this == other);
    }
    ListNode current_;
  };

  // list member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using pointer = ListNode<T>*;

  // list functions
  list() : head_(new ListNode<T>(value_type())), end_(head_), size_(0) {}

  list(size_type n) : end_(new ListNode<T>(value_type())), size_(0) {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
    if (n > 0) {
      tail_->next_ = end_;
    }
  }

  list(std::initializer_list<value_type> const& items)
      : end_(new ListNode<T>(value_type())), size_(0) {
    for (const auto& item : items) {
      push_back(item);
    }
  }

  // copy constructor
  list(const list& l) : end_(new ListNode<T>(value_type())), size_(0) {
    for (const auto& item : l) {
      push_back(item);
    }
  }

  // move constructor
  list(list&& l) {
    if (this != &l) {
      clear();
      end_ = l.end_;
      tail_ = l.tail_;
      head_ = l.head_;
      size_ = l.size_;
      l.end_ = nullptr;
      l.tail_ = nullptr;
      l.head_ = nullptr;
      l.size_ = 0;
    }
  }
  // destructor
  ~list() {
    clear();
    delete end_;
  }

  list operator=(list&& l) {
    if (this != &l) {
      clear();
      if (end_) delete end_;
      if (head_) delete head_;
      end_ = l.end_;
      tail_ = l.tail_;
      head_ = l.head_;
      size_ = l.size_;
      l.end_ = nullptr;
      l.tail_ = nullptr;
      l.head_ = nullptr;
      l.size_ = 0;
    }
    return *this;
  }

  // list element access
  const_reference front() const {
    if (!empty()) {
      return *begin();
    } else {
      throw std::out_of_range("List is empty.");
    }
  }

  const_reference back() const {
    if (!empty()) {
      return *(--end());
    } else {
      throw std::out_of_range("List is empty.");
    }
  }

  // list iterators
  iterator begin() const { return iterator(head_); }
  const_iterator cbegin() const { return const_iterator(head_); }
  iterator end() const { return iterator(end_); }
  const_iterator cend() const { return const_iterator(end_); }

  // list capacity
  bool empty() const { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() { return std::numeric_limits<size_type>::max(); }

  // list modifiers
  void clear() {
    while (size_ != 0) {
      pop_back();
    }
  }

  iterator insert(iterator pos, const_reference value) {
    ListNode<value_type>* newNode = new ListNode<value_type>(value);

    newNode->previous_ = pos.current_->previous_;
    if (pos.current_->previous_)
      pos.current_->previous_->next_ = newNode;
    else
      head_ = newNode;
    pos.current_->previous_ = newNode;

    newNode->next_ = pos.current_;

    if (pos.current_ == end_) tail_ = newNode;

    --pos;
    size_++;
    return pos;
  }

  void erase(iterator pos) {
    if (pos.current_->previous_)
      pos.current_->previous_->next_ = pos.current_->next_;
    else
      head_ = pos.current_->next_;

    pos.current_->next_->previous_ = pos.current_->previous_;

    if (pos.current_ == tail_) {
      if (pos.current_->previous_)
        tail_ = pos.current_->previous_;
      else
        tail_ = end_;
    }

    delete pos.current_;
    size_--;
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(iterator(tail_)); }

  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() { erase(iterator(head_)); }

  void swap(list& other) {
    pointer temp_head_ = other.head_;
    pointer temp_tail_ = other.tail_;
    pointer temp_end_ = other.end_;
    size_type temp_size_ = other.size_;
    other.head_ = this->head_;
    other.tail_ = this->tail_;
    other.end_ = this->end_;
    other.size_ = this->size_;
    this->head_ = temp_head_;
    this->tail_ = temp_tail_;
    this->end_ = temp_end_;
    this->size_ = temp_size_;
  }

  void merge(list& other) {
    if (!head_ || !other.head_) {
      return;
    }
    list<value_type> temp;
    auto current1 = begin();
    auto current2 = other.begin();
    while (current1 != end() && current2 != other.end()) {
      if (*current1 < *current2) {
        temp.push_back(*current1);
        ++current1;
      } else {
        temp.push_back(*current2);
        ++current2;
      }
    }
    while (current1 != end()) {
      temp.push_back(*current1);
      ++current1;
    }
    while (current2 != other.end()) {
      temp.push_back(*current2);
      ++current2;
    }
    clear();
    other.clear();
    for (auto& elem : temp) {
      push_back(elem);
    }
  }

  void splice(const_iterator pos, list& other) {
    iterator temp = iterator(pos.node_);
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      insert(temp, *iter);
    }
  }

  void reverse() {
    if (size_ <= 1) {
      return;
    }
    ListNode<value_type>* newHead = tail_;
    ListNode<value_type>* newTail = head_;
    ListNode<value_type>* prev = nullptr;
    ListNode<value_type>* current = head_;
    while (current != nullptr) {
      ListNode<value_type>* next = current->next_;
      current->next_ = prev;
      current->previous_ = next;
      prev = current;
      current = next;
    }
    head_ = newHead;
    tail_ = newTail;
    head_->previous_ = nullptr;
    tail_->next_ = end_;
    end_->previous_ = tail_;
  }

  void unique() {
    if (!(size_ <= 1)) {
      auto current = begin();
      auto next = current;
      ++next;
      while (next != end()) {
        if (*current == *next) {
          erase(next);
          next = current;
          ++next;
        } else {
          current = next;
          ++next;
        }
      }
    }
  }

  void sort() {
    if (!(size_ <= 1)) {
      list* left = new list();
      list* right = new list();
      auto current = begin();
      for (size_t i = 0; i < size_ / 2; i++) {
        left->push_back(*current);
        ++current;
      }
      for (size_t i = size_ / 2; i < size_; i++) {
        right->push_back(*current);
        ++current;
      }
      left->sort();
      right->sort();
      clear();
      merge(*left);
      merge(*right);
      delete left;
      delete right;
    }
  }

  template <typename... Args>
  iterator insert_many(iterator pos, Args&&... args) {
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
  void insert_many_back(Args&&... args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (push_front(std::forward<Args>(args)), ...);
  }

 private:
  pointer head_ = nullptr;
  pointer tail_ = nullptr;
  pointer end_ = nullptr;
  size_type size_ = 0;
};
};  // namespace s21

#endif