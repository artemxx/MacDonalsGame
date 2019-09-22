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

    void MoveForwardFirstIterator() override;
    void MoveBackwardFirstIterator() override;
    void MoveForwardSecondIterator() override;
    void MoveBackwardSecondIterator() override;

    void ChangeFirstName(const QString& name) override;
    void ChangeSecondName(const QString& name) override;

    void CompareDeques() override;

protected:
    TAbstractView* View;

    TBiDirectionalList<QString>::TIterator FirstIterator;
    TBiDirectionalList<QString>::TIterator SecondIterator;
    TBiDirectionalList<QString> FirstDeque;
    TBiDirectionalList<QString> SecondDeque;
};
