#include "mainwindow.h"
#include "ui_mainwindow.h"
/*
 * 注意书上说的水平分割布局再和下方显示信息的groupBox在主窗口工作区水平布局，要改为垂直布局。不是垂直分割布局
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::currentPath());//设置根目录
    ui->treeView->setModel(model);//设置数据模型
    ui->listView->setModel(model);//设置数据模型
    ui->tableView->setModel(model);//设置数据模型
    //信号与槽关联，tree单击时，其目录设置位listView和tableView的根节点
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->listView,SLOT(setRootIndex(QModelIndex)));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->tableView,SLOT(setRootIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->chkIsDir->setChecked(model->isDir(index));//判断节点是否为目录
    ui->LabPath->setText(model->filePath(index));//返回节点的目录名或带路径的文件名
    ui->LabType->setText(model->type(index));//返回描述节点类型的文字
    ui->LabFileName->setText(model->fileName(index));//返回去除路径的文件夹名称或文件名
    //Returns the size in bytes of index. If the file does not exist, 0 is returned.
    int sz = model->size(index)/1024;//如果节点是文件，size函数返回的单位是字节，除于1024得到的是KB，如果是文件夹，返回0
    if(sz<1024)
        //Returns a copy of this string with the lowest numbered place marker replaced by string a, i.e., %1, %2, ..., %99.
        ui->LabFileSize->setText(QString("%1 KB").arg(sz));
    else
        ui->LabFileSize->setText(QString::asprintf("%.1f MB",sz/1024.0));//再除1024得到的是MB
}




