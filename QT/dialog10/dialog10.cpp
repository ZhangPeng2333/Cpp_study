#include "dialog10.h"
#include "ui_dialog10.h"

#include<QDebug>
#include<QPixmap>
#include<QPainter>
#include<QKeyEvent>
#include<QEvent>
#include<QObject>


dialog10::dialog10(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog10)
{
    ui->setupUi(this);
    // 给要检测的子组件注册事件过滤器
    // 当前的窗口去监控自组件的事件
    ui->lineEdit->installEventFilter(this);
}

dialog10::~dialog10()
{
    delete ui;
}

bool dialog10::eventFilter(QObject *watched, QEvent *event){
    if(watched == ui->lineEdit&&
            event->type() == QEvent::FocusIn)
    {
        qDebug()<<"蓝色输入框获取焦点！";

    }else if(watched == ui->lineEdit&&
             event->type() == QEvent::FocusOut){
        qDebug()<<"蓝色输入框失去焦点！";
    }
    return QDialog::eventFilter(watched,event);
}
