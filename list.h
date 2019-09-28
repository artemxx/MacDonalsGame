#pragma once

#include <iostream>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <vector>

template<typename T>
class TBiDirectionalList {
protected:
    struct TNode;

public:
    class TIterator;
    class TConstIterator;

    TBiDirectionalList() : First(nullptr), Last(nullptr) {}

    ~TBiDirectionalList() { Clear(); }

    bool IsEmpty() const;

    void Clear();

    TIterator begin();
    TIterator end();

    TConstIterator begin() const;
    TConstIterator end() const;

    std::vector<T> AsArray() const;

    template<class C>
    friend bool operator==(const TBiDirectionalList<C>& lhs, const TBiDirectionalList<C>& rhs);

    void InsertBefore(TIterator position, const T& value);
    void InsertBefore(TIterator position, T&& value);

    void InsertAfter(TIterator position, const T& value);
    void InsertAfter(TIterator position, T&& value);

    void PushBack(const T& value);
    void PushBack(T&& value);

    void PushFront(const T& value);
    void PushFront(T&& value);

    void Erase(TIterator position);

    void PopFront();
    void PopBack();

    TIterator Find(const T& value);
    TConstIterator Find(const T& value) const;

    TIterator Find(std::function<bool(const T&)> predicate);
    TConstIterator Find(std::function<bool(const T&)> predicate) const;

    int GetSize() const;

protected:
    struct TNode {
        explicit TNode(const T& value)
            : Value(value), NextNode(nullptr), PreviousNode(nullptr) {
        }
        explicit TNode(T&& value)
            : Value(std::move(value)), NextNode(nullptr), PreviousNode(nullptr) {
        }

        ~TNode() = default;

        T Value;
        TNode* NextNode;
        TNode* PreviousNode;
    };

    TNode* First;
    TNode* Last;

    int Size = 0;

    void InsertBefore(TNode* existingNode, TNode* newNode);
    void InsertAfter(TNode* existingNode, TNode* newNode);
    void Erase(TNode* node);
};

template<typename T>
class TBiDirectionalList<T>::TIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    TIterator& operator=(const TIterator& other);

    T& operator*() const;
    T* operator->() const;

    TIterator& operator++();
    const TIterator operator++(int);

    TIterator& operator--();
    const TIterator operator--(int);

    bool operator==(const TIterator& other) const;
    bool operator!=(const TIterator& other) const;

    bool IsValid() const;

private:
    friend class TBiDirectionalList;

    const TBiDirectionalList* List;
    TNode* Node;

    TIterator(const TBiDirectionalList* const list, TNode* node)
        : List(list), Node(node) {}
};

template<typename T>
class TBiDirectionalList<T>::TConstIterator :
    public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    TConstIterator(TIterator iterator)
        : List(iterator.List), Node(iterator.Node) {}

    const T& operator*() const;
    const T* operator->() const;

    TConstIterator& operator++();
    const TConstIterator operator++(int);

    TConstIterator& operator--();
    const TConstIterator operator--(int);

    bool operator==(const TConstIterator& other) const;
    bool operator!=(const TConstIterator& other) const;

    bool IsValid() const;

private:
    friend class TBiDirectionalList;
    friend class TIterator;

    const TBiDirectionalList* List;
    const TNode* Node;

    TConstIterator(const TBiDirectionalList* const list, TNode* node)
        : List(list), Node(node) {}
};

template<typename T>
T& TBiDirectionalList<T>::TIterator::operator*() const {
    return Node->Value;
}

template<typename T>
T* TBiDirectionalList<T>::TIterator::operator->() const {
    return &(Node->Value);
}

template<typename T>
typename TBiDirectionalList<T>::TIterator& TBiDirectionalList<T>::TIterator::operator++() {
    if (Node == nullptr) {
        throw std::invalid_argument("Attempt to increment nullptr!");
    }
    Node = Node->NextNode;
    return *this;
}

template<typename T>
const typename TBiDirectionalList<T>::TIterator TBiDirectionalList<T>::TIterator::operator++(int) {
    if (Node == nullptr) {
        throw std::invalid_argument("Attempt to increment nullptr!");
    }
    auto result = *this;
    Node = Node->NextNode;
    return result;
}

template<typename T>
typename TBiDirectionalList<T>::TIterator& TBiDirectionalList<T>::TIterator::operator--() {
    if (Node == List->First) {
        throw std::invalid_argument("Attempt to decrement begin!");
    }
    if (Node == nullptr) {
        Node = List->Last;
    } else {
        Node = Node->PreviousNode;
    }
    return *this;
}

