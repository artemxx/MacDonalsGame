#pragma once

#include <QString>
#include <QVector>

#include "list.h"

class TVisitor;

struct TPeopleGroup {
    virtual ~TPeopleGroup() = default;

    virtual void Accept(const TVisitor& visitor) = 0;
};

struct TDeque : public TPeopleGroup {
    TDeque();
    ~TDeque() override = default;

    void Accept(const TVisitor& visitor) override;

    TBiDirectionalList<QString> Deque;
    TIterator<QString> Iterator;
};

struct TCrawd : public TPeopleGroup {
    void Accept(const TVisitor& visitor) override;

    QVector<QString> Crawd;
};
