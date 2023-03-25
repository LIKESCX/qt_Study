#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
     * 将ScrollArea组件设置为主窗口工作区的中心组件后，
     * DockWidget与ScrollArea之间自动出现分割条，可以分割两个组件的大小
     */
    setCentralWidget(ui->scrollArea);
    initTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initTree()
{//初始化目录树
    QString dataStr = "";   //Item 的Data 存储的string
    ui->treeFiles->clear();
    QIcon icon;
    icon.addFile(":/images/icons/15.ico");

    QTreeWidgetItem* item = new QTreeWidgetItem(MainWindow::itTopItem);
    item->setIcon(MainWindow::colItem,icon);  //第1列的图标
    item->setText(MainWindow::colItem,"图片文件"); //第1列的文字
    item->setText(MainWindow::colItemType,"type=itTopItem"); //第2列
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsTristate);
    item->setCheckState(colItem,Qt::Checked);

    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dataStr));
    ui->treeFiles->addTopLevelItem(item);//添加顶层节点
}
