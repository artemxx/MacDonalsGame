#include "mainwindow.h"
#include "test.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
    TestAll();
    QApplication a(argc, argv);
    TMainWindow w;
    w.show();

    return a.exec();
}
