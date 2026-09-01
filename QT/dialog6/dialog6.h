#ifndef DIALOG6_H
#define DIALOG6_H

#include <QDialog>
#include<QTimer>

namespace Ui {
class dialog6;
}

class dialog6 : public QDialog
{
    Q_OBJECT

public:
    explicit dialog6(QWidget *parent = 0);
    ~dialog6();

private:
    Ui::dialog6 *ui;
    QTimer * timer;

private slots:
    void btnClickedSlot();
    void timeoutSlot();
};

#endif // DIALOG6_H
