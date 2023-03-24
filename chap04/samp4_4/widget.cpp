#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //ui->groupBox->setStyleSheet(QObject::tr("#groupBox{border: none;}"));
    //this->setLayout(ui->horizontalLayout);
    ui->groupBox->setFlat(true);
    ui->groupBox_2->setFlat(true);
    ui->groupBox_3->setFlat(true);
    ui->groupBox_4->setFlat(true);
    ui->groupBox_5->setFlat(true);
    ui->groupBox_6->setFlat(true);
    ui->groupBox_7->setFlat(true);
    ui->groupBox_8->setFlat(true);
    connect(ui->SliderBlue,SIGNAL(valueChanged(int)),
            this,SLOT(on_SliderRed_valueChanged(int)));
    connect(ui->SliderGreen,SIGNAL(valueChanged(int)),
            this,SLOT(on_SliderRed_valueChanged(int)));
    connect(ui->SliderAlpha,SIGNAL(valueChanged(int)),
            this,SLOT(on_SliderRed_valueChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_SliderRed_valueChanged(int value)
{
    //拖动Red、Green、Blue 颜色滑动条配色，然后设置为旁边的textEdit的底色
    Q_UNUSED(value);
    QColor color;
    int R = ui->SliderRed->value();
    int G = ui->SliderGreen->value();
    int B = ui->SliderBlue->value();
    int alpha = ui->SliderAlpha->value();
    //qDebug() << R <<" "<< G <<" "<< B <<" "<< alpha;
    color.setRgb(R,G,B,alpha);//使用QColor的setRgb()函数获得颜色
    QPalette pal = ui->textEdit->palette();//获取调色板
    pal.setColor(QPalette::Base, color);//设置底色
    ui->textEdit->setPalette(pal);
}

//设置 移动水平Slider的滑块时，ScrollBar和ProgressBar都跟着动态变化。
void Widget::on_horizontalSlider_valueChanged(int value)
{
    ui->horizontalScrollBar->setValue(value);
    ui->progressBar->setValue(value);
}
//LCD值显示
void Widget::on_dial_valueChanged(int value)
{   //设置LCD的显示值等于Dial的值
    ui->LCDDisplay->display(value);
}

void Widget::on_radioBtnDec_clicked()
{   //设置LCD显示十进制数
    ui->LCDDisplay->setDigitCount(3);//设置位数（包括小数点）
    ui->LCDDisplay->setDecMode();
}

void Widget::on_radioBtnBin_clicked()
{   //设置LCD显示二进制
    ui->LCDDisplay->setDigitCount(8);
    ui->LCDDisplay->setBinMode();
}

void Widget::on_radioBtnOct_clicked()
{   //设置LCD显示八进制
    ui->LCDDisplay->setDigitCount(4);
    ui->LCDDisplay->setOctMode();
}

void Widget::on_radioBtnHex_clicked()
{  //设置LCD显示十六进制
   ui->LCDDisplay->setDigitCount(3);
   ui->LCDDisplay->setHexMode();

}


