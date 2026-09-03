#include "dialog9.h"
#include "ui_dialog9.h"
#include<QDebug>
#include<QPixmap>
#include <QPainter>
#include <QKeyEvent>

dialog9::dialog9(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog9)
{
    ui->setupUi(this);
    m_pixmap.load(":/new/prefix1/pic.jpg");
    move(100, 100);
}

dialog9::~dialog9()
{
    delete ui;

}

void dialog9::paintEvent(QPaintEvent* ){
    qDebug()<<x()<<","<<y();
    qDebug()<<width()<<"x"<<height();

    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), m_pixmap);

    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
}

void dialog9::keyReleaseEvent(QKeyEvent * event){

    //判断按键是哪个
    int code = event->key();
    if(code == Qt::Key_A){
        int value = ui->progressBar->value();
        if(value!=0)
            ui->progressBar->setValue(--value);
    }
    else if(code == Qt::Key_D){
        int value = ui->progressBar->value();
        if(value!=100)
            ui->progressBar->setValue(++value);
    }
}
