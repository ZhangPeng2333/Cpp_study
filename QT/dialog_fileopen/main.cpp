#include "dialog_fileopen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog_fileopen w;
    w.show();

    return a.exec();
}
