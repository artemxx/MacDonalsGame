#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QLCDNumber>

#include "abstractview.h"
#include "controller.h"
#include "peoplegroup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

    void DrawCrawd(const TCrawd& crawd) override;

private:
    void DiscardCompareButton();

    void AddWidget(QWidget* widget, int x, int y, int sx = 1, int sy = 1,
                   Qt::AlignmentFlag flag = Qt::AlignmentFlag());

    void AddWidgets();

    static void SetRandomName(QLineEdit* widget);

private:
    struct TImages {
        QLabel* CreateLabel(const QString& image);

        TImages(const QString& dragonFly, const QString& artemx, const QString& mac,
                const QString& kfc, const QString& yEda, const QString& kroshka);

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
    QVector<QLabel*> CrawdLabels;

    TImages Images;

    QGridLayout* Layout;

    TController* Controller;
};
