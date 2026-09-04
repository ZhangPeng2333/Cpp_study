#ifndef DIALOG11_H
#define DIALOG11_H

#include <QDialog>
#include<QButtonGroup>
#include<QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery> //数据库操作

namespace Ui {
class dialog11;
}

class dialog11 : public QDialog
{
    Q_OBJECT

public:
    explicit dialog11(QWidget *parent = 0);
    ~dialog11();

private:
    Ui::dialog11 *ui;
    QButtonGroup* group;
    QSqlDatabase db; // 数据库连接对象

    // 连接数据库
    void connectDB();
    // 创建表
    void createTable();
    // 插入数据
    void insertData();
    // 删除数据
    void deleteData();
    // 修改数据
    void updateData();
    // 关键字查询
    void likeSelectData();
    // 查询所有数据
    void allSelectData();
    // 判断某个记录是否存在
    bool hasData(int id);

private slots:
    // 按钮点击统一槽函数
    void btnsClickedSlot(int);
};

#endif // DIALOG11_H
