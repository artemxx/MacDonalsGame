#pragma once

#include <iostream>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <algorithm>

template<typename T>
class BiDirectionalList {
 protected:
  struct Node;

 public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
   public:
    T& operator*() const;
    T* operator->() const;

    Iterator& operator++();
    const Iterator operator++(int);

    Iterator& operator--();
    const Iterator operator--(int);

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

   private:
    friend class BiDirectionalList;

    const BiDirectionalList* const list_;
    Node* node_;

    Iterator(const BiDirectionalList* const list, Node* node)
        : list_(list), node_(node) {}
  };

  class ConstIterator :
      public std::iterator<std::bidirectional_iterator_tag, T> {
   public:
    const T& operator*() const;
    const T* operator->() const;

    ConstIterator& operator++();
    const ConstIterator operator++(int);

    ConstIterator& operator--();
    const ConstIterator operator--(int);

    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;

   private:
    friend class BiDirectionalList;

    const BiDirectionalList* const list_;
    const Node* node_;

    ConstIterator(const BiDirectionalList* const list, Node* node)
        : list_(list), node_(node) {}
  };

  BiDirectionalList() : first_(nullptr), last_(nullptr) {}

  ~BiDirectionalList() { Clear(); }

  bool IsEmpty() const;

  void Clear();

  Iterator begin();
  Iterator end();

  ConstIterator begin() const;
  ConstIterator end() const;

  std::vector<T> AsArray() const;

  void InsertBefore(Iterator position, const T& value);
  void InsertBefore(Iterator position, T&& value);

  void InsertAfter(Iterator position, const T& value);
  void InsertAfter(Iterator position, T&& value);

  void PushBack(const T& value);
  void PushBack(T&& value);

  void PushFront(const T& value);
  void PushFront(T&& value);

  void Erase(Iterator position);

  void PopFront();
  void PopBack();

  Iterator Find(const T& value);
  ConstIterator Find(const T& value) const;

  Iterator Find(std::function<bool(const T&)> predicate);
  ConstIterator Find(std::function<bool(const T&)> predicate) const;

 protected:
  struct Node {
    explicit Node(const T& value)
        : value_(value), next_node_(nullptr), previous_node_(nullptr) {
    }
    explicit Node(T&& value)
        : value_(std::move(value)), next_node_(nullptr), previous_node_(nullptr) {
    }

    ~Node() = default;

    T value_;
    Node* next_node_;
    Node* previous_node_;
  };

  Node* first_;
  Node* last_;

  void InsertBefore(Node* existing_node, Node* new_node);
  void InsertAfter(Node* existing_node, Node* new_node);
  void Erase(Node* node);
};

template<typename T>
T& BiDirectionalList<T>::Iterator::operator*() const {
  return node_->value_;
}

template<typename T>
T* BiDirectionalList<T>::Iterator::operator->() const {
  return &(node_->value_);
}

template<typename T>
typename BiDirectionalList<T>::Iterator& BiDirectionalList<T>::Iterator::operator++() {
  if (node_ == nullptr) {
    throw std::invalid_argument("Attempt to increment nullptr!");
  }
  node_ = node_->next_node_;
  return *this;
}

template<typename T>
const typename BiDirectionalList<T>::Iterator BiDirectionalList<T>::Iterator::operator++(int) {
  if (node_ == nullptr) {
    throw std::invalid_argument("Attempt to increment nullptr!");
  }
  auto result = *this;
  node_ = node_->next_node_;
  return result;
}

template<typename T>
typename BiDirectionalList<T>::Iterator& BiDirectionalList<T>::Iterator::operator--() {
  if (node_ == list_->first_) {
    throw std::invalid_argument("Attempt to decrement begin!");
  }
  if (node_ == nullptr) {
    node_ = list_->last_;
  } else {
    node_ = node_->previous_node_;
  }
  return *this;
}

template<typename T>
const typename BiDirectionalList<T>::Iterator BiDirectionalList<T>::Iterator::operator--(int) {
  if (node_ == list_->first_) {
    throw std::invalid_argument("Attempt to decrement begin!");
  }
  auto result = *this;
  if (node_ == nullptr) {
    node_ = list_->last_;
  } else {
    node_ = node_->previous_node_;
  }
  return result;
}

