#include "dialog5.h"
#include "ui_dialog5.h"
#include<QString>
#include<QDebug>
#include<QDateTime>

dialog5::dialog5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog5)
{
    qint64 start = QDateTime::currentMSecsSinceEpoch();
    //时间戳
    ui->setupUi(this);
    QString str = "你好スぬㅙㅞБЖ";

    qDebug()<<str[1]<<str.at(3);
    // mid从某个索引开始打印后面的
    // at效率高于 []
    ui->label->setText(str.mid(3));
    //int -> QString
    qDebug()<<QString::number(123);
    qDebug()<<str.setNum(6666666).size();
    qDebug()<<str;

    //QString-> int
    int i = str.toInt();
    qDebug()<<i;
    QString s1= "Abc";
    QString s2 = "aBc";
    qDebug()<<"With Caps:"<<s1.compare(s2);
    //默认 Qt::CaseSensitive
    qDebug()<<"Without Caps:"<<s1.compare(s2,Qt::CaseInsensitive);
    QString s3 = "bC";
    qDebug()<<"Include: "<<s1.contains(s3)<<
              s1.contains(s3,Qt::CaseInsensitive);
    s3.append("hahaha");//向前追加
    qDebug()<<s3;

    s3.swap(s2);//交换

    qDebug()<<s2<<s3;

    //qDebug()<<std::endl;


    qint64 time = QDateTime::currentMSecsSinceEpoch();
    qDebug()<<time-start;
    //设置随机数种子
    qsrand(time);
    // 1-10随机数
    int rand = qrand()%10+1;
    qDebug()<<rand;

    //获得一个基于当前时间和日期的对象
    QDateTime dt = QDateTime::currentDateTime();
    // 时间和日期格式化
    // 格式可参考手册或上网查询
    QString text = dt.toString("yyyy-MM-dd hh:mm:ss t");

    qDebug()<<text;
    connect(ui->calendarWidget,SIGNAL(currentPageChanged(int,int)),
            this,SLOT(pageSlot(int,int)));
    connect(ui->calendarWidget,SIGNAL(selectionChanged()),
            this,SLOT(selectionSlot()));

}

dialog5::~dialog5()
{
    delete ui;
}

void dialog5::pageSlot(int year, int mon){
    qDebug()<<"turned page:"<<year<<"Year "<<mon<<" Month";
}

void dialog5::selectionSlot(){
    // 获取当前日期
    QDate date = ui->calendarWidget->selectedDate();
    // 格式化
    qDebug()<<"Selected "<<date<<"Days";
}




