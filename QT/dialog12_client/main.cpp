#include "dialog12_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog12_client w;
    w.show();

    return a.exec();
}
