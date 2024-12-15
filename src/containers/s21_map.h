#ifndef __S21_CONTAINERS_MAP_H__
#define __S21_CONTAINERS_MAP_H__

#include "s21_RBTree.h"

namespace s21 {
template <typename Key, typename T>
class map : public RBTree<Key, T> {
 public:
  // Member types
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const Key, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<Key, T>::Iterator;
  using const_iterator = typename RBTree<Key, T>::ConstIterator;
  using size_type = size_t;
  using Node = typename RBTree<Key, T>::Node;

  // Member functions
  map() : RBTree<Key, T>(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &m) : RBTree<Key, T>(m){};
  map(map &&m) : RBTree<Key, T>(std::move(m)){};
  ~map() = default;
  map &operator=(map &&m) = default;

  // Element access
  T &at(const Key &key);
  T &operator[](const Key &key);

  // Modifiers
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> ret;
    (ret.push_back(insert(std::forward<Args>(args))), ...);
    return ret;
  }
};

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) {
  map();
  for (auto &item : items) insert(item.first, item.second);
}

template <typename Key, typename T>
T &map<Key, T>::operator[](const Key &key) {
  return RBTree<Key, T>::contains(key) ? *(RBTree<Key, T>::find(key))
                                       : *(insert(key, mapped_type()).first);
}

template <typename Key, typename T>
T &map<Key, T>::at(const Key &key) {
  if (!RBTree<Key, T>::contains(key))
    throw std::out_of_range("no such element exists");
  return *(RBTree<Key, T>::find(key));
}

template <typename Key, typename T>
typename std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  Node *node = new Node();
  node->key = value.first;
  node->value = value.second;

  std::pair<Node *, bool> inserResult = RBTree<Key, T>::insertNode(node);
  bool isInserted = inserResult.second;

  iterator it = iterator(inserResult.first);
  std::pair<iterator, bool> insertResult(it, isInserted);
  if (!isInserted) delete node;

  return insertResult;
}

template <typename Key, typename T>
typename std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  Node *node = new Node();
  node->key = key;
  node->value = obj;

  std::pair<Node *, bool> inserResult = RBTree<Key, T>::insertNode(node);
  bool isInserted = inserResult.second;

  iterator it = iterator(inserResult.first);
  std::pair<iterator, bool> insertResult(it, isInserted);
  if (!isInserted) delete node;

  return insertResult;
}

template <typename Key, typename T>
typename std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  std::pair<iterator, bool> result{nullptr, true};
  if (RBTree<Key, T>::contains(key)) {
    RBTree<Key, T>::deleteNode(RBTree<Key, T>::search(this->root, key));
    result.second = false;
  }
  result.first = insert(key, obj).first;
  return result;
}

}  // namespace s21

#endif