#pragma once

#include <QString>
#include <memory>

#include "list.h"

class TAbstractController {
public:
    virtual ~TAbstractController() = default;

    virtual void PushFirstDequeFront(const QString& name) = 0;
    virtual void PushFirstDequeBack(const QString& name) = 0;
    virtual void PopFirstDequeFront() = 0;
    virtual void PopFirstDequeBack() = 0;

    virtual void PushSecondDequeFront(const QString& name) = 0;
    virtual void PushSecondDequeBack(const QString& name) = 0;
    virtual void PopSecondDequeFront() = 0;
    virtual void PopSecondDequeBack() = 0;

    virtual void CompareDeques() = 0;

protected:
    TBiDirectionalList<QString> FirstDeque;
    TBiDirectionalList<QString> SecondDeque;
};