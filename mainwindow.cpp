#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , Ui(new Ui::MainWindow)
    , AddClientLeftButton(new QPushButton(tr("Add client")))
    , AddClientRightButton(new QPushButton(tr("Add client")))
    , Layout(new QGridLayout())
{
    Ui->setupUi(this);

    Layout->addWidget(AddClientLeftButton, 0, 0, Qt::AlignCenter);
    Layout->addWidget(AddClientRightButton, 0, 1, Qt::AlignCenter);

    auto widget = new QWidget();
    widget->setLayout(Layout);
    setCentralWidget(widget);

    connect(AddClientLeftButton, SIGNAL(released()), this, SLOT(OnAddClientLeftButtonClicked()));
    connect(AddClientRightButton, SIGNAL(released()), this, SLOT(OnAddClientRightButtonClicked()));
}

MainWindow::~MainWindow() {
    delete Ui;
}

void MainWindow::OnAddClientLeftButtonClicked() {
    static int cnt = 0;
    qDebug() << "Test message #" << ++cnt;
}

void MainWindow::OnAddClientRightButtonClicked() {
    static int cnt = 0;
    qDebug() << "Kek #" << ++cnt;
}
