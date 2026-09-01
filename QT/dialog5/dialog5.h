#ifndef DIALOG5_H
#define DIALOG5_H

#include <QDialog>

namespace Ui {
class dialog5;
}

class dialog5 : public QDialog
{
    Q_OBJECT

public:
    explicit dialog5(QWidget *parent = 0);
    ~dialog5();

private:
    Ui::dialog5 *ui;

private slots:
    void pageSlot(int,int);
    void selectionSlot();
};



#endif // DIALOG5_H
