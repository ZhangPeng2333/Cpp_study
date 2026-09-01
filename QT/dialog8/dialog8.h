#ifndef DIALOG8_H
#define DIALOG8_H

#include <QDialog>

namespace Ui {
class dialog8;
}

class dialog8 : public QDialog
{
    Q_OBJECT

public:
    explicit dialog8(QWidget *parent = 0);
    ~dialog8();

private:
    Ui::dialog8 *ui;
};

#endif // DIALOG8_H
