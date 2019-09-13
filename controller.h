#pragma once

#include <memory>
#include <QString>
#include "abstractdequecontroller.h"
#include "abstractdequeview.h"

class TDequeController : public TAbstractDequeController {
public:
     explicit TDequeController(TAbstractDequeView* view);
     ~TDequeController() override = default;

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
    TAbstractDequeView* View;
};
