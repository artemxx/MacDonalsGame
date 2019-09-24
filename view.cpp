#include <QVector>

#include <QDebug>
#include <QStyle>

#include "view.h"
#include "ui_mainwindow.h"
#include "peoplegroup.h"
#include "constants.h"

TView::TView(QWidget *parent)
    : QMainWindow(parent)
    , LeftLabel(new QLabel("В очереди:"))
    , RightLabel(new QLabel("В очереди:"))
    , LeftNumber(new QLCDNumber)
    , RightNumber(new QLCDNumber)
    , LeftBackServeButton(new QPushButton("Обслужить с конца\n(Я.Еда)"))
    , RightBackServeButton(new QPushButton("Обслужить с конца\n(Я.Еда)"))
    , LeftFrontServeButton(new QPushButton("Обслужить с начала"))
    , RightFrontServeButton(new QPushButton("Обслужить с начала"))
    , LeftTextInput(new QLineEdit(NConstants::GetRandomName()))
    , RightTextInput(new QLineEdit(NConstants::GetRandomName()))
    , ComparisonButton(new QPushButton("Сравнить очереди"))
    , AddClientFrontLeftButton(new QPushButton("Мне только спросить"))
    , AddClientFrontRightButton(new QPushButton("Мне только спросить"))
    , AddClientBackLeftButton(new QPushButton("Встать в конец"))
    , AddClientBackRightButton(new QPushButton("Встать в конец"))
    , LeftNextIteratorButton(new QPushButton("Вперёд"))
    , LeftPrevIteratorButton(new QPushButton("Назад"))
    , LeftIteratorTextInput(new QLineEdit)
    , LeftNameChangeButton(new QPushButton("Сменить имя"))
    , RightNextIteratorButton(new QPushButton("Вперёд"))
    , RightPrevIteratorButton(new QPushButton("Назад"))
    , RightIteratorTextInput(new QLineEdit)
    , RightNameChangeButton(new QPushButton("Сменить имя"))
    , AddClientToCrowdButton(new QPushButton("Кинуть в толпу"))
    , ServeClientFromCrowdButton(new QPushButton("Выкинуть из толпы"))
    , LeftLabels(NConstants::MAX_DISPLAYED_COUNT_DEQUE)
    , RightLabels(NConstants::MAX_DISPLAYED_COUNT_DEQUE)
    , CrawdLabels(NConstants::MAX_DISPLAYED_COUNT_CROWD)
    , Images(":/images/dragonfly.jpg", ":/images/artemxx.jpg", ":/images/mac.jpeg",
             ":/images/kfc.jpg", ":/images/eda.jpg", ":/images/kroshka.jpg")
    , Layout(new QGridLayout())
    , Controller(new TController(this))
{
    setMinimumSize(1000, 700);

    AddWidgets();

    auto widget = new QWidget();
    widget->setLayout(Layout);
    setCentralWidget(widget);

    // Serve client buttons
    connect(LeftBackServeButton, &QPushButton::clicked, [&](){
        Controller->PopFirstDequeBack();
    });
    connect(RightBackServeButton, &QPushButton::clicked, [&](){
        Controller->PopSecondDequeBack();
    });
    connect(LeftFrontServeButton, &QPushButton::clicked, [&](){
        Controller->PopFirstDequeFront();
    });
    connect(RightFrontServeButton, &QPushButton::clicked, [&](){
        Controller->PopSecondDequeFront();
    });

    // Input buttons
    connect(LeftTextInput, &QLineEdit::returnPressed, [&](){
        Controller->PushFirstDequeFront(LeftTextInput->text());
        SetRandomName(LeftTextInput);
    });
    connect(RightTextInput, &QLineEdit::returnPressed, [&](){
        Controller->PushSecondDequeFront(RightTextInput->text());
        SetRandomName(RightTextInput);
    });

    // Comparison button
    connect(ComparisonButton, &QPushButton::clicked, [&](){
       Controller->CompareDeques();
    });

    // Add client buttons
    connect(AddClientFrontLeftButton, &QPushButton::clicked, [&](){
        Controller->PushFirstDequeFront(LeftTextInput->text());
        SetRandomName(LeftTextInput);
    });
    connect(AddClientFrontRightButton, &QPushButton::clicked, [&](){
        Controller->PushSecondDequeFront(RightTextInput->text());
        SetRandomName(RightTextInput);
    });
    connect(AddClientBackLeftButton, &QPushButton::clicked, [&](){
        Controller->PushFirstDequeBack(LeftTextInput->text());
        SetRandomName(LeftTextInput);
    });
    connect(AddClientBackRightButton, &QPushButton::clicked, [&](){
        Controller->PushSecondDequeBack(RightTextInput->text());
        SetRandomName(RightTextInput);
    });

    // Left iterator buttons
    connect(LeftNextIteratorButton, &QPushButton::clicked, [&](){
        Controller->MoveForwardFirstIterator();
    });
    connect(LeftPrevIteratorButton, &QPushButton::clicked, [&](){
        Controller->MoveBackwardFirstIterator();
    });
    connect(LeftIteratorTextInput, &QLineEdit::returnPressed, [&](){
        Controller->ChangeFirstName(LeftIteratorTextInput->text());
    });
    connect(LeftNameChangeButton, &QPushButton::clicked, [&](){
        Controller->ChangeFirstName(LeftIteratorTextInput->text());
    });

    // Right iterator buttons
    connect(RightNextIteratorButton, &QPushButton::clicked, [&](){
        Controller->MoveForwardSecondIterator();
    });
    connect(RightPrevIteratorButton, &QPushButton::clicked, [&](){
        Controller->MoveBackwardSecondIterator();
    });
    connect(RightIteratorTextInput, &QLineEdit::returnPressed, [&](){
        Controller->ChangeSecondName(RightIteratorTextInput->text());
    });
    connect(RightNameChangeButton, &QPushButton::clicked, [&](){
        Controller->ChangeSecondName(RightIteratorTextInput->text());
    });

    // Crowd control buttons
    connect(AddClientToCrowdButton, &QPushButton::clicked, [&](){
        Controller->PushCrawd(NConstants::GetRandomName());
    });
    connect(ServeClientFromCrowdButton, &QPushButton::clicked, [&](){
        Controller->PopCrawd();
    });

    EnableLeftButtons(false);
    EnableRightButtons(false);
}

