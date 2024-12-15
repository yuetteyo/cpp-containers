#ifndef __S21_CONTAINERS_MULTISET_H__
#define __S21_CONTAINERS_MULTISET_H__

#include "s21_RBTree.h"

namespace s21 {
template <class Key>
class multiset : public RBTree<Key, Key> {
 public:
  // Member type
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<Key, Key>::Iterator;
  using const_iterator = const typename RBTree<Key, Key>::Iterator;
  using size_type = size_t;
  using Node = typename RBTree<Key, Key>::Node;

 public:
  // Member functions
  multiset() : RBTree<Key, Key>(){};
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms) : RBTree<Key, Key>(ms){};
  multiset(multiset&& ms) : RBTree<Key, Key>(std::move(ms)){};
  ~multiset() = default;
  multiset operator=(multiset&& ms);

  // Modifiers
  iterator insert(const value_type& value);

  // Lookup - просмотр мультисета
  size_type count(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  // Additional
  iterator insertNode(Node* node);
  void merge(multiset& other);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> ret;
    (ret.push_back(std::pair(insert(std::forward<Args>(args)), true)), ...);
    return ret;
  }
};

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items) {
  for (value_type value : items) insert(value);
};

template <typename Key>
multiset<Key> multiset<Key>::operator=(multiset&& ms) {
  RBTree<Key, Key>::operator=(std::move(ms));
  return *this;
};

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  Node* node = new Node();
  node->key = value;
  node->value = value;

  return insertNode(node);
};

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  auto it = RBTree<Key, Key>::begin();
  auto end = RBTree<Key, Key>::end();
  size_type count = 0;
  while (it != end && *it != key) it++;
  while (it != end && *it++ == key) count++;
  return count;
};

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
};

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  auto start = RBTree<Key, Key>::begin();
  auto end = RBTree<Key, Key>::end();
  while (start != end && *start != key) start++;
  return start;
};

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  auto it = lower_bound(key);
  auto end = RBTree<Key, Key>::end();
  while (it != end && *it++ == key) it++;
  return it;
};

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insertNode(Node* node) {
  Node *parent = nullptr, *root = this->root;
  node->color = RBTree<Key, Key>::RED;

  while (root != nullptr) {
    parent = root;
    if (node->key < root->key)
      root = root->left;
    else
      root = root->right;
  };

  if (parent == nullptr)
    this->root = node;
  else if (node->key < parent->key)
    parent->left = node;
  else
    parent->right = node;

  node->parent = parent;

  RBTree<Key, Key>::fixInsertion(node);

  return node;
};

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  RBTree constTree(other);
  iterator it = constTree.begin();
  iterator itEnd = other.end();

  for (; it != itEnd; ++it) insert(*it);
  other.clear();
}

};  // namespace s21

#endif