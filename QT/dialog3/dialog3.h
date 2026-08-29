#ifndef DIALOG3_H
#define DIALOG3_H

#include <QDialog>
#include<QPushButton>
#include<QGroupBox>

namespace Ui {
class Dialog3;
}

class Dialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3(QWidget *parent = 0);
    ~Dialog3();

private:
    Ui::Dialog3 *ui;
    QPushButton *btn1;
    QButtonGroup *group;
    int time;

private slots:
    void mySlote();
    void mySlot1(int id,bool checked);
};

#endif // DIALOG3_H
