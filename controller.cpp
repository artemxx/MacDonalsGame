#include "controller.h"

TController::TController(TAbstractView* view)
    : View(view), FirstDeque(), SecondDeque(),
      FirstIterator(FirstDeque.begin()), SecondIterator(SecondDeque.begin()) {}

void TController::PushFirstDequeFront(const QString& name) {
    FirstDeque.PushFront(name);
    if (FirstDeque.GetSize() == 1) {
        FirstIterator = FirstDeque.begin();
    }
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::PushFirstDequeBack(const QString& name) {
    FirstDeque.PushBack(name);
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
    FirstDeque.PopFront();
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::PopFirstDequeBack() {
    if (FirstDeque.IsEmpty()) {
        return;
    }
    if (FirstIterator == --FirstDeque.end()) {
        FirstIterator = FirstDeque.begin();
    }
    FirstDeque.PopBack();
    View->DrawFirstDeque(FirstDeque, FirstIterator);
}

void TController::PushSecondDequeFront(const QString& name) {
    SecondDeque.PushFront(name);
    if (SecondDeque.GetSize() == 1) {
        SecondIterator = SecondDeque.begin();
    }
    View->DrawSecondDeque(SecondDeque, SecondIterator);
}

void TController::PushSecondDequeBack(const QString& name) {
    SecondDeque.PushBack(name);
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
    SecondDeque.PopFront();
    View->DrawSecondDeque(SecondDeque, SecondIterator);
}

void TController::PopSecondDequeBack() {
    if (SecondDeque.IsEmpty()) {
        return;
    }
    if (SecondIterator == --SecondDeque.end()) {
        SecondDeque.begin();
    }
    SecondDeque.PopBack();
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
