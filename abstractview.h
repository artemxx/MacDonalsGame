#pragma once

#include <QString>

#include "list.h"

class TAbstractView {
public:
    virtual ~TAbstractView() = default;

    virtual void DrawFirstDeque(const TBiDirectionalList<QString>& deque,
                                const TBiDirectionalList<QString>::TIterator iterator) = 0;
    virtual void DrawSecondDeque(const TBiDirectionalList<QString>& deque,
                                 const TBiDirectionalList<QString>::TIterator iterator) = 0;

    virtual void DrawCompareResult(bool result) = 0;
};
