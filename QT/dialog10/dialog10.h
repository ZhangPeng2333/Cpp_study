#ifndef DIALOG10_H
#define DIALOG10_H

#include <QDialog>

namespace Ui {
class dialog10;
}

class dialog10 : public QDialog
{
    Q_OBJECT

public:
    explicit dialog10(QWidget *parent = 0);
    ~dialog10();

private:
    Ui::dialog10 *ui;
    bool eventFilter(QObject *, QEvent *);
};

#endif // DIALOG10_H
