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
    //计算
    int num = ui->spinNum->value();
    float price = ui->spinPrice->value();
    float total = num*price;
    ui->spinTotal->setValue(total);
}

void Widget::on_btnBin_clicked()
{
    //读取二进制数，以其他进制显示
    int val = ui->spinBin->value();
    qDebug() << val;
    ui->spinDec->setValue(val);
    ui->spinHex->setValue(val);
}


void Widget::on_btnDec_clicked()
{
    //读取十进制数，以其他进制显示
    int val = ui->spinDec->value();
    qDebug() << val;
    ui->spinBin->setValue(val);
    ui->spinHex->setValue(val);
}

void Widget::on_btnHex_clicked()
{
    //读取十六进制数，以其他进制显示
    int val = ui->spinHex->value();
    qDebug() << val;
    ui->spinBin->setValue(val);
    ui->spinDec->setValue(val);
}
