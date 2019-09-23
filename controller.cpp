#include "controller.h"

TFrontPusher::TFrontPusher(const QString &name)
    : Name(name)
{
}

TBackPusher::TBackPusher(const QString &name)
    : Name(name)
{
}

void TFrontPusher::Visit(TDeque& deque) {
    deque.PushFront(Name);
}

void TBackPusher::Visit(TDeque& deque) {
    deque.PushBack(Name);
}

void TFrontPopper::Visit(TDeque& deque) {
    deque.PopFront();
}

void TBackPopper::Visit(TDeque& deque) {
    deque.PopBack();
}

TController::TController(TAbstractView* view)
    : View(view), FirstDeque(), SecondDeque()
    , FirstIterator(FirstDeque.begin()), SecondIterator(SecondDeque.begin())
    {
    }

void TController::PushFirstDequeFront(const QString& name) {
    TFrontPusher(name).Visit(FirstDeque);
    if (FirstDeque.GetSize() == 1) {
        FirstIterator = FirstDeque.begin();
    }
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::PushFirstDequeBack(const QString& name) {
    TBackPusher(name).Visit(FirstDeque);
    if (FirstDeque.GetSize() == 1) {
        FirstIterator = FirstDeque.begin();
    }
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::PopFirstDequeFront() {
    if (FirstDeque.IsEmpty()) {
        return;
    }
    if (FirstIterator == FirstDeque.begin()) {
        ++FirstIterator;
    }
    TFrontPopper().Visit(FirstDeque);
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::PopFirstDequeBack() {
    if (FirstDeque.IsEmpty()) {
        return;
    }
    if (FirstIterator == --FirstDeque.end()) {
        FirstIterator = FirstDeque.begin();
    }
    TBackPopper().Visit(FirstDeque);
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::PushSecondDequeFront(const QString& name) {
    TFrontPusher(name).Visit(SecondDeque);
    if (SecondDeque.GetSize() == 1) {
        SecondIterator = SecondDeque.begin();
    }
    View->DrawSecondDeque(SecondDeque, SecondIterator);
}

void TController::PushSecondDequeBack(const QString& name) {
    TBackPusher(name).Visit(SecondDeque);
    if (SecondDeque.GetSize() == 1) {
        SecondIterator = SecondDeque.begin();
    }
    View->DrawSecondDeque(SecondDeque, SecondIterator);
}

void TController::PopSecondDequeFront() {
    if (SecondDeque.IsEmpty()) {
        return;
    }
    if (SecondIterator == SecondDeque.begin()) {
        ++SecondIterator;
    }
    TFrontPopper().Visit(SecondDeque);
    View->DrawSecondDeque(SecondDeque, SecondIterator);
}

void TController::PopSecondDequeBack() {
    if (SecondDeque.IsEmpty()) {
        return;
    }
    if (SecondIterator == --SecondDeque.end()) {
        SecondIterator = SecondDeque.begin();
    }
    TBackPopper().Visit(SecondDeque);
    View->DrawSecondDeque(SecondDeque, SecondIterator);
}

void TController::MoveForwardFirstIterator() {
    ++FirstIterator;
    if (FirstIterator == FirstDeque.end()) {
        FirstIterator = FirstDeque.begin();
    }
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::MoveBackwardFirstIterator() {
    if (FirstIterator == FirstDeque.begin()) {
        FirstIterator = --FirstDeque.end();
    } else {
        --FirstIterator;
    }
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::MoveForwardSecondIterator() {
    ++SecondIterator;
    if (SecondIterator == SecondDeque.end()) {
        SecondIterator = SecondDeque.begin();
    }
    View->DrawSecondDeque(SecondDeque, SecondIterator);
}

void TController::MoveBackwardSecondIterator() {
    if (SecondIterator == SecondDeque.begin()) {
        SecondIterator = --SecondDeque.end();
    } else {
        --SecondIterator;
    }
    View->DrawSecondDeque(SecondDeque, SecondIterator);
}

void TController::ChangeFirstName(const QString& name) {
    *FirstIterator = name;
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::ChangeSecondName(const QString& name) {
    *SecondIterator = name;
    View->DrawSecondDeque(SecondDeque, SecondIterator);
}

void TController::CompareDeques() {
    View->DrawCompareResult(FirstDeque == SecondDeque);
}
