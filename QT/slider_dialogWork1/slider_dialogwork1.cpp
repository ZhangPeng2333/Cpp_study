#include "slider_dialogwork1.h"
#include "ui_slider_dialogwork1.h"

int main_slider_value = 0;

slider_dialogWork1::slider_dialogWork1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::slider_dialogWork1)
{
    ui->setupUi(this);
    ui->cldbtn->setText("ChildBTN");
    ui->frdbtn->setText("FriendBTN");
    ui->horizontalSlider->move(300,300);
    ui->horizontalSlider->setFixedSize(300,50);
    connect(ui->cldbtn,SIGNAL(clicked()),
            this,SLOT(createChildSlot()));
    connect(ui->frdbtn,SIGNAL(clicked()),
            this,SLOT(createFriendSlot()));

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),
            this,SLOT(changeFandCSliderValue(int)));


}

slider_dialogWork1::~slider_dialogWork1()
{
    delete clddlg;
    delete frddlg;
    delete ui;
}

void slider_dialogWork1::createChildSlot(){

    if (clddlg) {
        clddlg->show();
        clddlg->raise();
        return;
    }
    clddlg = new QDialog(this);
    child_slider = new QSlider(Qt::Horizontal, clddlg);
    child_slider->setRange(0, 100);
    child_slider->setValue(0);
    child_slider->move(300,300);
    child_slider->setFixedSize(300,50);
    clddlg->resize(800,800);
    clddlg->show();
    connect(child_slider,SIGNAL(valueChanged(int)),
            this,SLOT(changeMainSliderValue(int)));
}

void slider_dialogWork1::createFriendSlot(){
    if(frddlg){
        frddlg->show();
        frddlg->raise();
        return;
    }
    frddlg = new QDialog;
    friend_slider = new QSlider(Qt::Horizontal, frddlg);
    friend_slider->setRange(0, 100);
    friend_slider->setValue(0);
    friend_slider->move(300,300);
    friend_slider->setFixedSize(300,50);
    frddlg->resize(800,800);
    frddlg->show();
}

void slider_dialogWork1::changeFandCSliderValue(int value){
    if (child_slider !=NULL) {
        child_slider->setValue(value);
    }
    if (friend_slider !=NULL) {
        friend_slider->setValue(value);
    }
    return;
}

void slider_dialogWork1::changeMainSliderValue(int value){
    ui->horizontalSlider->setValue(value);
}
