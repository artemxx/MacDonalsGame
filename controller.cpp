#include "controller.h"

TController::TController(TAbstractView* view)
    : View(view), FirstDeque(), SecondDeque()
    {
    }

void TController::PushFirstDequeFront(const QString& name) {
    FirstDeque.Accept(TFrontPusher(name));
    View->DrawFirstDeque(FirstDeque);
}

void TController::PushFirstDequeBack(const QString& name) {
    FirstDeque.Accept(TBackPusher(name));
    View->DrawFirstDeque(FirstDeque);
}

void TController::PopFirstDequeFront() {
    FirstDeque.Accept(TFrontPopper());
    View->DrawFirstDeque(FirstDeque);
}

void TController::PopFirstDequeBack() {
    FirstDeque.Accept(TBackPopper());
    View->DrawFirstDeque(FirstDeque);
}

void TController::PushSecondDequeFront(const QString& name) {
    SecondDeque.Accept(TFrontPusher(name));
    View->DrawSecondDeque(SecondDeque);
}

void TController::PushSecondDequeBack(const QString& name) {
    SecondDeque.Accept(TBackPusher(name));
    View->DrawSecondDeque(SecondDeque);
}

void TController::PopSecondDequeFront() {
    SecondDeque.Accept(TFrontPopper());
    View->DrawSecondDeque(SecondDeque);
}

void TController::PopSecondDequeBack() {
    SecondDeque.Accept(TBackPopper());
    View->DrawSecondDeque(SecondDeque);
}

void TController::MoveForwardIterator(TDeque& deque) {
    ++deque.Iterator;
    if (deque.Iterator == deque.Deque.end()) {
        deque.Iterator = deque.Deque.begin();
    }
}

void TController::MoveBackwardIterator(TDeque& deque) {
    if (deque.Iterator == deque.Deque.begin()) {
        deque.Iterator = --deque.Deque.end();
    } else {
        --deque.Iterator;
    }
}

void TController::MoveForwardFirstIterator() {
    MoveForwardIterator(FirstDeque);
    View->DrawFirstDeque(FirstDeque);
}

void TController::MoveBackwardFirstIterator() {
    MoveBackwardIterator(FirstDeque);
    View->DrawFirstDeque(FirstDeque);
}

void TController::MoveForwardSecondIterator() {
    MoveForwardIterator(SecondDeque);
    View->DrawSecondDeque(SecondDeque);
}

void TController::MoveBackwardSecondIterator() {
    MoveBackwardIterator(SecondDeque);
    View->DrawSecondDeque(SecondDeque);
}

void TController::ChangeName(TDeque& deque, const QString& name) {
    *deque.Iterator = name;
}

void TController::ChangeFirstName(const QString& name) {
    ChangeName(FirstDeque, name);
    View->DrawFirstDeque(FirstDeque);
}

void TController::ChangeSecondName(const QString& name) {
    ChangeName(SecondDeque, name);
    View->DrawSecondDeque(SecondDeque);
}

void TController::CompareDeques() {
    View->DrawCompareResult(FirstDeque.Deque == SecondDeque.Deque);
}

void TController::PushCrawd(const QString& name) {
    Crawd.Accept(TFrontPusher(name));
    View->DrawCrawd(Crawd);
}

void TController::PopCrawd() {
    Crawd.Accept(TFrontPopper());
    View->DrawCrawd(Crawd);
}
