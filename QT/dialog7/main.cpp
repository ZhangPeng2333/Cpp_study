#include "dialog7.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog7 w;
    w.show();

    return a.exec();
}