TView::~TView() {
    delete Controller;
}

void TView::EnableRightButtons(bool enabled) {
    RightNextIteratorButton->setEnabled(enabled);
    RightPrevIteratorButton->setEnabled(enabled);
    RightNameChangeButton->setEnabled(enabled);
    RightIteratorTextInput->setEnabled(enabled);
    if (!enabled) {
        RightIteratorTextInput->setText("");
    }
}

void TView::EnableLeftButtons(bool enabled) {
    LeftNextIteratorButton->setEnabled(enabled);
    LeftPrevIteratorButton->setEnabled(enabled);
    LeftNameChangeButton->setEnabled(enabled);
    LeftIteratorTextInput->setEnabled(enabled);
    if (!enabled) {
        LeftIteratorTextInput->setText("");
    }
}

void TView::DrawFirstDeque(const TDeque& firstDeque) {
    const auto& deque = firstDeque.Deque;
    const auto& current = firstDeque.Iterator;
    for (auto& label : LeftLabels) {
        label->clear();
        label->setFrameStyle(QFrame::NoFrame);
    }

    LeftNumber->display(deque.GetSize());

    DiscardCompareButton();
    if (deque.IsEmpty()) {
        EnableLeftButtons(false);
        return;
    } else {
        EnableLeftButtons(true);
    }

    auto it = deque.begin();
    for (int displayedCount = 0; displayedCount < LeftLabels.size() &&
         it.IsValid(); ++it, ++displayedCount) {
        if (it == current) {
            LeftLabels[displayedCount - 1]->setFrameStyle(QFrame::Panel);
        }
        LeftLabels[displayedCount - 1]->setText(*it);
    }
    LeftIteratorTextInput->setText(*current);
}


