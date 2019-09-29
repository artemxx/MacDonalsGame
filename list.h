#pragma once

#include <iostream>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <memory>

#include "iterable.h"

template<typename T>
class TIterator;

template<typename T>
class TConstIterator;

template<typename T>
class TListIteratorImplementation;

template<typename T>
class TListConstIteratorImplementation;

template<typename T>
class TBiDirectionalList : public IIterable<T> {
public:
    TBiDirectionalList() : First(nullptr), Last(nullptr) {}

    ~TBiDirectionalList() { Clear(); }

    bool IsEmpty() const;

    void Clear();

    TIterator<T> begin() override;
    TIterator<T> end() override;

    TConstIterator<T> begin() const override;
    TConstIterator<T> end() const override;

    std::vector<T> AsArray() const;

    template<class C>
    friend bool operator==(const TBiDirectionalList<C>& lhs, const TBiDirectionalList<C>& rhs);

    void InsertBefore(TIterator<T> position, const T& value);
    void InsertBefore(TIterator<T> position, T&& value);

    void InsertAfter(TIterator<T> position, const T& value);
    void InsertAfter(TIterator<T> position, T&& value);

    void PushBack(const T& value);
    void PushBack(T&& value);

    void PushFront(const T& value);
    void PushFront(T&& value);

    void Erase(TIterator<T> position);

    void PopFront();
    void PopBack();

    int GetSize() const;

protected:
    friend class TIterator<T>;
    friend class TConstIterator<T>;
    friend class TListIteratorImplementation<T>;
    friend class TListConstIteratorImplementation<T>;

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
class TIterator {
public:
    struct IIteratorImplementation {
        virtual T& GetReference() const = 0;
        virtual T* GetPointer() const = 0;

        virtual void Increment() = 0;
        virtual void Decrement() = 0;

        virtual bool EqualTo(IIteratorImplementation* const other) const = 0;

        virtual bool IsValid() const = 0;

        virtual ~IIteratorImplementation() = default;
    };

    TIterator(IIteratorImplementation* const implementation)
        : Implementation(implementation) {
    }

    TIterator(const TIterator& other) = default;

    TIterator& operator=(const TIterator& other) = default;

    T& operator*() const {
        return Implementation->GetReference();
    }

    T* operator->() const {
        return Implementation->GetPointer();
    }

    TIterator& operator++() {
        Implementation->Increment();
        return *this;
    }

    TIterator operator++(int) {
        TIterator<T> result(*this);
        Implementation->Increment();
        return result;
    }

    TIterator& operator--() {
        Implementation->Decrement();
        return *this;
    }

    TIterator operator--(int) {
        TIterator<T> result(*this);
        Implementation->Decrement();
        return result;
    }

    bool operator==(const TIterator& other) const {
        return Implementation->EqualTo(other.Implementation);
    }

    bool operator!=(const TIterator& other) const {
        return !operator==(other);
    }

    bool IsValid() const {
        return Implementation->IsValid();
    }

private:
    friend class TBiDirectionalList<T>;
    friend class TConstIterator<T>;

    IIteratorImplementation* Implementation;
};

template<typename T>
class TConstIterator {
public:
    struct IConstIteratorImplementation {
        virtual const T& GetReference() const = 0;
        virtual const T* GetPointer() const = 0;

        virtual void Increment() = 0;
        virtual void Decrement() = 0;

        virtual bool EqualTo(IConstIteratorImplementation* const other) const = 0;
        virtual bool EqualTo(typename TIterator<T>::IIteratorImplementation* const other) const = 0;

        virtual bool IsValid() const = 0;

        virtual ~IConstIteratorImplementation() = default;
    };

    TConstIterator(IConstIteratorImplementation* const implementation)
        : Implementation(implementation) {
    }

    TConstIterator(const TConstIterator& other) = default;

    TConstIterator& operator=(const TConstIterator& other) = default;

    const T& operator*() const {
        return Implementation->GetReference();
    }

    const T* operator->() const {
        return Implementation->GetPointer();
    }

    TConstIterator& operator++() {
        Implementation->Increment();
        return *this;
    }

    TConstIterator operator++(int) {
        TConstIterator<T> result(*this);
        Implementation->Increment();
        return result;
    }

    TConstIterator& operator--() {
        Implementation->Decrement();
        return *this;
    }

    TConstIterator operator--(int) {
        TConstIterator<T> result(*this);
        Implementation->Decrement();
        return result;
    }

    bool operator==(const TConstIterator& other) const {
        return Implementation->EqualTo(other.Implementation);
    }

    bool operator==(const TIterator<T>& other) const {
        return Implementation->EqualTo(other.Implementation);
    }

    bool operator!=(const TConstIterator& other) const {
        return !operator==(other);
    }

    bool operator!=(const TIterator<T>& other) const {
        return !operator==(other);
    }

    bool IsValid() const {
        return Implementation->IsValid();
    }

private:
    friend class TBiDirectionalList<T>;

    IConstIteratorImplementation* Implementation;
};

template<typename T>
struct TListIteratorImplementation : public TIterator<T>::IIteratorImplementation {
public:
    T& GetReference() const override {
        return Node->Value;
    }
    T* GetPointer() const override {
        return &(Node->Value);
    }

    void Increment() override;
    void Decrement() override;

