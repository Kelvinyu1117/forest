#pragma once
#include <algorithm>
#include <memory>

namespace forest {

template <typename T> struct LinkedBinarySearchTreeNode {
  T _value;
  LinkedBinarySearchTreeNode *_parent;
  LinkedBinarySearchTreeNode *_left;
  LinkedBinarySearchTreeNode *_right;

  constexpr static LinkedBinarySearchTreeNode *
  min_node(LinkedBinarySearchTreeNode *p) {
    if (!p)
      return p;

    while (p->_left) {
      p = p->_left;
    }

    return p;
  }

  constexpr static LinkedBinarySearchTreeNode *
  max_node(LinkedBinarySearchTreeNode *p) {
    if (!p)
      return p;

    while (p->_right) {
      p = p->_right;
    }

    return p;
  }
};
template <typename T, typename Compare = std::less<T>,
          typename Alloc = std::allocator<LinkedBinarySearchTreeNode<T>>>
class LinkedBinarySearchTree {
private:
  template <typename... Args>
  constexpr LinkedBinarySearchTreeNode<T> *construct_node(Args &&...args) {
    auto *node = _allocator.allocate(1);
    ::new (node) LinkedBinarySearchTreeNode<T>(std::forward<Args>(args)...);
    return node;
  }

  constexpr void destory_node(LinkedBinarySearchTreeNode<T> *p) {
    _allocator.destory(p);
    _allocator.deallocate(p);
  }

public:
  constexpr LinkedBinarySearchTree() : _root{}, _cmp(Compare()), _allocator() {}

  struct Iterator {
    LinkedBinarySearchTreeNode<T> *_curr;

    constexpr Iterator &operator--() {
      if (!_curr) {
        _curr = _curr->_right;
      } else if (!_curr->_left) {
        auto parent = _curr->_parent;
        while (parent && _curr == parent->_left) {
          _curr = parent;
          parent = _curr->_parent;
        }

        if (_curr)
          _curr = parent;
      } else {
        _curr = LinkedBinarySearchTreeNode<T>::max_node(_curr->_left);
      }

      return *this;
    }

    constexpr Iterator &operator++() {
      if (!_curr->_right) {
        auto parent = _curr->_parent;
        while (parent && _curr == parent->_right) {
          _curr = parent;
          parent = _curr->_parent;
        }
        _curr = parent;
      } else {
        _curr = LinkedBinarySearchTreeNode<T>::min_node(_curr->_right);
      }

      return *this;
    }

    bool operator==(const Iterator &it) const { return it._curr == _curr; }
    bool operator!=(const Iterator &it) const { return !(it == *this); }
    T &operator*() { return _curr->_value; }
  };

  constexpr auto insert(const T &value) -> std::pair<Iterator, bool> {
    return insert_impl(construct_node(value));
  }

  constexpr auto insert(T &&value) noexcept -> std::pair<Iterator, bool> {
    return insert_impl(construct_node(std::move(value)));
  }

  constexpr auto find(const T &target) -> Iterator {
    LinkedBinarySearchTree *it = _root;

    while (it && it->_value != target) {
      if (_cmp(it->_value, target))
        it = it->_left;
      else
        it = it->_right;
    }

    return Iterator{it};
  }

  constexpr auto begin() -> Iterator { return Iterator{LinkedBinarySearchTreeNode<T>::min_node(_root)}; }
  constexpr auto end() -> Iterator { return Iterator{nullptr}; }

private:
  constexpr auto insert_impl(LinkedBinarySearchTreeNode<T> *node)
      -> std::pair<Iterator, bool> {
    if (!_root) {
      _root = node;
      return {Iterator{_root}, true};

    } else {
      LinkedBinarySearchTreeNode<T> *it = _root;
      LinkedBinarySearchTreeNode<T> *parent = nullptr;
      while (it) {
        parent = it;
        bool is_less_than = _cmp(node->_value, it->_value);
        bool is_greater_than = _cmp(it->_value, node->_value);
        if (is_less_than)
          it = it->_left;
        else if (is_greater_than)
          it = it->_right;
        else {
          return {Iterator{it}, false};
        };
      }

      bool is_less_than = _cmp(node->_value, parent->_value);
      if (is_less_than) {
        parent->_left = node;
        node->_parent = parent;
      } else {
        parent->_right = node;
        node->_parent = parent;
      }

      return {Iterator{node}, true};
    }
  }

private:
  LinkedBinarySearchTreeNode<T> *_root;
  Compare _cmp;
  Alloc _allocator;
};
} // namespace forest
