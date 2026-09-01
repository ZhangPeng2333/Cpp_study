#include "dialog7.h"
#include "ui_dialog7.h"
#include<QDebug>

dialog7::dialog7(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog7)
{
    ui->setupUi(this);

    // 创建一个QList对象
    QList<Student> class22071;
    // 准备一些学生对象
    Student s1("张三",18,"物联网");
    Student s2("李四",19,"电子信息");
    Student s3("王五",20,"计算机");
    Student s4("赵六",21,"软件工程");
    Student s5("钱七",22,"网络工程");
    // 添加元素
    class22071.append(s1); // 向后追加
    class22071.push_back(s2); // 向后追加
    class22071.prepend(s3); // 向前追加
    class22071.push_front(s4); // 向前追加
    class22071 << s1 << s2 << s3; // 连续追加

    // 取出单个元素
    qDebug() << class22071[0].getName()
             << class22071.at(1).getName();

    // 插入元素
    // 参数1：插入的位置
    // 参数2：插入的元素
    class22071.insert(1,s5);

    // STL 迭代器
    for(QList<Student>::const_iterator iter = class22071.begin();
        iter != class22071.end();iter++)
    {
        Student s = *iter;
        qDebug() << s.getName() << s.getAge() << s.getMajor();
    }

    qDebug() << "------------------------";

    // Java迭代器
    // 只读：QListIterator
    // 读写：QMutableListIterator
    QListIterator<Student> iter(class22071);

    while(iter.hasNext()) // 判断迭代器指针后面还有没有元素
    {
        Student s = iter.next(); // 向后移动迭代器指针，并取出元素对象
        qDebug() << s.getName() << s.getAge() << s.getMajor();
    }

    QList<int> list;
    list << 34 << 56 << 123 << 34 << 56;
    list.removeAll(34); // 移除所有34
    list.removeFirst(); // 移除第一个元素
    list.removeLast(); // 移除最后一个元素

    list << 111 << 111 << 111;

    list.removeOne(111); // 移除第一个111
    list.removeAt(1); // 移除第二个元素

    // 修改元素
    // 参数1：修改的元素位置
    // 参数2：新元素值
    list.replace(0,666);

    qDebug() << list;
}

dialog7::~dialog7()
{
    delete ui;
}
