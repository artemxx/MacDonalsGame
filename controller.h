#pragma once

#include <QString>
#include <memory>

#include "abstractcontroller.h"
#include "abstractview.h"
#include "visitor.h"

using TDeque = TBiDirectionalList<QString>;

class TFrontPusher : public TVisitor {
public:
    TFrontPusher(const QString& name);

    ~TFrontPusher() override = default;
    void Visit(TDeque& deque) override;

private:
    const QString Name;
};

class TBackPusher : public TVisitor {
public:
    TBackPusher(const QString& name);

    ~TBackPusher() override = default;
    void Visit(TDeque& deque) override;

private:
    const QString Name;
};

class TFrontPopper : public TVisitor {
public:
    ~TFrontPopper() override = default;
    void Visit(TDeque& deque) override;
};

class TBackPopper : public TVisitor {
public:
    ~TBackPopper() override = default;
    void Visit(TDeque& deque) override;
};

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

    TDeque FirstDeque;
    TDeque SecondDeque;
    TDeque::TIterator FirstIterator;
    TDeque::TIterator SecondIterator;
};
