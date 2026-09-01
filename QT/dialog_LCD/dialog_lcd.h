#ifndef DIALOG_LCD_H
#define DIALOG_LCD_H

#include <QDialog>
#include<QTimer>

namespace Ui {
class dialog_LCD;
}

class dialog_LCD : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_LCD(QWidget *parent = 0);
    ~dialog_LCD();

private:
    Ui::dialog_LCD *ui;
    QTimer * timer;

private slots:
    void timeoutSlot();
};

#endif // DIALOG_LCD_H