template<typename T>
const typename TBiDirectionalList<T>::TIterator TBiDirectionalList<T>::TIterator::operator--(int) {
    if (Node == List->First) {
        throw std::invalid_argument("Attempt to decrement begin!");
    }
    auto result = *this;
    if (Node == nullptr) {
        Node = List->Last;
    } else {
        Node = Node->PreviousNode;
    }
    return result;
}

template<typename T>
typename TBiDirectionalList<T>::TIterator& TBiDirectionalList<T>::TIterator::operator=(const TBiDirectionalList::TIterator& other) {
    List = other.List;
    Node = other.Node;
    return *this;
}

template<typename T>
bool TBiDirectionalList<T>::TIterator::operator==(const TBiDirectionalList::TIterator& other) const {
    return List == other.List && Node == other.Node;
}

template<typename T>
bool TBiDirectionalList<T>::TIterator::operator!=(const TBiDirectionalList::TIterator& other) const {
    return List != other.List || Node != other.Node;
}

template<typename T>
bool TBiDirectionalList<T>::TIterator::IsValid() const {
    return Node != nullptr;
}

template<typename T>
const T& TBiDirectionalList<T>::TConstIterator::operator*() const {
    return Node->Value;
}

template<typename T>
const T* TBiDirectionalList<T>::TConstIterator::operator->() const {
    return &(Node->Value);
}

template<typename T>
typename TBiDirectionalList<T>::TConstIterator& TBiDirectionalList<T>::TConstIterator::operator++() {
    if (Node == nullptr) {
        throw std::invalid_argument("Attempt to increment nullptr!");
    }
    Node = Node->NextNode;
    return *this;
}

template<typename T>
const typename TBiDirectionalList<T>::TConstIterator TBiDirectionalList<T>::TConstIterator::operator++(int) {
    if (Node == nullptr) {
        throw std::invalid_argument("Attempt to increment nullptr!");
    }
    auto result = *this;
    Node = Node->NextNode;
    return result;
}

template<typename T>
typename TBiDirectionalList<T>::TConstIterator& TBiDirectionalList<T>::TConstIterator::operator--() {
    if (Node == List->First) {
        throw std::invalid_argument("Attempt to decrement begin!");
    }
    if (Node == nullptr) {
        Node = List->Last;
    } else {
        Node = Node->PreviousNode;
    }
    return *this;
}

template<typename T>
const typename TBiDirectionalList<T>::TConstIterator TBiDirectionalList<T>::TConstIterator::operator--(int) {
    if (Node == List->First) {
        throw std::invalid_argument("Attempt to decrement begin!");
    }
    auto result = *this;
    if (Node == nullptr) {
        Node = List->Last;
    } else {
        Node = Node->PreviousNode;
    }
    return result;
}

template<typename T>
bool TBiDirectionalList<T>::TConstIterator::operator==(const TBiDirectionalList::TConstIterator& other) const {
    return List == other.List && Node == other.Node;
}

template<typename T>
bool TBiDirectionalList<T>::TConstIterator::operator!=(const TBiDirectionalList::TConstIterator& other) const {
    return List != other.List || Node != other.Node;
}

template<typename T>
bool TBiDirectionalList<T>::TConstIterator::IsValid() const {
    return Node != nullptr;
}

template<typename T>
bool TBiDirectionalList<T>::IsEmpty() const {
    return First == nullptr;
}

template<typename T>
void TBiDirectionalList<T>::Clear() {
    auto it = First;
    while (it != nullptr) {
        auto nextIt = it->NextNode;
        delete it;
        it = nextIt;
    }
    First = nullptr;
    Last = nullptr;
}

template<typename T>
typename TBiDirectionalList<T>::TIterator TBiDirectionalList<T>::begin() {
    return TIterator(this, First);
}

template<typename T>
typename TBiDirectionalList<T>::TIterator TBiDirectionalList<T>::end() {
    return TIterator(this, nullptr);
}

template<typename T>
typename TBiDirectionalList<T>::TConstIterator TBiDirectionalList<T>::begin() const {
    return TConstIterator(this, First);
}

template<typename T>
typename TBiDirectionalList<T>::TConstIterator TBiDirectionalList<T>::end() const {
    return TConstIterator(this, nullptr);
}

template<typename T>
std::vector<T> TBiDirectionalList<T>::AsArray() const {
    std::vector<T> result;
    std::copy(begin(), end(), back_inserter(result));
    return result;
}

template<typename T>
bool operator==(const TBiDirectionalList<T>& lhs, const TBiDirectionalList<T>& rhs) {
    if (lhs.GetSize() != rhs.GetSize()) {
        return false;
    }
    typename TBiDirectionalList<T>::TConstIterator lhsIt = lhs.begin();
    typename TBiDirectionalList<T>::TConstIterator rhsIt = rhs.begin();
    while (lhsIt != lhs.end() && (*lhsIt) == (*rhsIt)) {
        ++lhsIt;
        ++rhsIt;
    }
    return lhsIt == lhs.end();
}