void TView::DrawSecondDeque(const TDeque& secondDeque) {
    const auto& deque = secondDeque.Deque;
    const auto& current = secondDeque.Iterator;
    for (auto& label : RightLabels) {
        label->clear();
        label->setFrameStyle(QFrame::NoFrame);
    }

    RightNumber->display(deque.GetSize());

    DiscardCompareButton();
    if (deque.IsEmpty()) {
        EnableRightButtons(false);
        return;
    } else {
        EnableRightButtons(true);
    }


    typename TBiDirectionalList<QString>::TConstIterator it = deque.begin();
    for (int displayedCount = 0; displayedCount < RightLabels.size() &&
         it.IsValid(); ++it, ++displayedCount)
    {
        if (it == current) {
            RightLabels[displayedCount]->setFrameStyle(QFrame::Panel);
        }
        RightLabels[displayedCount]->setText(*it);
    }
    RightIteratorTextInput->setText(*current);
}

void TView::DrawCompareResult(bool equal) {
    QPalette palette = ComparisonButton->palette();
    if (equal) {
        palette.setColor(QPalette::Button, Qt::green);
    } else {
        palette.setColor(QPalette::Button, Qt::red);
    }

    ComparisonButton->setPalette(palette);
}

void TView::DrawCrawd(const TCrawd& crawd) {
    for (auto& label : CrawdLabels) {
        label->clear();
    }

    for (int displayedCount = 0; displayedCount < CrawdLabels.size() &&
         displayedCount < crawd.Crawd.size(); ++displayedCount)
    {
        CrawdLabels[displayedCount]->setText(crawd.Crawd.at(displayedCount));
    }
}


void TView::DiscardCompareButton() {
    QPalette palette = ComparisonButton->palette();
    ComparisonButton->setPalette(ComparisonButton->style()->standardPalette());
}

void TView::AddWidget(QWidget *widget, int x, int y, int sx, int sy, Qt::AlignmentFlag flag) {
    static const auto itemSizePolicy
            = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    widget->setSizePolicy(itemSizePolicy);

    Layout->addWidget(widget, x, y, sx, sy, flag);
}

void TView::AddWidgets() {
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

    for (int i = 0; i < LeftLabels.size(); ++i) {
        LeftLabels[i] = new QLabel();
        AddWidget(LeftLabels[i], i + 4, 2);
    }
    for (int i = 0; i < RightLabels.size(); ++i) {
        RightLabels[i] = new QLabel();
        AddWidget(RightLabels[i], i + 4, 5);
    }

    for (int i = 0; i < CrawdLabels.size(); ++i) {
        CrawdLabels[i] = new QLabel();
        AddWidget(CrawdLabels[i], i % 5 + 7, 3 + i / 5);
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

void TView::SetRandomName(QLineEdit *widget) {
    widget->setText(NConstants::GetRandomName());
}


QLabel *TView::TImages::CreateLabel(const QString &image) {
    QPixmap pixmap(image);
    QLabel* label = new QLabel();
    label->setPixmap(pixmap);
    label->setScaledContents(true);

    return label;
}

TView::TImages::TImages(const QString &dragonFly, const QString &artemx, const QString &mac,
                        const QString &kfc, const QString &yEda, const QString &kroshka)
    : DragonFly(CreateLabel(dragonFly))
    , Artemx(CreateLabel(artemx))
    , Mac(CreateLabel(mac))
    , Kfc(CreateLabel(kfc))
    , YEda(CreateLabel(yEda))
    , Kroshka(CreateLabel(kroshka))
{
}
