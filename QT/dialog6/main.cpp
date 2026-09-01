#include "dialog6.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog6 w;
    w.show();

    return a.exec();
}
