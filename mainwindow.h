#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QLCDNumber>
#include <QDebug>
#include <QStyle>

#include "list.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TMainWindow : public QMainWindow {
    Q_OBJECT

public:
    TMainWindow(QWidget* parent = nullptr);
    ~TMainWindow();

    void DrawFirstDeque(const TBiDirectionalList<QString>& deque) {}
    void DrawSecondDeque(const TBiDirectionalList<QString>& deque) {}

    void DrawCompareResult(bool result) {}

private:
    void AddWidget(QWidget* widget, int x, int y, Qt::AlignmentFlag flag = Qt::AlignmentFlag()) {
        static const auto itemSizePolicy
            = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        widget->setSizePolicy(itemSizePolicy);

        Layout->addWidget(widget, x, y, flag);
    }

    void AddWidgets() {
        AddWidget(LeftLabel, 0, 0, Qt::AlignCenter);
        AddWidget(RightLabel, 0, 4, Qt::AlignCenter);

        AddWidget(LeftNumber, 1, 0);
        AddWidget(RightNumber, 1, 4);

        AddWidget(LeftBackServeButton, 2, 1);
        AddWidget(RightBackServeButton, 2, 3);
        AddWidget(LeftFrontServeButton, 3, 1);
        AddWidget(RightFrontServeButton, 3, 3);

        AddWidget(LeftTextInput, 4, 0);
        AddWidget(RightTextInput, 4, 4);

        AddWidget(ComparisonButton, 4, 2);

        AddWidget(AddClientFrontLeftButton, 5, 0);
        AddWidget(AddClientFrontRightButton, 5, 4);
        AddWidget(AddClientBackLeftButton, 6, 0);
        AddWidget(AddClientBackRightButton, 6, 4);

        for (int i = 0; i <= 6; ++i) {
            Layout->setRowStretch(i, (i != 1) ? 1 : 2);
        }
        for (int i = 0; i <= 4; ++i) {
            Layout->setColumnStretch(i, (i != 2) ? 2 : 3);
        }
    }

private:
    static constexpr auto MAX_DISPLAYED_COUNT = 8;
    Ui::MainWindow *Ui;

    QLabel* LeftLabel;
    QLabel* RightLabel;

    QLCDNumber* LeftNumber;
    QLCDNumber* RightNumber;

    QPushButton* LeftBackServeButton;
    QPushButton* RightBackServeButton;
    QPushButton* LeftFrontServeButton;
    QPushButton* RightFrontServeButton;

    QLineEdit* LeftTextInput;
    QLineEdit* RightTextInput;

    QPushButton* ComparisonButton;

    QPushButton* AddClientFrontLeftButton;
    QPushButton* AddClientFrontRightButton;
    QPushButton* AddClientBackLeftButton;
    QPushButton* AddClientBackRightButton;

    QGridLayout* Layout;
};
