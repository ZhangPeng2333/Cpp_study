#ifndef STUDENT_H
#define STUDENT_H

// 需要引入Qt的头文件
#include <QString>

class Student
{
public:
    Student(QString,int,QString);

    QString getName() const;
    void setName(const QString &value);

    int getAge() const;
    void setAge(int value);

    QString getMajor() const;
    void setMajor(const QString &value);

private:
    QString name;
    int age;
    QString major;
};

#endif // STUDENT_H
