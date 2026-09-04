#ifndef DIALOG12_H
#define DIALOG12_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class dialog12;
}

class dialog12 : public QDialog
{
    Q_OBJECT

public:
    explicit dialog12(QWidget *parent = 0);
    ~dialog12();

private:
    Ui::dialog12 *ui;
    QTcpServer* server;
    QTcpSocket *socket = NULL; // 只保存最新的连接对象

    void printDateTime(); // 打印当前日期和时间

private slots:
    void newConnectionSlot(); // 新连接接入槽
    void disconnectedSlot();  // 连接断开槽
    void readReadSlot();      // 读取消息槽
};

#endif // DIALOG12_H
