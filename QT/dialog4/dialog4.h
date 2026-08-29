#ifndef DIALOG4_H
#define DIALOG4_H

#include <QMainWindow>

namespace Ui {
class dialog4;
}

class dialog4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit dialog4(QWidget *parent = 0);
    ~dialog4();

private:
    Ui::dialog4 *ui;

private slots:
    void mySlot(int value);

};

#endif // DIALOG4_H
