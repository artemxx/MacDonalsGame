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

class TMainWindow : public QMainWindow {
    Q_OBJECT

public:
    TMainWindow(QWidget* parent = nullptr);
    ~TMainWindow();

private:
    void AddWidget(QWidget* widget, int x, int y, Qt::AlignmentFlag flag = Qt::AlignmentFlag()) {
        static const auto itemSizePolicy
            = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        widget->setSizePolicy(itemSizePolicy);

        Layout->addWidget(widget, x, y, flag);
    }

    void AddWidgets() {
        AddWidget(LeftLabel, 0, 0, Qt::AlignCenter);
        AddWidget(RightLabel, 0, 5, Qt::AlignCenter);
        AddWidget(LeftNumber, 1, 0);
        AddWidget(RightNumber, 1, 5);
        AddWidget(LeftTextInput, 4, 0);
        AddWidget(RightTextInput, 4, 5);
        AddWidget(LeftBackServeButton, 2, 1);
        AddWidget(RightBackServeButton, 2, 4);
        AddWidget(LeftFrontServeButton, 3, 1);
        AddWidget(RightFrontServeButton, 3, 4);
        AddWidget(AddClientFrontLeftButton, 5, 0);
        AddWidget(AddClientFrontRightButton, 5, 5);
        AddWidget(AddClientBackLeftButton, 6, 0);
        AddWidget(AddClientBackRightButton, 6, 5);
    }

private:
    // TODO: group by sence & chande order
    Ui::MainWindow *Ui;
    QLabel* LeftLabel;
    QLabel* RightLabel;
    QLCDNumber* LeftNumber;
    QLCDNumber* RightNumber;
    QLineEdit* LeftTextInput;
    QLineEdit* RightTextInput;
    QPushButton* LeftBackServeButton;
    QPushButton* RightBackServeButton;
    QPushButton* LeftFrontServeButton;
    QPushButton* RightFrontServeButton;
    QPushButton* AddClientFrontLeftButton;
    QPushButton* AddClientFrontRightButton;
    QPushButton* AddClientBackLeftButton;
    QPushButton* AddClientBackRightButton;
    QGridLayout* Layout;
};
