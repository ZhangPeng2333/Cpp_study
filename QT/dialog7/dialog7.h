#ifndef DIALOG7_H
#define DIALOG7_H

#include <QDialog>
#include"student.h"

namespace Ui {
class dialog7;
}

class dialog7 : public QDialog
{
    Q_OBJECT

public:
    explicit dialog7(QWidget *parent = 0);
    ~dialog7();

private:
    Ui::dialog7 *ui;
};

#endif // DIALOG7_H
