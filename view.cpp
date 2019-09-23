#include <QVector>

#include "view.h"
#include "ui_mainwindow.h"

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
    , CrowdLabels(NConstants::MAX_DISPLAYED_COUNT_CROWD)
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
    connect(LeftNameChangeButton, &QPushButton::clicked, [&](){
        Controller->ChangeFirstName(LeftIteratorTextInput->text());
    });
    connect(LeftIteratorTextInput, &QLineEdit::returnPressed, [&](){
        Controller->ChangeFirstName(LeftIteratorTextInput->text());
    });

    // Right iterator buttons
    connect(RightNextIteratorButton, &QPushButton::clicked, [&](){
        Controller->MoveForwardSecondIterator();
    });
    connect(RightPrevIteratorButton, &QPushButton::clicked, [&](){
        Controller->MoveBackwardSecondIterator();
    });
    connect(RightNameChangeButton, &QPushButton::clicked, [&](){
        Controller->ChangeSecondName(RightIteratorTextInput->text());
    });
    connect(RightIteratorTextInput, &QLineEdit::returnPressed, [&](){
        Controller->ChangeSecondName(RightIteratorTextInput->text());
    });

    EnableLeftButtons(false);
    EnableRightButtons(false);
}

TView::~TView() {
    delete Controller;
}

void TView::EnableRightButtons(bool is_enabled) {
    RightNextIteratorButton->setEnabled(is_enabled);
    RightPrevIteratorButton->setEnabled(is_enabled);
    RightNameChangeButton->setEnabled(is_enabled);
    RightIteratorTextInput->setEnabled(is_enabled);
}

void TView::EnableLeftButtons(bool is_enabled) {
    LeftNextIteratorButton->setEnabled(is_enabled);
    LeftPrevIteratorButton->setEnabled(is_enabled);
    LeftNameChangeButton->setEnabled(is_enabled);
    LeftIteratorTextInput->setEnabled(is_enabled);
}

void TView::DrawFirstDeque(const TBiDirectionalList<QString> &deque,
                           const TBiDirectionalList<QString>::TIterator current) {
    for (auto& label : LeftLabels) {
        label->clear();
        label->setFrameStyle(QFrame::NoFrame);
    }

    LeftNumber->display(deque.GetSize());

    if (deque.IsEmpty()) {
        EnableLeftButtons(false);
    } else {
        EnableLeftButtons(true);
    }

    int displayedCount = 0;
    typename TBiDirectionalList<QString>::TConstIterator it = deque.begin();
    for (; ++displayedCount <= LeftLabels.size() && it.IsValid(); ++it) {
        if (it == current) {
            LeftLabels[displayedCount - 1]->setFrameStyle(QFrame::Panel);
        }
        LeftLabels[displayedCount - 1]->setText(*it);
    }

    DiscardCompareButton();
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

void TView::DrawSecondDeque(const TBiDirectionalList<QString> &deque,
                            const TBiDirectionalList<QString>::TIterator current) {
    for (auto& label : RightLabels) {
        label->clear();
        label->setFrameStyle(QFrame::NoFrame);
    }

    RightNumber->display(deque.GetSize());

    if (deque.IsEmpty()) {
        EnableRightButtons(false);
    } else {
        EnableRightButtons(true);
    }

    int displayedCount = 0;
    typename TBiDirectionalList<QString>::TConstIterator it = deque.begin();
    for (; ++displayedCount <= RightLabels.size() && it.IsValid(); ++it) {
        if (it == current) {
            RightLabels[displayedCount - 1]->setFrameStyle(QFrame::Panel);
        }
        RightLabels[displayedCount - 1]->setText(*it);
    }

    DiscardCompareButton();
}

void TView::DiscardCompareButton() {
    QPalette palette = ComparisonButton->palette();
    ComparisonButton->setPalette(ComparisonButton->style()->standardPalette());
}

