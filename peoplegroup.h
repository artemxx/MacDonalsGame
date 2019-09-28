#pragma once
#include <QString>
#include <vector>

#include "list.h"

class TVisitor;

struct TPeopleGroup {
    virtual ~TPeopleGroup() = default;

    virtual void Accept(const TVisitor& visitor) = 0;
};

struct TDeque : public TPeopleGroup {
    TDeque();
    ~TDeque() = default;

    void Accept(const TVisitor& visitor) override;

    TBiDirectionalList<QString> Deque;
    TBiDirectionalList<QString>::TIterator Iterator;
};

struct TCrawd : public TPeopleGroup {
    void Accept(const TVisitor& visitor) override;

    std::vector<QString> Crawd;
};
