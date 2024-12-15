#ifndef __S21_CONTAINERS_SET_H__
#define __S21_CONTAINERS_SET_H__

#include "s21_RBTree.h"

namespace s21 {
template <typename Key>
class set : public RBTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const Key&;
  using iterator = typename RBTree<Key, Key>::Iterator;
  using const_iterator = typename RBTree<Key, Key>::ConstIterator;
  using size_type = size_t;

  set() : RBTree<Key, Key>(){};
  set(std::initializer_list<Key> const& items) {
    for (value_type value : items) RBTree<Key, Key>::insert(value);
  };
  set(const set& other) : RBTree<Key, Key>(other){};
  set(set&& other) : RBTree<Key, Key>(std::move(other)){};
  ~set() = default;
  set& operator=(set&& s) {
    RBTree<Key, Key>::operator=(std::move(s));
    return *this;
  };

  iterator find(const key_type& key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> ret;
    (ret.push_back(s21::RBTree<int, int>::insert(std::forward<Args>(args))),
     ...);
    return ret;
  }
};

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  return RBTree<Key, Key>::find(key);
}

}  // namespace s21

#endif