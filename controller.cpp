#include "controller.h"

TController::TController(TAbstractView* view)
    : View(view) {}

void TController::PushFirstDequeFront(const QString& name) {
    FirstDeque.PushFront(name);
    View->DrawFirstDeque(FirstDeque);
}

void TController::PushFirstDequeBack(const QString& name) {
    FirstDeque.PushBack(name);
    View->DrawFirstDeque(FirstDeque);
}

void TController::PopFirstDequeFront() {
    if (FirstDeque.IsEmpty()) {
        return;
    }
    FirstDeque.PopFront();
    View->DrawFirstDeque(FirstDeque);
}

void TController::PopFirstDequeBack() {
    if (FirstDeque.IsEmpty()) {
        return;
    }
    FirstDeque.PopBack();
    View->DrawFirstDeque(FirstDeque);
}

void TController::PushSecondDequeFront(const QString& name) {
    SecondDeque.PushFront(name);
    View->DrawSecondDeque(SecondDeque);
}

void TController::PushSecondDequeBack(const QString& name) {
    SecondDeque.PushBack(name);
    View->DrawSecondDeque(SecondDeque);
}

void TController::PopSecondDequeFront() {
    if (SecondDeque.IsEmpty()) {
        return;
    }
    SecondDeque.PopFront();
    View->DrawSecondDeque(SecondDeque);
}

void TController::PopSecondDequeBack() {
    if (SecondDeque.IsEmpty()) {
        return;
    }
    SecondDeque.PopBack();
    View->DrawSecondDeque(SecondDeque);
}

void TController::MoveForwardFirstIterator() {
    if ()
}

void TController::CompareDeques() {
    View->DrawCompareResult(FirstDeque == SecondDeque);
}
