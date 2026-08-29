#include "dialog2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog2 w;
    w.show();

    return a.exec();
}
