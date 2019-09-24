#include <QDebug>

#include "visitor.h"
#include "constants.h"

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

void TFrontPusher::Visit(TCrawd& crawd) const {
    auto& list = crawd.Crawd;
    const int offset = NConstants::twister() % (list.size() + 1);
    list.insert(list.begin() + offset, Name);
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

void TFrontPopper::Visit(TCrawd& crawd) const {
    auto& list = crawd.Crawd;
    if (list.isEmpty()) {
        return;
    }

    const int randomIndex = NConstants::twister() % list.size();
    std::swap(list[randomIndex], list.back());
    crawd.Crawd.pop_back();
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
