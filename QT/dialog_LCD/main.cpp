#include "dialog_lcd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dialog_LCD w;
    w.show();

    return a.exec();
}
