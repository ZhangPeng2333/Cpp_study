#include "dialog2.h"
#include "ui_dialog2.h"

dialog2::dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog2)
{
    ui->setupUi(this);
    QPixmap map(":/new/img/img.jpg");
    QSize size(300,300);
    map = map.scaled(size,Qt::KeepAspectRatioByExpanding);
    ui->label->setPixmap(map);

    QColor color(255,0,128);
    QPalette pa;
    pa.setColor(QPalette::WindowText,color);

    ui->label_2->setPalette(pa);
}

dialog2::~dialog2()
{
    delete ui;
}
