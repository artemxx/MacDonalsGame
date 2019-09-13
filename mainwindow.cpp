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
    , LeftTextInput(new QLineEdit())
    , RightTextInput(new QLineEdit())
    , ComparisonButton(new QPushButton("Сравнить очереди"))
    , AddClientFrontLeftButton(new QPushButton("Мне только спросить"))
    , AddClientFrontRightButton(new QPushButton("Мне только спросить"))
    , AddClientBackLeftButton(new QPushButton("Встать в конец"))
    , AddClientBackRightButton(new QPushButton("Встать в конец"))
    , Labels(MAX_DISPLAYED_COUNT)
    , Layout(new QGridLayout())
    , Controller(new TDequeController(this))
{
    Ui->setupUi(this);
    setMinimumSize(1000, 700);

    AddWidgets();

    auto widget = new QWidget();
    widget->setLayout(Layout);
    setCentralWidget(widget);

    connect(LeftTextInput, &QLineEdit::returnPressed, [&](){
        Controller->PushFirstDequeFront(LeftTextInput->text());
        // TODO: remove this .....uck
        LeftTextInput->setText("");
    });
    connect(RightTextInput, &QLineEdit::returnPressed, [&](){
        static int cnt = 0;
        qDebug() << "Kekt message #" << ++cnt;
    });
    connect(AddClientFrontLeftButton, &QPushButton::clicked, [&](){
        static int cnt = 0;
        qDebug() << "Test message #" << ++cnt;
    });
    connect(AddClientFrontRightButton, &QPushButton::clicked, [&](){
        static int cnt = 0;
        qDebug() << "Test message #" << ++cnt;
    });
    connect(AddClientBackLeftButton, &QPushButton::clicked, [&](){
        static int cnt = 0;
        qDebug() << "Test message #" << ++cnt;
    });
    connect(AddClientBackRightButton, &QPushButton::clicked, [&](){
        static int cnt = 0;
        qDebug() << "Test message #" << ++cnt;
    });
    connect(ComparisonButton, &QPushButton::clicked, [&](){
       Controller->CompareDeques();
    });
}

TMainWindow::~TMainWindow() {
    delete Ui;
    delete Controller;
}

void TMainWindow::DrawSecondDeque(const TBiDirectionalList<QString> &deque)
{
    DrawFirstDeque(deque);
}

void TMainWindow::DrawCompareResult(bool result)
{
    DrawFirstDeque({});
}

void TMainWindow::DrawFirstDeque(const TBiDirectionalList<QString> &deque) {
    for (auto& label : Labels) {
        label->setText("");
    }

    int displayedCount = 0;
    typename TBiDirectionalList<QString>::TConstIterator it = deque.begin();
    for (; ++displayedCount <= MAX_DISPLAYED_COUNT && it.IsValid(); ++it) {
        Labels[displayedCount - 1]->setText(*it);
    }

    // TODO: what is it
    // repaint();
}
