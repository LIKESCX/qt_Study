#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"
#include <QMessageBox>
#include "mainwindow.h"
QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{
    QMessageBox::information(this,"提示","单元格定位与文字设置被删除");
    delete ui;
}

void QWDialogLocate::closeEvent(QCloseEvent *event)
{//窗口关闭事件，发射信号使actTab_Locate能用
    emit changeActionEnable(true);
}

void QWDialogLocate::showEvent(QShowEvent *event)
{//窗口显示事件，发射信号使actTab_Locate不能用
    emit changeActionEnable(false);
}

void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{//响应主窗口信号，更新spinBox的值
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}



void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{
    ui->spinBoxRow->setMaximum(0);
    ui->spinBoxRow->setMaximum(rowCount);

    ui->spinBoxColumn->setMinimum(0);
    ui->spinBoxColumn->setMaximum(colCount);
}

void QWDialogLocate::on_btnSetText_clicked()
{//发射信号，定位到单元格，并设置字符串
    int row = ui->spinBoxRow->value();//行号
    int col = ui->spinBoxColumn->value();//列号
    QString text = ui->edtCaption->text();//文字
//  MainWindow *parWind = (MainWindow*)parentWidget();//获取父窗口指针
//  parWind->setACellText(row,col,text);//调用主窗口函数
    emit changeCellText(row,col,text);//发射信号
    if(ui->chkBoxRow->isChecked()) //行增
        ui->spinBoxRow->setValue(1+ui->spinBoxRow->value());
    if(ui->chkBoxColumn->isChecked())//列增
        ui->spinBoxColumn->setValue(1+ui->spinBoxColumn->value());

}

