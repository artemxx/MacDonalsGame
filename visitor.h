#pragma once

#include "peoplegroup.h"

#include <QString>

class TVisitor {
public:
    virtual ~TVisitor() = default;

    virtual void Visit(TDeque& deque) const = 0;

    virtual void Visit(TCrawd&) const {}
};

class TFrontPusher : public TVisitor {
public:
    TFrontPusher(const QString& name);
    ~TFrontPusher() override = default;

    void Visit(TDeque& deque) const override;
    void Visit(TCrawd& crawd) const override;

private:
    const QString Name;
};

class TBackPusher : public TVisitor {
public:
    TBackPusher(const QString& name);
    ~TBackPusher() override = default;

    void Visit(TDeque& deque) const override;

private:
    const QString Name;
};

class TFrontPopper : public TVisitor {
public:
    ~TFrontPopper() override = default;

    void Visit(TDeque& deque) const override;
    void Visit(TCrawd& crawd) const override;
};

class TBackPopper : public TVisitor {
public:
    ~TBackPopper() override = default;

    void Visit(TDeque& deque) const override;
};
