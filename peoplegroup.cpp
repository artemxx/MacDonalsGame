#include "peoplegroup.h"
#include "visitor.h"

TDeque::TDeque()
    : Deque()
    , Iterator(Deque.begin())
    {
    }

void TDeque::Accept(const TVisitor& visitor) {
    visitor.Visit(*this);
}

void TCrawd::Accept(const TVisitor& visitor) {
    visitor.Visit(*this);
}
