#include "dialog8.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog8 w;
    w.show();

    return a.exec();
}
