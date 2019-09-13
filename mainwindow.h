#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QLCDNumber>
#include <QDebug>
#include <QStyle>
#include <QRandomGenerator>

#include "list.h"
#include "dequecontroller.h"
#include "abstractdequeview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace NConstants {
    constexpr auto MAX_DISPLAYED_COUNT = 8;

    const QVector<QString> RandomNames = {
        "Dragon-fly",
        "Artemx",
        "Kigan",
        "Jesus",
        "MCDavidas",
        "Kefaa",
        "Renkens",
        "Dasfex",
        "Tigerrrrr",
        "Tranvick",
        "Vitonka",
        "Chmel_Tolstiy",
        "Fivut",
        "Sind",
        "Progmatic"
    };

    static QRandomGenerator gen(2020);
    static QString GetRandomName() {
        const int ind = gen() % RandomNames.size();
        return RandomNames[ind];
    }
} // NConstants

class TMainWindow : public QMainWindow, public TAbstractDequeView {
    Q_OBJECT

public:
    TMainWindow(QWidget* parent = nullptr);
    ~TMainWindow() override;

    void DrawFirstDeque(const TBiDirectionalList<QString>& deque) override;
    void DrawSecondDeque(const TBiDirectionalList<QString>& deque) override;

    void DrawCompareResult(bool result) override;

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

        for (int i = 0; i < NConstants::MAX_DISPLAYED_COUNT; ++i) {
            LeftLabels[i] = new QLabel();
            RightLabels[i] = new QLabel();

            AddWidget(LeftLabels[i], i + 4, 1, Qt::AlignCenter);
            AddWidget(RightLabels[i], i + 4, 3, Qt::AlignCenter);
        }

        for (int i = 0; i <= 11; ++i) {
            Layout->setRowStretch(i, (i != 1) ? 1 : 2);
        }
        for (int i = 0; i <= 4; ++i) {
            Layout->setColumnStretch(i, (i != 2) ? 2 : 3);
        }
    }

    static void SetRandomName(QLineEdit* widget) {
        widget->setText(NConstants::GetRandomName());
    }

private:

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

    QVector<QLabel*> LeftLabels;
    QVector<QLabel*> RightLabels;

    QGridLayout* Layout;

    TDequeController* Controller;
};
