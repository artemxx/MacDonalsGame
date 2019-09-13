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
    , LeftBackServeButton(new QPushButton("Обслужить с конца (Я.Еда)"))
    , RightBackServeButton(new QPushButton("Обслужить с конца (Я.Еда)"))
    , LeftFrontServeButton(new QPushButton("Обслужить"))
    , RightFrontServeButton(new QPushButton("Обслужить"))
    , LeftTextInput(new QLineEdit())
    , RightTextInput(new QLineEdit())
    , ComparisonButton(new QPushButton("Сравнить очереди"))
    , AddClientFrontLeftButton(new QPushButton("Мне только спросить"))
    , AddClientFrontRightButton(new QPushButton("Мне только спросить"))
    , AddClientBackLeftButton(new QPushButton("Встать в конец"))
    , AddClientBackRightButton(new QPushButton("Встать в конец"))
    , Layout(new QGridLayout())
{
    Ui->setupUi(this);
    setMinimumSize(1000, 700);

    AddWidgets();

    auto widget = new QWidget();
    widget->setLayout(Layout);
    setCentralWidget(widget);

    connect(LeftTextInput, &QLineEdit::returnPressed, [&](){
        static int cnt = 0;
        qDebug() << "Test message #" << ++cnt;
        LeftLabel->setText("");
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
}

TMainWindow::~TMainWindow() {
    delete Ui;
}

/*
void TMainWindow::DrawFirstDeque(const TBiDirectionalList<QString> &deque) {
    QVector<QLabel*> labels(MAX_DISPLAYED_COUNT);
    for (auto& label : labels) {
        label = new QLabel();
    }

    int displayedCount = 0;
    typename TBiDirectionalList<QString>::TConstIterator it = deque.begin();
    while (++displayedCount <= MAX_DISPLAYED_COUNT && it != deque.end()) {
        labels[displayedCount - 1]->setText(*it);
    }
}
*/
