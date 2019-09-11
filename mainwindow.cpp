#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    test_button_ = new QPushButton("My Button", this);
    test_button_->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(test_button_, SIGNAL(released()), this, SLOT(OnTestButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnTestButtonClicked() {
    static int cnt = 0;
    qDebug() << "Test message #" << ++cnt;
}

