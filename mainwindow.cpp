#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

TMainWindow::TMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , Ui(new Ui::MainWindow)
    , LeftLabel(new QLabel("В очереди:"))
    , RightLabel(new QLabel("В очереди:"))
    , LeftNumber(new QLCDNumber())
    , RightNumber(new QLCDNumber())
    , LeftTextInput(new QLineEdit())
    , RightTextInput(new QLineEdit())
    , LeftBackServeButton(new QPushButton("Обслужить с конца (Я.Еда)"))
    , RightBackServeButton(new QPushButton("Обслужить с конца (Я.Еда)"))
    , LeftFrontServeButton(new QPushButton("Обслужить"))
    , RightFrontServeButton(new QPushButton("Обслужить"))
    , AddClientFrontLeftButton(new QPushButton("Мне только спросить"))
    , AddClientFrontRightButton(new QPushButton("Мне только спросить"))
    , AddClientBackLeftButton(new QPushButton("Встать в конец"))
    , AddClientBackRightButton(new QPushButton("Встать в конец"))
    , Layout(new QGridLayout())
{
    Ui->setupUi(this);

    AddWidgets();

    auto widget = new QWidget();
    widget->setLayout(Layout);
    setCentralWidget(widget);

    connect(LeftTextInput, &QLineEdit::returnPressed, [&](){
        static int cnt = 0;
        qDebug() << "Test message #" << ++cnt;
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
