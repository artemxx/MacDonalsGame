#pragma once

#include <QString>
#include <memory>

#include "abstractcontroller.h"
#include "abstractview.h"

class TController : public TAbstractController {
public:
     explicit TController(TAbstractView* view);
     ~TController() override = default;

    void PushFirstDequeFront(const QString& name) override;
    void PushFirstDequeBack(const QString& name) override;
    void PopFirstDequeFront() override;
    void PopFirstDequeBack() override;

    void PushSecondDequeFront(const QString& name) override;
    void PushSecondDequeBack(const QString& name) override;
    void PopSecondDequeFront() override;
    void PopSecondDequeBack() override;

    void CompareDeques() override;

protected:
    TAbstractView* View;

    TBiDirectionalList<QString> FirstDeque;
    TBiDirectionalList<QString> SecondDeque;
};
