#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(0,0,this);//数据模型
    theSelection = new QItemSelectionModel(theModel);//选择模式
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{//选择单元格变化时的响应
    if(current.isValid())
    {
//        LabCellPos->text();
    }

}
void MainWindow::on_setRowsAndColsAction_triggered()
{

}

