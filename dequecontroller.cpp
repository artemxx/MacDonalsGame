#include "dequecontroller.h"
#include <stdexcept>

TDequeController::TDequeController(TMainWindow* view)
    : View(view) {}

void TDequeController::PushFirstDequeFront(const QString& name) {
    FirstDeque.PushFront(name);
    View->PushFirstDequeFront(name);
}

void TDequeController::PushSecondDequeFront(const QString& name) {
    SecondDeque.PushFront(name);
    View->PushSecondDequeFront(name);
}

void TDequeController::PushFirstDequeBack(const QString& name) {
    FirstDeque.PushBack(name);
    View->PushFirstDequeBack(name);
}

void TDequeController::PushSecondDequeBack(const QString& name) {
    SecondDeque.PushBack(name);
    View->PushSecondDequeBack(name);
}

void TDequeController::PopFirstDequeFront() {
    if (FirstDeque.IsEmpty()) {
        return;
    }
    FirstDeque.PopFront();
    View->PopFirstDequeFront();
}

void TDequeController::PopSecondDequeFront() {
    if (SecondDeque.IsEmpty()) {
        return;
    }
    SecondDeque.PopFront();
    View->PopSecondDequeFront();
}

void TDequeController::PopFirstDequeBack() {
    if (FirstDeque.IsEmpty()) {
        return;
    }
    FirstDeque.PopBack();
    View->PopFirstDequeBack();
}

void TDequeController::PopSecondDequeBack() {
    if (SecondDeque.IsEmpty()) {
        return;
    }
    SecondDeque.PopBack();
    View->PopSecondDequeBack();
}

void TDequeController::CompareDeques() {
  View->CompareDeques(FirstDeque == SecondDeque);
}
