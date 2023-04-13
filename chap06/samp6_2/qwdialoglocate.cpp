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
{//窗口关闭 event
    MainWindow *parWind = (MainWindow*)parentWidget();//获取父窗口指针
    parWind->setActLocateEnable(true);//使能actTab_Locate
    parWind->setDlgLocateNull();//将窗口指针置为NULL
}


void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{
    ui->spinBoxRow->setMaximum(0);
    ui->spinBoxRow->setMaximum(rowCount);

    ui->spinBoxColumn->setMinimum(0);
    ui->spinBoxColumn->setMaximum(colCount);
}

void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{//设置SpinBox组件的数值
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}

void QWDialogLocate::on_btnSetText_clicked()
{//定位到单元格，并设置字符串
    int row = ui->spinBoxRow->value();
    int col = ui->spinBoxColumn->value();
    MainWindow *parWind = (MainWindow*)parentWidget();////获取父窗口指针
    QString text = ui->edtCaption->text();
    parWind->setACellText(row,col,text);//调用主窗口函数
    if(ui->chkBoxRow->isChecked()) //行增
        ui->spinBoxRow->setValue(1+ui->spinBoxRow->value());
    if(ui->chkBoxColumn->isChecked())//列增
        ui->spinBoxColumn->setValue(1+ui->spinBoxColumn->value());

}

