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

#include "abstractdequeview.h"
#include "dequecontroller.h"
#include "list.h"

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

class TMainWindow : public QMainWindow, public TAbstractDequeView {
    Q_OBJECT

public:
    TMainWindow(QWidget* parent = nullptr);
    ~TMainWindow() override;

    void DrawFirstDeque(const TBiDirectionalList<QString>& deque) override;
    void DrawSecondDeque(const TBiDirectionalList<QString>& deque) override;

    void DrawCompareResult(bool result) override;

private:
    void DiscardCompareButton();

    void AddWidget(QWidget* widget, int x, int y, Qt::AlignmentFlag flag
                   = Qt::AlignmentFlag(), int sx = 1, int sy = 1) {
        static const auto itemSizePolicy
            = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        widget->setSizePolicy(itemSizePolicy);

        Layout->addWidget(widget, x, y, sx, sy, flag);
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

        AddWidget(Images.DragonFly, 2, 0, Qt::AlignCenter, 2, 1);
        AddWidget(Images.Artemx, 2, 4, Qt::AlignCenter, 2, 1);
        AddWidget(Images.Mac, 0, 1, Qt::AlignCenter, 2, 1);
        AddWidget(Images.Kfc, 0, 3, Qt::AlignCenter, 2, 1);
        AddWidget(Images.YEda, 0, 2, Qt::AlignCenter, 2, 1);
        AddWidget(Images.Kroshka, 2, 2, Qt::AlignCenter, 2, 1);

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

    QVector<QLabel*> LeftLabels;
    QVector<QLabel*> RightLabels;

    QGridLayout* Layout;

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
    } Images;

    TDequeController* Controller;
};
