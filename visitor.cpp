#include "visitor.h"

TFrontPusher::TFrontPusher(const QString &name)
    : Name(name)
{
}

TBackPusher::TBackPusher(const QString &name)
    : Name(name)
{
}

void TFrontPusher::Visit(TDeque& deque) const {
    deque.Deque.PushFront(Name);
    if (deque.Deque.GetSize() == 1) {
        deque.Iterator = deque.Deque.begin();
    }
}

void TBackPusher::Visit(TDeque& deque) const {
    deque.Deque.PushBack(Name);
    if (deque.Deque.GetSize() == 1) {
        deque.Iterator = deque.Deque.begin();
    }
}

void TFrontPopper::Visit(TDeque& deque) const {
    if (deque.Deque.IsEmpty()) {
        return;
    }
    if (deque.Iterator == deque.Deque.begin()) {
        ++deque.Iterator;
    }
    deque.Deque.PopFront();
}

void TBackPopper::Visit(TDeque& deque) const {
    if (deque.Deque.IsEmpty()) {
        return;
    }
    if (deque.Iterator == --deque.Deque.end()) {
        deque.Iterator = deque.Deque.begin();
    }
    deque.Deque.PopBack();
}