    bool EqualTo(typename TIterator<T>::IIteratorImplementation* const other) const override {
        auto other_list_iterator = (TListIteratorImplementation*)(other);
        return List == other_list_iterator->List && Node == other_list_iterator->Node;
    }

    bool IsValid() const override {
        return Node != nullptr;
    }

private:
    friend class TBiDirectionalList<T>;
    friend class TListConstIteratorImplementation<T>;

    const TBiDirectionalList<T>* List;
    typename TBiDirectionalList<T>::TNode* Node;

    TListIteratorImplementation(const TBiDirectionalList<T>* list, typename TBiDirectionalList<T>::TNode* node)
        : List(list), Node(node) {
    }
};

template<typename T>
struct TListConstIteratorImplementation : public TConstIterator<T>::IConstIteratorImplementation {
public:
    const T& GetReference() const override {
        return Node->Value;
    }

    const T* GetPointer() const override {
        return &(Node->Value);
    }

    void Increment() override;
    void Decrement() override;

    bool EqualTo(typename TConstIterator<T>::IConstIteratorImplementation* const other) const override {
        auto other_list_iterator = (TListConstIteratorImplementation*)(other);
        return List == other_list_iterator->List && Node == other_list_iterator->Node;
    }

    bool EqualTo(typename TIterator<T>::IIteratorImplementation* const other) const override {
        auto other_list_iterator = (TListIteratorImplementation<T>*)(other);
        return List == other_list_iterator->List && Node == other_list_iterator->Node;
    }

    bool IsValid() const override {
        return Node != nullptr;
    }

private:
    friend class TBiDirectionalList<T>;

    const TBiDirectionalList<T>* List;
    typename TBiDirectionalList<T>::TNode* Node;

    TListConstIteratorImplementation(const TBiDirectionalList<T>* list, typename TBiDirectionalList<T>::TNode* node)
        : List(list), Node(node) {
    }
};

template<typename T>
void TListIteratorImplementation<T>::Increment() {
    if (Node == nullptr) {
        throw std::invalid_argument("Attempt to increment nullptr!");
    }
    Node = Node->NextNode;
}

template<typename T>
void TListIteratorImplementation<T>::Decrement() {
    if (Node == List->First) {
        throw std::invalid_argument("Attempt to decrement begin!");
    }
    if (Node == nullptr) {
        Node = List->Last;
    } else {
        Node = Node->PreviousNode;
    }
}

template<typename T>
void TListConstIteratorImplementation<T>::Increment() {
    if (Node == nullptr) {
        throw std::invalid_argument("Attempt to increment nullptr!");
    }
    Node = Node->NextNode;
}

template<typename T>
void TListConstIteratorImplementation<T>::Decrement() {
    if (Node == List->First) {
        throw std::invalid_argument("Attempt to decrement begin!");
    }
    if (Node == nullptr) {
        Node = List->Last;
    } else {
        Node = Node->PreviousNode;
    }
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
TIterator<T> TBiDirectionalList<T>::begin() {
    return TIterator<T>(new TListIteratorImplementation<T>(this, First));
}

template<typename T>
TIterator<T> TBiDirectionalList<T>::end() {
    return TIterator<T>(new TListIteratorImplementation<T>(this, nullptr));
}

template<typename T>
TConstIterator<T> TBiDirectionalList<T>::begin() const {
    return TConstIterator<T>(new TListConstIteratorImplementation<T>(this, First));
}

template<typename T>
TConstIterator<T> TBiDirectionalList<T>::end() const {
    return TConstIterator<T>(new TListConstIteratorImplementation<T>(this, nullptr));
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
    TConstIterator<T> lhsIt = lhs.begin();
    TConstIterator<T> rhsIt = rhs.begin();
    while (lhsIt != lhs.end() && (*lhsIt) == (*rhsIt)) {
        ++lhsIt;
        ++rhsIt;
    }
    return lhsIt == lhs.end();
}

template<typename T>
void TBiDirectionalList<T>::InsertBefore(TIterator<T> position, const T& value) {
    if (((TListIteratorImplementation<T>*)(position.Implementation))->List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    InsertBefore(((TListIteratorImplementation<T>*)(position.Implementation))->Node, new TNode(value));
}

template<typename T>
void TBiDirectionalList<T>::InsertBefore(TIterator<T> position, T&& value) {
    if (((TListIteratorImplementation<T>*)(position.Implementation))->List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    InsertBefore(((TListIteratorImplementation<T>*)(position.Implementation))->Node, new TNode(std::move(value)));
}

template<typename T>
void TBiDirectionalList<T>::InsertAfter(TIterator<T> position, const T& value) {
    if (((TListIteratorImplementation<T>*)(position.Implementation))->List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    InsertAfter(((TListIteratorImplementation<T>*)(position.Implementation))->Node, new TNode(value));
}

template<typename T>
void TBiDirectionalList<T>::InsertAfter(TIterator<T> position, T&& value) {
    if (((TListIteratorImplementation<T>*)(position.Implementation))->List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    InsertAfter(((TListIteratorImplementation<T>*)(position.Implementation))->Node, new TNode(std::move(value)));
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
void TBiDirectionalList<T>::Erase(TIterator<T> position) {
    if (((TListIteratorImplementation<T>*)(position.Implementation))->List != this) {
        throw std::runtime_error("Incorrect iterator to the list!");
    }
    Erase(((TListIteratorImplementation<T>*)(position.Implementation))->Node);
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
