#include "dialog_lcd.h"
#include "ui_dialog_lcd.h"
#include<QString>
#include <QDateTime>

dialog_LCD::dialog_LCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_LCD)
{
    ui->setupUi(this);

    timeoutSlot();
    timer = new QTimer(this);
    timer->setSingleShot(false);//周期性
    timer->setInterval(100);//间隔时间

    //连接信号槽
    connect(timer,SIGNAL(timeout()),
            this,SLOT(timeoutSlot()));

    timer->start();





}

void dialog_LCD::timeoutSlot(){
    //获取当前时间并显示
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->display(time);
}

dialog_LCD::~dialog_LCD()
{
    delete ui;
    if(timer->isActive())
        timer->stop();
    delete timer;
}
