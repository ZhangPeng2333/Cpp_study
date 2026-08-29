#include "dialog4.h"
#include "ui_dialog4.h"

dialog4::dialog4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dialog4)
{
    ui->setupUi(this);
    connect(ui->dial,SIGNAL(valueChanged(int)),this,SLOT(mySlot(int)));

}

dialog4::~dialog4()
{
    delete ui;
}

void dialog4::mySlot(int value){
    ui->horizontalScrollBar->setValue(value);
    ui->horizontalSlider->setValue(value);
    ui->progressBar->setValue(value);
    ui->spinBox->setValue(value);
    ui->verticalScrollBar->setValue(value);
    ui->verticalSlider->setValue(value);
}
