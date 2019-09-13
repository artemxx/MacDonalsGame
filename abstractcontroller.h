#pragma once

#include <memory>
#include <QString>
#include "list.h"

class TAbstractDequeController {
public:
    virtual ~TAbstractDequeController() = default;

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
