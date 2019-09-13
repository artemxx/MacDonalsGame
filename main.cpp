#include "view.h"
#include "test.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    TestAll();
    QApplication a(argc, argv);
    TView w;
    w.show();

    return a.exec();
}
