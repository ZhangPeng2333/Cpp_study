#include "dialog6.h"
#include "ui_dialog6.h"
#include <QDebug>
#include<QMessageBox>

dialog6::dialog6(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog6)
{
    ui->setupUi(this);
    // 创建定时器对象
    timer = new QTimer(this);
    // 设置为一次性
    timer->setSingleShot(true);
    // 设置触发时间为5s
    timer->setInterval(5000);

    ui->pushButton->setText("5s");
    connect(ui->pushButton,SIGNAL(clicked()),this,
            SLOT(btnClickedSlot()));
    connect(timer,SIGNAL(timeout()),
            this,SLOT(timeoutSlot()));


}

dialog6::~dialog6()
{
    delete ui;
    delete timer;
}

void dialog6::btnClickedSlot(){
//启动计时器
    timer->start();
}

void dialog6::timeoutSlot(){
    qDebug()<<"Time is over!!!";

}
