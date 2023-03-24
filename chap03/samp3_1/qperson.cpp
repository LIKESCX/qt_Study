#include "qperson.h"

//构造函数
QPerson::QPerson(QString fName, QObject *parent) : QObject(parent)
{
    m_name = fName;
}

//返回 age
int QPerson::age()
{
    return m_age;
}

//设置 age
void QPerson::setAge(int value)
{
    m_age = value;
    emit ageChanged(m_age);//发射信号
}

void QPerson::incAge()
{
    m_age++;
    emit ageChanged(m_age);//发射信号
}


