#include "dialog12_client.h"
#include "ui_dialog12_client.h"
#include <QHostAddress>

dialog12_client::dialog12_client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog12_client)
{
    ui->setupUi(this);

    // 设置窗口置顶
    setWindowFlags(Qt::WindowStaysOnTopHint);
    // 设置窗口标题
    setWindowTitle("客户端");

    // 连接按钮信号槽
    connect(ui->pushButton, SIGNAL(clicked()),
            this, SLOT(btnConnClickedSlot()));
    // 发送按钮信号槽
    connect(ui->pushButton_2, SIGNAL(clicked()),
            this, SLOT(btnSendClickedSlot()));

    // 初始状态：发送按钮禁用
    ui->pushButton_2->setEnabled(false);
}

dialog12_client::~dialog12_client()
{
    // 如果还有连接，关闭并释放
    if(client != NULL && client->isOpen())
    {
        // 断开信号槽
        disconnect(client, SIGNAL(disconnected()),
                   this, SLOT(disconnectedSlot()));
        client->close();
    }
    delete ui;
}

// 连接服务器按钮
void dialog12_client::btnConnClickedSlot()
{
    // 获取用户输入的IP和端口
    QString ip = ui->lineEdit->text();
    int port = ui->spinBox->value();

    // 创建客户端套接字
    client = new QTcpSocket(this);

    // 绑定连接成功、断开信号槽
    connect(client, SIGNAL(connected()),
            this, SLOT(connectedSlot()));
    connect(client, SIGNAL(disconnected()),
            this, SLOT(disconnectedSlot()));

    // 发起连接
    client->connectToHost(ip, port);
}

// 发送消息按钮
void dialog12_client::btnSendClickedSlot()
{
    // 获取昵称
    QString name = ui->lineEdit_2->text();
    if(name == "")
    {
        QMessageBox::warning(this, "提示", "请输入昵称！");
        return;
    }

    // 获取消息
    QString msg = ui->lineEdit_3->text();
    if(msg == "")
    {
        QMessageBox::warning(this, "提示", "请输入要发送的消息！");
        return;
    }

    // 创建文本流发送
    QTextStream ts(client);
    name.append("：").append(msg);
    ts << name;

    // 清空消息输入框
    ui->lineEdit_3->clear();
}

// 连接成功回调
void dialog12_client::connectedSlot()
{
    // 绑定读消息信号槽
    connect(client, SIGNAL(readyRead()),
            this, SLOT(readyReadySlot()));

    // 屏蔽连接按钮，修改文字
    ui->pushButton->setEnabled(false);
    ui->pushButton->setText("已连接");
    // 开启发送按钮
    ui->pushButton_2->setEnabled(true);
}

// 连接断开/失败回调
void dialog12_client::disconnectedSlot()
{
    // 断开读消息信号槽
    disconnect(client, SIGNAL(readyRead()),
               this, SLOT(readyReadySlot()));

    // 恢复连接按钮
    ui->pushButton->setEnabled(true);
    ui->pushButton->setText("Connect");
    // 屏蔽发送按钮
    ui->pushButton_2->setEnabled(false);

    QMessageBox::warning(this, "提示", "连接已断开！");
}

// 读取服务器消息
void dialog12_client::readyReadySlot()
{
    QTextStream ts(client);
    QString text = ts.readAll();
    QMessageBox::information(this, "接收到服务器的消息", text);
}
