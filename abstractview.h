#pragma once

#include <QString>

#include "peoplegroup.h"

class TAbstractView {
public:
    virtual ~TAbstractView() = default;

    virtual void DrawFirstDeque(const TDeque& firstDeque) = 0;
    virtual void DrawSecondDeque(const TDeque& secondDeque) = 0;

    virtual void DrawCompareResult(bool result) = 0;

    virtual void DrawCrawd(const TCrawd& crawd) = 0;
};
