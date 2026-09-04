#ifndef DIALOG12_CLIENT_H
#define DIALOG12_CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTextStream>

namespace Ui {
class dialog12_client;
}

class dialog12_client : public QDialog
{
    Q_OBJECT

public:
    explicit dialog12_client(QWidget *parent = 0);
    ~dialog12_client();

private:
    Ui::dialog12_client *ui;
    QTcpSocket *client = NULL; // 客户端连接对象

private slots:
    // 连接按钮点击槽
    void btnConnClickedSlot();
    // 发送按钮点击槽
    void btnSendClickedSlot();
    // 连接成功槽
    void connectedSlot();
    // 连接断开/失败槽
    void disconnectedSlot();
    // 读取服务器消息槽
    void readyReadySlot();
};

#endif // DIALOG12_CLIENT_H
