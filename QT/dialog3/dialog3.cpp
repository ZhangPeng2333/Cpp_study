#include "dialog3.h"
#include "ui_dialog3.h"
#include<string>
#include<QtDebug>

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    time = 0;
    //setGeometry(1000,600,300,300);
    ui->setupUi(this);
    ui->btn->setText("I'm a button");
    btn1 = new QPushButton("I'm a button1",this);
    btn1->move(100,100);
    btn1->resize(100,100);
    connect(btn1,SIGNAL(clicked()),this,SLOT(mySlote()));

    group = new QButtonGroup(this);

    group->addButton(ui->checkBox,1);
    group->addButton(ui->checkBox_2,2);
    group->addButton(ui->checkBox_3,3);

    connect(group,SIGNAL(buttonToggled(int,bool)),this,SLOT(mySlot1(int,bool)));

}

Dialog3::~Dialog3()
{
    delete ui;
    delete btn1;
}

void Dialog3::mySlote(){
    btn1->move(btn1->x()+15,btn1->y()+15);
    time++;
    char str[20];
    snprintf(str, sizeof(str), "%d", time);
    btn1->setText(str);
}

void Dialog3::mySlot1(int id,bool checked){
    switch (id) {
    case 1:
        qDebug()<<"1 "<<checked;break;
    case 2:
        qDebug()<<"2 "<<checked;break;
    case 3:
        qDebug()<<"3 "<<checked;

        break;
    default:
        break;
    }
}
