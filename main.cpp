#include "mainwindow.h"
#include "test.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    TestAll();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
