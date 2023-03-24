#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnCal_clicked()
{
    QString str = ui->editNum->text();//读取"数量"
    int num = str.toInt();
    str = ui->editPrice->text();//读取"单价"
    float price = str.toFloat();
    float total = num*price;
    //str = str.sprintf("%.2f",total);
    //qDebug() <<"--1--: " << str;
    str.sprintf("%.2f",total);
    qDebug() << "--2--: " << str;
    ui->editTotal->setText(str);
}

void Widget::on_btnDec_clicked()
{
    //读取十进制数，转换为其他进制
    QString str = ui->editDec->text();
    int val = str.toInt();//缺省为十进制
    //str = QString::number(val,16);//转换为十六进制的字符串
    str = str.setNum(val,16);//十六进制
    str= str.toUpper();
    ui->editHex->setText(str);

    str = str.setNum(val,2);//二进制
    //str = QString::number(val,16);
    ui->editBin->setText(str);
}

void Widget::on_btnBin_clicked()
{
    //读取二进制数，转换为其他进制
    QString str = ui->editBin->text();
    bool ok;
    int val = str.toInt(&ok,2);//以二进制数读入
    qDebug() << "ok = " << ok;
    qDebug() << "val = " << val;
    str = QString::number(val); //数字显示为十进制字符串
    ui->editDec->setText(str);

    //str = QString::number(val,16);//转换为十六进制的字符串
    str = str.setNum(val,16);//显示为十六进制
    str= str.toUpper();
    ui->editHex->setText(str);
}

void Widget::on_btnHex_clicked()
{
    //读取十六进制数，转换为其他进制
    QString str = ui->editHex->text();
    bool ok;
    qDebug() << "ok init = " << ok;
    int val = str.toInt(&ok,16);//以十六进制数读入
    qDebug() << "ok = " << ok;
    qDebug() << "val = " << val;
    str = QString::number(val);
    ui->editDec->setText(str);

    str = str.setNum(val,2);//二进制
    //str = QString::number(val,16);
    ui->editBin->setText(str);
    QString str1 = "a",str2 = "拐";
    QString str3 = str1;
    QString str4 = str1.append(str2);
    str3.prepend(str2);
    qDebug() << str1;
    qDebug() << str2;
    str1 = str1.toUpper();
    qDebug() << str1;
    qDebug() << str1.count();
    QString str5, str6 = "\0";
    qDebug() << str6.count();
    qDebug() << str6.isNull();
    qDebug() << str6.isEmpty();
}
