#include "dialog11.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog11 w;
    w.show();

    return a.exec();
}
