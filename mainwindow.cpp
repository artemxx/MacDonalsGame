#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , Ui(new Ui::MainWindow)
{
    Ui->setupUi(this);

    TestButton = new QPushButton("My Button", this);
    TestButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(TestButton, SIGNAL(released()), this, SLOT(OnTestButtonClicked()));
}

MainWindow::~MainWindow() {
    delete Ui;
}

void MainWindow::OnTestButtonClicked() {
    static int cnt = 0;
    qDebug() << "Test message #" << ++cnt;
}

