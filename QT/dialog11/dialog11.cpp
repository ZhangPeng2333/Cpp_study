#include "dialog11.h"
#include "ui_dialog11.h"

dialog11::dialog11(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog11)
{
    ui->setupUi(this);

    // 按钮分组管理，绑定ID
    group = new QButtonGroup(this);
    group->addButton(ui->pushButton_insert, 1);
    group->addButton(ui->pushButton_delete, 2);
    group->addButton(ui->pushButton_updata, 3);
    group->addButton(ui->pushButton_select, 4);
    // 连接按钮点击信号与槽
    connect(group, SIGNAL(buttonClicked(int)),
            this, SLOT(btnsClickedSlot(int)));

    // 启动时连接数据库
    connectDB();
}

dialog11::~dialog11()
{
    // 关闭数据库
    if(db.isOpen())
    {
        db.close();
    }
    delete ui;
}

// 按钮点击分发槽函数
void dialog11::btnsClickedSlot(int id)
{
    if(id == 1)
    {
        insertData();
    }
    else if(id == 2)
    {
        deleteData();
    }
    else if(id == 3)
    {
        updateData();
    }
    else if(id == 4)
    {
        likeSelectData();
    }
}

// 连接SQLite数据库
void dialog11::connectDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("country management.db");

    if(db.open())
    {
        qDebug() << "数据库连接打开成功!";
        createTable(); // 建表
        allSelectData(); // 初始化查询全部数据
    }
    else
    {
        QSqlError info = db.lastError();
        QString text = info.text();
        text.prepend("数据库连接错误！");
        QMessageBox::critical(this, "错误", text);
    }
}

// 创建国家表
void dialog11::createTable()
{
    QSqlQuery sq;
    QString sql = "CREATE TABLE country(id INTEGER PRIMARY KEY,name TEXT,continent TEXT,power INTEGER);";

    if(sq.exec(sql))
    {
        qDebug() << "建表成功!";
    }
    else
    {
        QString text = sq.lastError().text();
        text.prepend("建表失败!");
        qDebug() << text;
    }
}

// 插入数据
void dialog11::insertData()
{
    QString name = ui->lineEdit->text();
    if(name == "")
    {
        QMessageBox::warning(this, "提示", "请输入国家名称！");
        return;
    }

    int id = ui->spinBox->value();
    QString continent = ui->comboBox->currentText();
    int power = ui->horizontalSlider->value();

    QSqlQuery sq;
    QString sql = "INSERT INTO country VALUES(?,?,?,?);";
    sq.prepare(sql);

    // 按顺序绑定占位符
    sq.addBindValue(id);
    sq.addBindValue(name);
    sq.addBindValue(continent);
    sq.addBindValue(power);

    if(sq.exec())
    {
        qDebug() << "插入成功！";
        allSelectData();
    }
    else
    {
        QString text = sq.lastError().text();
        text.prepend("插入失败!");
        QMessageBox::warning(this, "提示", text);
    }
}

// 删除数据
void dialog11::deleteData()
{
    int value = ui->spinBox->value();
    if(!hasData(value))
    {
        QMessageBox::information(this, "提示", "您要删除的数据不存在！");
        return;
    }

    QSqlQuery sq;
    QString sql = "DELETE FROM country WHERE id=:id";
    sq.prepare(sql);
    sq.bindValue(":id", value);

    if(sq.exec())
    {
        qDebug() << "删除操作成功！";
        allSelectData();
    }
    else
    {
        QString text = sq.lastError().text();
        text.prepend("删除操作失败!");
        QMessageBox::warning(this, "提示", text);
    }
}

// 更新数据
void dialog11::updateData()
{
    int id = ui->spinBox->value();
    if(!hasData(id))
    {
        QMessageBox::information(this, "提示", "您要更新的数据不存在！");
        return;
    }

    QString name = ui->lineEdit->text();
    if(name == "")
    {
        QMessageBox::warning(this, "提示", "请输入国家名称！");
        return;
    }

    QString continent = ui->comboBox->currentText();
    int power = ui->horizontalSlider->value();

    QSqlQuery sq;
    QString sql = "UPDATE country SET name=?,continent=?,power=? WHERE id=?";
    sq.prepare(sql);

    sq.addBindValue(name);
    sq.addBindValue(continent);
    sq.addBindValue(power);
    sq.addBindValue(id);

    if(sq.exec())
    {
        qDebug() << "更新操作成功！";
        allSelectData();
    }
    else
    {
        QString text = sq.lastError().text();
        text.prepend("更新操作失败!");
        QMessageBox::warning(this, "提示", text);
    }
}

// 模糊查询
void dialog11::likeSelectData()
{
    QString name = ui->lineEdit->text();
    if(name == "")
    {
        QMessageBox::warning(this, "提示", "请输入国家名称！");
        return;
    }

    ui->textBrowser->clear();
    QSqlQuery sq;
    QString sql = "SELECT * FROM country WHERE name LIKE ?";
    sq.prepare(sql);

    // 绑定通配符
    sq.addBindValue(name.append("%").prepend("%"));

    if(sq.exec())
    {
        qDebug() << "查询成功!";
        while(sq.next())
        {
            QString id = sq.value(0).toString();
            QString name = sq.value(1).toString();
            QString continent = sq.value("continent").toString();
            QString power = sq.value("power").toString();

            QString line = id + " " + name + " " + continent + " " + power;
            ui->textBrowser->append(line);
        }
    }
    else
    {
        QString text = sq.lastError().text();
        text.prepend("查询操作失败!");
        QMessageBox::warning(this, "提示", text);
    }
}

// 查询全部数据
void dialog11::allSelectData()
{
    ui->textBrowser->clear();
    QSqlQuery sq;
    QString sql = "SELECT * FROM country";

    if(sq.exec(sql))
    {
        qDebug() << "查询成功!";
        while(sq.next())
        {
            QString id = sq.value(0).toString();
            QString name = sq.value(1).toString();
            QString continent = sq.value("continent").toString();
            QString power = sq.value("power").toString();

            QString line = id + " " + name + " " + continent + " " + power;
            ui->textBrowser->append(line);
        }
    }
    else
    {
        QString text = sq.lastError().text();
        text.prepend("查询操作失败!");
        QMessageBox::warning(this, "提示", text);
    }
}

// 判断指定ID的数据是否存在
bool dialog11::hasData(int id)
{
    QSqlQuery sq;
    QString idText = QString::number(id);
    QString sql = "SELECT * FROM country WHERE id=" + idText;

    if(sq.exec(sql))
    {
        return sq.next();
    }
    else
    {
        QString text = sq.lastError().text();
        text.prepend("查询操作失败!");
        QMessageBox::warning(this, "提示", text);
        return false;
    }
}
