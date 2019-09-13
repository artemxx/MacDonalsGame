#pragma once

#include <QString>

#include "list.h"

class TAbstractDequeView {
public:
    virtual ~TAbstractDequeView() = default;

    virtual void DrawFirstDeque(const TBiDirectionalList<QString>& deque) = 0;
    virtual void DrawSecondDeque(const TBiDirectionalList<QString>& deque) = 0;

    virtual void DrawCompareResult(bool result) = 0;
};
