#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QLCDNumber>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void SetSizePolicy(QWidget* widget) {
        static const auto itemSizePolicy
            = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        widget->setSizePolicy(itemSizePolicy);
    }

    void SetSizePolicies() {
        SetSizePolicy(LeftLabel);
        SetSizePolicy(RightLabel);
        SetSizePolicy(LeftNumber);
        SetSizePolicy(RightNumber);
        SetSizePolicy(LeftTextInput);
        SetSizePolicy(RightTextInput);
        SetSizePolicy(AddClientFrontLeftButton);
        SetSizePolicy(AddClientFrontRightButton);
        SetSizePolicy(AddClientBackLeftButton);
        SetSizePolicy(AddClientBackRightButton);
    }

    void AddWidget(QWidget* widget, int x, int y, Qt::AlignmentFlag flag = Qt::AlignmentFlag()) {
        Layout->addWidget(widget, x, y, flag);
    }

    void AddWidgets() {
        AddWidget(LeftLabel, 0, 0, Qt::AlignCenter);
        AddWidget(RightLabel, 0, 5, Qt::AlignCenter);
        AddWidget(LeftNumber, 1, 0);
        AddWidget(RightNumber, 1, 5);
        AddWidget(LeftTextInput, 2, 0);
        AddWidget(RightTextInput, 2, 5);
        AddWidget(AddClientFrontLeftButton, 3, 0);
        AddWidget(AddClientFrontRightButton, 3, 5);
        AddWidget(AddClientBackLeftButton, 4, 0);
        AddWidget(AddClientBackRightButton, 4, 5);
    }

private:
    Ui::MainWindow *Ui;
    QLabel* LeftLabel;
    QLabel* RightLabel;
    QLCDNumber* LeftNumber;
    QLCDNumber* RightNumber;
    QLineEdit* LeftTextInput;
    QLineEdit* RightTextInput;
    QPushButton* AddClientFrontLeftButton;
    QPushButton* AddClientFrontRightButton;
    QPushButton* AddClientBackLeftButton;
    QPushButton* AddClientBackRightButton;
    QGridLayout* Layout;
};
