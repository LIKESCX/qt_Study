#include "dialog.h"
#include "ui_dialog.h"
#include <QDir>
#include <QFileDialog>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnOpen_clicked()
{//选择单个文件
    QString curPath = QDir::currentPath();//获取应用程序当前目录
    QString dlgTitle="选择一个文件";
    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}

void Dialog::on_btnOpenMulti_clicked()
{//选择多个文件
    QString curPath = QDir::currentPath();//获取应用程序当前目录
    QString dlgTitle="选择一个文件";
    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
    QStringList fileList = QFileDialog::getOpenFileNames(this,dlgTitle,curPath,filter);
    for(int i=0;i<fileList.count();i++)
    {
        ui->plainTextEdit->appendPlainText(fileList.at(i));
    }
}


void Dialog::on_btnSelDir_clicked()
{//选择文件夹
    QString curPath = QCoreApplication::applicationDirPath();//返回可执行文件所在的目录
    QString dlgTitle="选择一个目录";
    QString selectedDir = QFileDialog::getExistingDirectory(this,dlgTitle,curPath,QFileDialog::ShowDirsOnly);//返回值是选择的目录名称的字符串
    if(!selectedDir.isEmpty())
        ui->plainTextEdit->appendPlainText(selectedDir);
}


void Dialog::on_btnSave_clicked()
{//保存文件
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle="保存文件";
    QString filter="文件(*.h);;C++文件(*.cpp);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if(!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}

