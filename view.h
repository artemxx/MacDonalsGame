#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QLCDNumber>
#include <QStyle>
#include <random>
#include <chrono>

#include "abstractview.h"
#include "controller.h"
#include "peoplegroup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace NConstants {
    constexpr auto MAX_DISPLAYED_COUNT_DEQUE = 8;
    constexpr auto MAX_DISPLAYED_COUNT_CROWD = 10;

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
        "Progmatic",
        "Gepardo",
        "Melnik",
        "Aleex",
        "Magneet",
        "Fedosik",
        "LamaMarine",
        "Sigismundych"
    };

    static std::mt19937 twister(std::chrono::steady_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<int> gen(0, RandomNames.size() - 1);

    static QString GetRandomName() {
        const int ind = gen(twister);
        return RandomNames[ind];
    }
} // NConstants

class TView : public QMainWindow, public TAbstractView {
    Q_OBJECT

public:
    TView(QWidget* parent = nullptr);
    ~TView() override;

    void EnableRightButtons(bool is_enabled);

    void EnableLeftButtons(bool is_enabled);

    void DrawFirstDeque(const TDeque& firstDeque) override;
    void DrawSecondDeque(const TDeque& secondDeque) override;

    void DrawCompareResult(bool result) override;

private:
    void DiscardCompareButton();

    void AddWidget(QWidget* widget, int x, int y, int sx = 1, int sy = 1,
                   Qt::AlignmentFlag flag = Qt::AlignmentFlag()) {
        static const auto itemSizePolicy
            = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        widget->setSizePolicy(itemSizePolicy);

        Layout->addWidget(widget, x, y, sx, sy, flag);
    }

    void AddWidgets() {
        AddWidget(LeftLabel, 0, 0, 1, 2, Qt::AlignCenter);
        AddWidget(RightLabel, 0, 6, 1, 2, Qt::AlignCenter);

        AddWidget(LeftNumber, 1, 0, 1, 2);
        AddWidget(RightNumber, 1, 6, 1, 2);

        AddWidget(LeftBackServeButton, 2, 2);
        AddWidget(RightBackServeButton, 2, 5);
        AddWidget(LeftFrontServeButton, 3, 2);
        AddWidget(RightFrontServeButton, 3, 5);

        AddWidget(LeftTextInput, 4, 0, 1, 2);
        AddWidget(RightTextInput, 4, 6, 1, 2);

        AddWidget(ComparisonButton, 4, 3, 1, 2);

        AddWidget(AddClientFrontLeftButton, 5, 0, 1, 2);
        AddWidget(AddClientFrontRightButton, 5, 6, 1, 2);
        AddWidget(AddClientBackLeftButton, 6, 0, 1, 2);
        AddWidget(AddClientBackRightButton, 6, 6, 1, 2);

        AddWidget(LeftNextIteratorButton, 8, 0);
        AddWidget(LeftPrevIteratorButton, 8, 1);
        AddWidget(LeftIteratorTextInput, 9, 0, 1, 2);
        AddWidget(LeftNameChangeButton, 10, 0, 1, 2);

        AddWidget(RightNextIteratorButton, 8, 6);
        AddWidget(RightPrevIteratorButton, 8, 7);
        AddWidget(RightIteratorTextInput, 9, 6, 1, 2);
        AddWidget(RightNameChangeButton, 10, 6, 1, 2);

        AddWidget(AddClientToCrowdButton, 6, 3);
        AddWidget(ServeClientFromCrowdButton, 6, 4);

        for (int i = 0; i < NConstants::MAX_DISPLAYED_COUNT_DEQUE; ++i) {
            LeftLabels[i] = new QLabel();
            RightLabels[i] = new QLabel();

            AddWidget(LeftLabels[i], i + 4, 2);
            AddWidget(RightLabels[i], i + 4, 5);
        }

        for (int i = 0; i < NConstants::MAX_DISPLAYED_COUNT_CROWD; ++i) {
            CrowdLabels[i] = new QLabel();

            AddWidget(CrowdLabels[i], i % 5 + 7, 3 + i / 5);
        }

        AddWidget(Images.DragonFly, 2, 0, 2, 2, Qt::AlignCenter);
        AddWidget(Images.Artemx, 2, 6, 2, 2, Qt::AlignCenter);
        AddWidget(Images.Mac, 0, 2, 2, 1, Qt::AlignCenter);
        AddWidget(Images.Kfc, 0, 5, 2, 1, Qt::AlignCenter);
        AddWidget(Images.YEda, 0, 3, 2, 2, Qt::AlignCenter);
        AddWidget(Images.Kroshka, 2, 3, 2, 2, Qt::AlignCenter);

        for (int i = 0; i <= 11; ++i) {
            Layout->setRowStretch(i, (i != 1) ? 1 : 2);
        }
        for (int i = 0; i <= 7; ++i) {
            int stretch = 2;
            if (i <= 1 || i >= 6) {
                stretch = 1;
            }

            Layout->setColumnStretch(i, stretch);
        }
    }

    static void SetRandomName(QLineEdit* widget) {
        widget->setText(NConstants::GetRandomName());
    }

private:
    struct TImages {
        QLabel* CreateLabel(const QString& image) {
            QPixmap pixmap(image);
            QLabel* label = new QLabel();
            label->setPixmap(pixmap);
            label->setScaledContents(true);

            return label;
        }

        TImages(const QString& dragonFly, const QString& artemx, const QString& mac,
                const QString& kfc, const QString& yEda, const QString& kroshka)
            : DragonFly(CreateLabel(dragonFly))
            , Artemx(CreateLabel(artemx))
            , Mac(CreateLabel(mac))
            , Kfc(CreateLabel(kfc))
            , YEda(CreateLabel(yEda))
            , Kroshka(CreateLabel(kroshka))
        {
        }

        QLabel* DragonFly;
        QLabel* Artemx;
        QLabel* Mac;
        QLabel* Kfc;
        QLabel* YEda;
        QLabel* Kroshka;
    };

    QLabel* LeftLabel;
    QLabel* RightLabel;

    QLCDNumber* LeftNumber;
    QLCDNumber* RightNumber;

    // Serve client buttons
    QPushButton* LeftBackServeButton;
    QPushButton* RightBackServeButton;
    QPushButton* LeftFrontServeButton;
    QPushButton* RightFrontServeButton;

    // Input buttons
    QLineEdit* LeftTextInput;
    QLineEdit* RightTextInput;

    // Comparison button
    QPushButton* ComparisonButton;

    // Add client buttons
    QPushButton* AddClientFrontLeftButton;
    QPushButton* AddClientFrontRightButton;
    QPushButton* AddClientBackLeftButton;
    QPushButton* AddClientBackRightButton;

    // Left iterator buttons
    QPushButton* LeftNextIteratorButton;
    QPushButton* LeftPrevIteratorButton;
    QLineEdit* LeftIteratorTextInput;
    QPushButton* LeftNameChangeButton;

    // Right iterator buttons
    QPushButton* RightNextIteratorButton;
    QPushButton* RightPrevIteratorButton;
    QLineEdit* RightIteratorTextInput;
    QPushButton* RightNameChangeButton;

    // Crowd control buttons
    QPushButton* AddClientToCrowdButton;
    QPushButton* ServeClientFromCrowdButton;

    // People names
    QVector<QLabel*> LeftLabels;
    QVector<QLabel*> RightLabels;
    QVector<QLabel*> CrowdLabels;

    TImages Images;

    QGridLayout* Layout;

    TController* Controller;
};
