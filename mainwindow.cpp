#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QVector>

TMainWindow::TMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , Ui(new Ui::MainWindow)
    , LeftLabel(new QLabel("В очереди:"))
    , RightLabel(new QLabel("В очереди:"))
    , LeftNumber(new QLCDNumber())
    , RightNumber(new QLCDNumber())
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
    , LeftLabels(NConstants::MAX_DISPLAYED_COUNT)
    , RightLabels(NConstants::MAX_DISPLAYED_COUNT)
    , Layout(new QGridLayout())
    , Controller(new TDequeController(this))
{
    Ui->setupUi(this);
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
}

TMainWindow::~TMainWindow() {
    delete Ui;
    delete Controller;
}

void TMainWindow::DrawFirstDeque(const TBiDirectionalList<QString> &deque) {
    // TODO: just clear?
    for (auto& label : LeftLabels) {
        label->setText("");
    }

    int displayedCount = 0;
    typename TBiDirectionalList<QString>::TConstIterator it = deque.begin();
    for (; ++displayedCount <= LeftLabels.size() && it.IsValid(); ++it) {
        LeftLabels[displayedCount - 1]->setText(*it);
    }

    // TODO: what is it
    // repaint();
}

// TODO: more wise name, not result
void TMainWindow::DrawCompareResult(bool result) {
    QPalette palette = ComparisonButton->palette();
    if (result) {
        palette.setColor(QPalette::Button, Qt::green);
    } else {
        palette.setColor(QPalette::Button, Qt::red);
    }

    qDebug() << result;
    ComparisonButton->setPalette(palette);
}

void TMainWindow::DrawSecondDeque(const TBiDirectionalList<QString> &deque)
{
    // TODO: just clear?
    for (auto& label : RightLabels) {
        label->setText("");
    }

    int displayedCount = 0;
    typename TBiDirectionalList<QString>::TConstIterator it = deque.begin();
    for (; ++displayedCount <= RightLabels.size() && it.IsValid(); ++it) {
        RightLabels[displayedCount - 1]->setText(*it);
    }

    // TODO: what is it
    // repaint();
}

