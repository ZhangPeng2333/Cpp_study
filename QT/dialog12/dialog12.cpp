#include "dialog12.h"
#include "ui_dialog12.h"
#include <QMessageBox>
#include <QDateTime>
#include <QTextStream>
#include <QHostAddress>

dialog12::dialog12(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog12)
{
    ui->setupUi(this);

    // 设置窗口置顶
    setWindowFlags(Qt::WindowStaysOnTopHint);
    // 设置窗口标题
    setWindowTitle("Server");

    // 创建服务器对象
    server = new QTcpServer(this);
    // 在8887端口开启监听
    bool result = server->listen(QHostAddress::Any, 8887);
    if (!result) {
        QMessageBox::critical(this, "ERROR", "Listen Err");
        return;
    }

    printDateTime();
    ui->textBrowser->append("Listen Start--Port 8887");

    // 绑定新连接信号槽
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnectionSlot()));
}

dialog12::~dialog12()
{
    // 关闭监听服务
    if (server->isListening())
        server->close();
    delete ui;
}

void dialog12::printDateTime()
{
    QString dt = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->textBrowser->append(dt);
}

void dialog12::newConnectionSlot()
{
    // 踢掉之前的旧连接
    if (socket != NULL && socket->isOpen())
    {
        socket->close();
        disconnect(socket, SIGNAL(disconnected()),
                   this, SLOT(disconnectedSlot()));
        disconnect(socket, SIGNAL(readyRead()),
                   this, SLOT(readReadSlot()));
    }

    // 获取最新连接
    socket = server->nextPendingConnection();

    // 向客户端发送连接成功问候
    QTextStream ts(socket);
    QString text = QDateTime::currentDateTime().toString("hh:mm:ss").prepend("已经接受了你的连接，连接时间：");
    ts << text;

    // 绑定断连、读消息信号槽
    connect(socket, SIGNAL(disconnected()),
            this, SLOT(disconnectedSlot()));
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(readReadSlot()));

    // 显示客户端IP与端口
    QString ip = socket->peerAddress().toString();
    quint16 port = socket->peerPort();
    QString portText = QString::number(port);
    ip.prepend("新连接来了！").append(":").append(portText);

    printDateTime();
    ui->textBrowser->append(ip);
}

void dialog12::disconnectedSlot()
{
    // 显示断开连接的客户端信息
    QString ip = socket->peerAddress().toString();
    quint16 port = socket->peerPort();
    QString portText = QString::number(port);
    ip.prepend("连接已断开！").append(":").append(portText);

    printDateTime();
    ui->textBrowser->append(ip);
}

void dialog12::readReadSlot()
{
    // 读取客户端发来的全部文本
    QTextStream ts(socket);
    QString text = ts.readAll();

    printDateTime();
    ui->textBrowser->append(text);
}
