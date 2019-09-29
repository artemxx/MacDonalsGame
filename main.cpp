#include "view.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TView w;
    w.show();

    return a.exec();
}
