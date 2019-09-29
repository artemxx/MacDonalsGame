#pragma once

template<typename T>
class TIterator;

template<typename T>
class TConstIterator;

template<typename T>
class IIterable {
public:
    virtual ~IIterable() = default;

    virtual TIterator<T> begin() = 0;
    virtual TIterator<T> end() = 0;

    virtual TConstIterator<T> begin() const = 0;
    virtual TConstIterator<T> end() const = 0;
};
