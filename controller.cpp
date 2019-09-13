#include "dequecontroller.h"

TDequeController::TDequeController(TAbstractDequeView* view)
    : View(view) {}

void TDequeController::PushFirstDequeFront(const QString& name) {
    FirstDeque.PushFront(name);
    View->DrawFirstDeque(FirstDeque);
}

void TDequeController::PushFirstDequeBack(const QString& name) {
    FirstDeque.PushBack(name);
    View->DrawFirstDeque(FirstDeque);
}

void TDequeController::PopFirstDequeFront() {
    if (FirstDeque.IsEmpty()) {
        return;
    }
    FirstDeque.PopFront();
    View->DrawFirstDeque(FirstDeque);
}

void TDequeController::PopFirstDequeBack() {
    if (FirstDeque.IsEmpty()) {
        return;
    }
    FirstDeque.PopBack();
    View->DrawFirstDeque(FirstDeque);
}

void TDequeController::PushSecondDequeFront(const QString& name) {
    SecondDeque.PushFront(name);
    View->DrawSecondDeque(SecondDeque);
}

void TDequeController::PushSecondDequeBack(const QString& name) {
    SecondDeque.PushBack(name);
    View->DrawSecondDeque(SecondDeque);
}

void TDequeController::PopSecondDequeFront() {
    if (SecondDeque.IsEmpty()) {
        return;
    }
    SecondDeque.PopFront();
    View->DrawSecondDeque(SecondDeque);
}

void TDequeController::PopSecondDequeBack() {
    if (SecondDeque.IsEmpty()) {
        return;
    }
    SecondDeque.PopBack();
    View->DrawSecondDeque(SecondDeque);
}

void TDequeController::CompareDeques() {
    View->DrawCompareResult(FirstDeque == SecondDeque);
}
