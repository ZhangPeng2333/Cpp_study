#include "dialog_fileopen.h"
#include "ui_dialog_fileopen.h"

#include<QFileInfo>
#include<QString>
#include<QDateTime>

dialog_fileopen::dialog_fileopen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_fileopen)
{
    ui->setupUi(this);
    group = new QButtonGroup(this);
    group->addButton(ui->pushButton_open,1);
    group->addButton(ui->pushButton_save,2);
    group->addButton(ui->pushButton_copy,3);

    ui->pushButton_copy->setText("开始");
    ui->pushButton_open->setText("打开文件");
    ui->pushButton_save->setText("保存至");

    ui->progressBar->setValue(0);

    connect(group,SIGNAL(buttonClicked(int)),
            this,SLOT(buttonClickedSlot(int)));

    //创造线程
    workThread = new mythread(this);

    connect(workThread,&mythread::progressUpdated,this,
            &dialog_fileopen::onCopyProgress);
    connect(workThread,&mythread::copyFinished,this,
            &dialog_fileopen::onCopyFinished);
    // 线程结束后自动销毁
    //connect(workThread,&mythread::finished,workThread,
    //        &QObject::deleteLater);

}

void dialog_fileopen::getOpenFilePath(){
    // 弹窗并选择要打开文件
    ui->textBrowser_open->setText("");
    QString path = QFileDialog::getOpenFileName(this,"打开文件","./",
                                                 "所有文件;;Qt(*.pro *.user *.h *.cpp *.ui)");
    if(path == "")
    {
        QMessageBox::warning(this,"提示","请选择要打开的文件！");
        return;
    }
    ui->textBrowser_open->append(path);
    readPath = path;

    QFileInfo info(path);
    QString text = "文件是否存在：";
    if(info.exists()){
        text.append("是");
    }
    else{
        text.append("否");
    }
    ui->textBrowser_open->append(text);

    text = info.created().toString("yyyy-MM-dd hh:mm:ss");
    text.prepend("创建日期：");

    ui->textBrowser_open->append(text);
    if(info.isReadable()){
        ui->textBrowser_open->append("可读");

    }else{
        ui->textBrowser_open->append("不可读");
    }
    text = "文件大小：";
    qint64 size = info.size();
    QString sizeText = QString::number(size);
    text.append(sizeText).append("字节");
    ui->textBrowser_open->append(text);


}

void dialog_fileopen::getSaveFilePath(){
    // 弹窗并选择要打开文件
    ui->textBrowser_save->setText("");
    QString path = QFileDialog::getSaveFileName(this,"打开文件","./",
                                                "所有类型;;Qt(*.pro *.user *.h *.cpp *.ui)");
    if(path == "")
    {
        QMessageBox::warning(this,"提示","请选择要打开的文件！");
        return;
    }
    ui->textBrowser_save->append(path);
    writePath = path;

    QFileInfo info(path);
    QString text = "文件是否存在：";
    if(info.exists()){
        text.append("是");
    }
    else{
        text.append("否");
    }
    ui->textBrowser_save->append(text);

    text = info.created().toString("yyyy-MM-dd hh:mm:ss");
    text.prepend("创建日期：");

    ui->textBrowser_save->append(text);
    if(info.isReadable()){
        ui->textBrowser_save->append("可读");

    }else{
        ui->textBrowser_save->append("不可读");
    }
    text = "文件大小：";
    qint64 size = info.size();
    QString sizeText = QString::number(size);
    text.append(sizeText).append("字节");
    ui->textBrowser_save->append(text);


}

void dialog_fileopen::copy(){
    if (readPath.isEmpty() || writePath.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择源文件和目标路径！");
        return;
    }
    if (!QFile::exists(readPath)) {
        QMessageBox::warning(this, "错误", "源文件不存在！");
        return;
    }
    if (QFile::exists(writePath)) {
        int ret = QMessageBox::question(this, "确认覆盖", "目标文件已存在，是否覆盖？",
                                        QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No)
            return;
    }
    // 禁用copy open save button
    ui->pushButton_copy->setEnabled(false);
    ui->pushButton_open->setEnabled(false);
    ui->pushButton_save->setEnabled(false);
    ui->progressBar->setValue(0);

    workThread->setPaths(readPath, writePath);
    workThread->start();
}

void dialog_fileopen::onCopyProgress(int percent){
    ui->progressBar->setValue(percent);
}

void dialog_fileopen::onCopyFinished(bool success, QString errorMsg){
    if (success) {
        QMessageBox::information(this, "完成", "文件拷贝成功！");
        ui->progressBar->setValue(100);
    } else {
        QMessageBox::critical(this, "错误", errorMsg);
        ui->progressBar->setValue(0);
    }
    // 恢复按钮
    ui->pushButton_copy->setEnabled(true);
    ui->pushButton_open->setEnabled(true);
    ui->pushButton_save->setEnabled(true);
}

void dialog_fileopen::buttonClickedSlot(int id){
    if(id == 1){
        getOpenFilePath();
    }
    else if(id == 2){
        getSaveFilePath();
    }
    else if(id == 3){
        copy();
    }
}

dialog_fileopen::~dialog_fileopen()
{
    if (workThread->isRunning()) {
        workThread->quit();
        workThread->wait();
    }
    delete ui;
}
