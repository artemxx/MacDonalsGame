#pragma once

#include "list.h"

#include <QString>

using TDeque = TBiDirectionalList<QString>;

class TVisitor {
public:
    virtual ~TVisitor() = default;

    virtual void Visit(TDeque& deque) = 0;
};
