#include "dialog12.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog12 w;
    w.show();

    return a.exec();
}
