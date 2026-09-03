#ifndef DIALOG_FILEOPEN_H
#define DIALOG_FILEOPEN_H

#include <QDialog>
#include<QButtonGroup>
#include<QFileDialog>
#include<QMessageBox>
#include <QString>
#include<mythread.h>

namespace Ui {
class dialog_fileopen;
}

class dialog_fileopen : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_fileopen(QWidget *parent = 0);
    ~dialog_fileopen();

private:
    Ui::dialog_fileopen *ui;
    QButtonGroup *group;
    // 获取要打开的文件路径
    void getOpenFilePath();
    // 获取要保存的文件路径
    void getSaveFilePath();

    void copy();
    QString readPath;
    QString writePath;

    mythread* workThread;
private slots:
    // 按钮组点击发射的槽函数
    void buttonClickedSlot(int);

    // 进度
    void onCopyProgress(int percent);
    // 结束拷贝
    void onCopyFinished(bool success, QString errorMsg);

};

#endif // DIALOG_FILEOPEN_H
