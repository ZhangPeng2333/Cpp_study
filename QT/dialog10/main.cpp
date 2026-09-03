#include "dialog10.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog10 w;
    w.show();

    return a.exec();
}