template<typename T>
void TBiDirectionalList<T>::InsertBefore(TBiDirectionalList::TIterator position, const T& value) {
    if (position.List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    InsertBefore(position.Node, new TNode(value));
}

template<typename T>
void TBiDirectionalList<T>::InsertBefore(TBiDirectionalList::TIterator position, T&& value) {
    if (position.List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    InsertBefore(position.Node, new TNode(std::move(value)));
}

template<typename T>
void TBiDirectionalList<T>::InsertAfter(TBiDirectionalList::TIterator position, const T& value) {
    if (position.List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    InsertAfter(position.Node, new TNode(value));
}

template<typename T>
void TBiDirectionalList<T>::InsertAfter(TBiDirectionalList::TIterator position, T&& value) {
    if (position.List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    InsertAfter(position.Node, new TNode(std::move(value)));
}

template<typename T>
void TBiDirectionalList<T>::PushBack(const T& value) {
    InsertAfter(Last, new TNode(value));
}

template<typename T>
void TBiDirectionalList<T>::PushBack(T&& value) {
    InsertAfter(Last, new TNode(std::move(value)));
}

template<typename T>
void TBiDirectionalList<T>::PushFront(const T& value) {
    InsertBefore(First, new TNode(value));
}

template<typename T>
void TBiDirectionalList<T>::PushFront(T&& value) {
    InsertBefore(First, new TNode(std::move(value)));
}

template<typename T>
void TBiDirectionalList<T>::Erase(TBiDirectionalList::TIterator position) {
    if (position.List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    Erase(position.Node);
}

template<typename T>
void TBiDirectionalList<T>::PopFront() {
    Erase(First);
}

template<typename T>
void TBiDirectionalList<T>::PopBack() {
    Erase(Last);
}

template<typename T>
typename TBiDirectionalList<T>::TIterator TBiDirectionalList<T>::Find(const T& value) {
    return std::find(begin(), end(), value);
}

template<typename T>
typename TBiDirectionalList<T>::TConstIterator TBiDirectionalList<T>::Find(const T& value) const {
    return std::find(begin(), end(), value);
}

template<typename T>
typename TBiDirectionalList<T>::TIterator TBiDirectionalList<T>::Find(std::function<bool(const T&)> predicate) {
    return std::find_if(begin(), end(), predicate);
}

template<typename T>
typename TBiDirectionalList<T>::TConstIterator TBiDirectionalList<T>::Find(std::function<bool(const T&)> predicate) const {
    return std::find_if(begin(), end(), predicate);
}

template<typename T>
int TBiDirectionalList<T>::GetSize() const {
    return Size;
}

template<typename T>
void TBiDirectionalList<T>::InsertBefore(TBiDirectionalList::TNode* existingNode, TBiDirectionalList::TNode* newNode) {
    if (newNode == nullptr) {
        throw std::invalid_argument("Attempt to insert nullptr!");
    }
    if (existingNode == nullptr) {
        InsertAfter(Last, newNode);
        return;
    }
    if (existingNode != First) {
        InsertAfter(existingNode->PreviousNode, newNode);
        return;
    }
    ++Size;
    First->PreviousNode = newNode;
    newNode->NextNode = First;
    newNode->PreviousNode = nullptr;
    First = newNode;
}

template<typename T>
void TBiDirectionalList<T>::InsertAfter(TBiDirectionalList::TNode* existingNode, TBiDirectionalList::TNode* newNode) {
    if (newNode == nullptr) {
        throw std::invalid_argument("Attempt to insert nullptr!");
    }
    if (First == nullptr) {
        ++Size;
        First = Last = newNode;
        return;
    }
    if (existingNode == nullptr) {
        throw std::invalid_argument("Attempt to insert after end!");
    }
    ++Size;
    if (existingNode != Last) {
        existingNode->NextNode->PreviousNode = newNode;
    } else {
        Last = newNode;
    }
    newNode->NextNode = existingNode->NextNode;
    newNode->PreviousNode = existingNode;
    existingNode->NextNode = newNode;
}

template<typename T>
void TBiDirectionalList<T>::Erase(TBiDirectionalList::TNode* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Attempt to erase nullptr!");
    }
    --Size;
    if (node == First) {
        First = node->NextNode;
        if (First != nullptr) {
            First->PreviousNode = nullptr;
        } else {
            Last = nullptr;
        }
    } else if (node == Last) {
        Last = node->PreviousNode;
        Last->NextNode = nullptr;
    } else {
        node->PreviousNode->NextNode = node->NextNode;
        node->NextNode->PreviousNode = node->PreviousNode;
    }
    delete node;
}
