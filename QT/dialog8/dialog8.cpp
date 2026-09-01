#include "dialog8.h"
#include "ui_dialog8.h"
#include<QDebug>
#include<QMap>
#include<QString>

dialog8::dialog8(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog8)
{
    ui->setupUi(this);
    // 创建一个QMap对象
    QMap<QString,QString> map;
//添加数据
    map["姓名"] = "张三";
    //key  value
    map.insert("年龄","100岁");
    map["姓名"]="张三丰";
    //[]方式未知其是否已存在
    //取出前判断key存在
    if(map.contains("姓名")){
        qDebug()<<map["姓名"];// 取出
    }


    // 这种方式可以不判断元素在不在，如果元素不存在，会返回默认值
    qDebug()<<map.value("地址","默认值");
    qDebug()<<map.value("年龄","默认值");
    qDebug()<<map;

    int result = map.remove("姓名");
    qDebug()<<"删除结果："<<result;
    qDebug()<<map;
    map["身高"]= "1m";
    map["体重"]="100金";
    //STL
    for(QMap<QString,QString>::const_iterator it = map.begin();
        it != map.end();it++){
        qDebug()<<it.key()<<it.value();
    }
    qDebug()<<"--------------";

    // JAVA
    // only read QMapIterator
    // r and w   QMutableIterator
    QMapIterator<QString,QString> it(map);
    while(it.hasNext()){
        it.next();
        qDebug()<<it.key()<<it.value();
    }

}

dialog8::~dialog8()
{
    delete ui;
}
