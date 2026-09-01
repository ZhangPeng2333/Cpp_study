
#include "student.h"

Student::Student(QString name,int age,QString major)
{
    this->name = name;
    this->age = age;
    this->major = major;
}

QString Student::getName() const
{
    return name;
}

void Student::setName(const QString &value)
{
    name = value;
}

int Student::getAge() const
{
    return age;
}

void Student::setAge(int value)
{
    age = value;
}

QString Student::getMajor() const
{
    return major;
}

void Student::setMajor(const QString &value)
{
    major = value;
}