template<typename T>
bool BiDirectionalList<T>::Iterator::operator==(const BiDirectionalList::Iterator& other) const {
  return list_ == other.list_ && node_ == other.node_;
}

template<typename T>
bool BiDirectionalList<T>::Iterator::operator!=(const BiDirectionalList::Iterator& other) const {
  return list_ != other.list_ || node_ != other.node_;
}

template<typename T>
const T& BiDirectionalList<T>::ConstIterator::operator*() const {
  return node_->value_;
}

template<typename T>
const T* BiDirectionalList<T>::ConstIterator::operator->() const {
  return &(node_->value_);
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator& BiDirectionalList<T>::ConstIterator::operator++() {
  if (node_ == nullptr) {
    throw std::invalid_argument("Attempt to increment nullptr!");
  }
  node_ = node_->next_node_;
  return *this;
}

template<typename T>
const typename BiDirectionalList<T>::ConstIterator BiDirectionalList<T>::ConstIterator::operator++(int) {
  if (node_ == nullptr) {
    throw std::invalid_argument("Attempt to increment nullptr!");
  }
  auto result = *this;
  node_ = node_->next_node_;
  return result;
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator& BiDirectionalList<T>::ConstIterator::operator--() {
  if (node_ == list_->first_) {
    throw std::invalid_argument("Attempt to decrement begin!");
  }
  if (node_ == nullptr) {
    node_ = list_->last_;
  } else {
    node_ = node_->previous_node_;
  }
  return *this;
}

template<typename T>
const typename BiDirectionalList<T>::ConstIterator BiDirectionalList<T>::ConstIterator::operator--(int) {
  if (node_ == list_->first_) {
    throw std::invalid_argument("Attempt to decrement begin!");
  }
  auto result = *this;
  if (node_ == nullptr) {
    node_ = list_->last_;
  } else {
    node_ = node_->previous_node_;
  }
  return result;
}

template<typename T>
bool BiDirectionalList<T>::ConstIterator::operator==(const BiDirectionalList::ConstIterator& other) const {
  return list_ == other.list_ && node_ == other.node_;
}

template<typename T>
bool BiDirectionalList<T>::ConstIterator::operator!=(const BiDirectionalList::ConstIterator& other) const {
  return list_ != other.list_ || node_ != other.node_;
}

template<typename T>
bool BiDirectionalList<T>::IsEmpty() const {
  return first_ == nullptr;
}

template<typename T>
void BiDirectionalList<T>::Clear() {
  auto it = first_;
  while (it != nullptr) {
    auto next_it = it->next_node_;
    delete it;
    it = next_it;
  }
  first_ = nullptr;
  last_ = nullptr;
}

template<typename T>
typename BiDirectionalList<T>::Iterator BiDirectionalList<T>::begin() {
  return Iterator(this, first_);
}

template<typename T>
typename BiDirectionalList<T>::Iterator BiDirectionalList<T>::end() {
  return Iterator(this, nullptr);
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator BiDirectionalList<T>::begin() const {
  return ConstIterator(this, first_);
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator BiDirectionalList<T>::end() const {
  return ConstIterator(this, nullptr);
}

template<typename T>
std::vector<T> BiDirectionalList<T>::AsArray() const {
  std::vector<T> result;
  std::copy(begin(), end(), back_inserter(result));
  return result;
}

template<typename T>
void BiDirectionalList<T>::InsertBefore(BiDirectionalList::Iterator position, const T& value) {
  if (position.list_ != this) {
    throw std::runtime_error("Incorrect iterator to the list!");
  }
  InsertBefore(position.node_, new Node(value));
}

template<typename T>
void BiDirectionalList<T>::InsertBefore(BiDirectionalList::Iterator position, T&& value) {
  if (position.list_ != this) {
    throw std::runtime_error("Incorrect iterator to the list!");
  }
  InsertBefore(position.node_, new Node(std::move(value)));
}

template<typename T>
void BiDirectionalList<T>::InsertAfter(BiDirectionalList::Iterator position, const T& value) {
  if (position.list_ != this) {
    throw std::runtime_error("Incorrect iterator to the list!");
  }
  InsertAfter(position.node_, new Node(value));
}

template<typename T>
void BiDirectionalList<T>::InsertAfter(BiDirectionalList::Iterator position, T&& value) {
  if (position.list_ != this) {
    throw std::runtime_error("Incorrect iterator to the list!");
  }
  InsertAfter(position.node_, new Node(std::move(value)));
}

template<typename T>
void BiDirectionalList<T>::PushBack(const T& value) {
  InsertAfter(last_, new Node(value));
}

template<typename T>
void BiDirectionalList<T>::PushBack(T&& value) {
  InsertAfter(last_, new Node(std::move(value)));
}

template<typename T>
void BiDirectionalList<T>::PushFront(const T& value) {
  InsertBefore(first_, new Node(value));
}

template<typename T>
void BiDirectionalList<T>::PushFront(T&& value) {
  InsertBefore(first_, new Node(std::move(value)));
}

template<typename T>
void BiDirectionalList<T>::Erase(BiDirectionalList::Iterator position) {
  if (position.list_ != this) {
    throw std::runtime_error("Incorrect iterator to the list!");
  }
  Erase(position.node_);
}

template<typename T>
void BiDirectionalList<T>::PopFront() {
  Erase(first_);
}

template<typename T>
void BiDirectionalList<T>::PopBack() {
  Erase(last_);
}

template<typename T>
typename BiDirectionalList<T>::Iterator BiDirectionalList<T>::Find(const T& value) {
  return std::find(begin(), end(), value);
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator BiDirectionalList<T>::Find(const T& value) const {
  return std::find(begin(), end(), value);
}

template<typename T>
typename BiDirectionalList<T>::Iterator BiDirectionalList<T>::Find(std::function<bool(const T&)> predicate) {
  return std::find_if(begin(), end(), predicate);
}

template<typename T>
typename BiDirectionalList<T>::ConstIterator BiDirectionalList<T>::Find(std::function<bool(const T&)> predicate) const {
  return std::find_if(begin(), end(), predicate);
}

template<typename T>
void BiDirectionalList<T>::InsertBefore(BiDirectionalList::Node* existing_node, BiDirectionalList::Node* new_node) {
  if (new_node == nullptr) {
    throw std::invalid_argument("Attempt to insert nullptr!");
  }
  if (existing_node == nullptr) {
    InsertAfter(last_, new_node);
    return;
  }
  if (existing_node != first_) {
    InsertAfter(existing_node->previous_node_, new_node);
    return;
  }
  first_->previous_node_ = new_node;
  new_node->next_node_ = first_;
  new_node->previous_node_ = nullptr;
  first_ = new_node;
}

template<typename T>
void BiDirectionalList<T>::InsertAfter(BiDirectionalList::Node* existing_node, BiDirectionalList::Node* new_node) {
  if (new_node == nullptr) {
    throw std::invalid_argument("Attempt to insert nullptr!");
  }
  if (first_ == nullptr) {
    first_ = last_ = new_node;
    return;
  }
  if (existing_node == nullptr) {
    throw std::invalid_argument("Attempt to insert after end!");
  }
  if (existing_node != last_) {
    existing_node->next_node_->previous_node_ = new_node;
  } else {
    last_ = new_node;
  }
  new_node->next_node_ = existing_node->next_node_;
  new_node->previous_node_ = existing_node;
  existing_node->next_node_ = new_node;
}

template<typename T>
void BiDirectionalList<T>::Erase(BiDirectionalList::Node* node) {
  if (node == nullptr) {
    throw std::invalid_argument("Attempt to erase nullptr!");
  }
  if (node == first_) {
    first_ = node->next_node_;
    if (first_ != nullptr) {
      first_->previous_node_ = nullptr;
    } else {
      last_ = nullptr;
    }
  } else if (node == last_) {
    last_ = node->previous_node_;
    last_->next_node_ = nullptr;
  } else {
    node->previous_node_->next_node_ = node->next_node_;
    node->next_node_->previous_node_ = node->previous_node_;
  }
  delete node;
}
