#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwdialogsize.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(0,6,this);//数据模型
    theSelection = new QItemSelectionModel(theModel);//选择模式
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{//选择单元格变化时的响应
    Q_UNUSED(previous)
    if(current.isValid())
    {
        LabCellPos->setText(QString::asprintf("当前单元格行号: %d, 列号: %d",current.row(),current.column()));
        QStandardItem *aItem = theModel->itemFromIndex(current);
        LabCellText->setText("当前单元格内容："+aItem->text());
    }

}

void MainWindow::on_actTab_SetSize_triggered()
{//模态对话框，动态创建，用过后删除
    QWDialogSize *dlgTableSize = new QWDialogSize(this);
    Qt::WindowFlags flags = dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dlgTableSize->setRowColumn(theModel->rowCount(),theModel->columnCount());
    int ret = dlgTableSize->exec();//以模态方式显示对话框
    if(ret==QDialog::Accepted)
    {//OK按钮被按下，获取对话框上的输入，设置行数和列数
        int cols = dlgTableSize->columnCount();
        theModel->setColumnCount(cols);
        int rows = dlgTableSize->rowCount();
        theModel->setRowCount(rows);
    }
    delete dlgTableSize;//手动释放内存
}


void MainWindow::on_actTab_SetHeader_triggered()
{//一次创建，多次调用，对话框关闭时只是隐藏
    if(dlgSetHeaders == nullptr)
        dlgSetHeaders = new QWDialogHeaders(this);
    if(dlgSetHeaders->headerList().count() != theModel->columnCount())
    {//如果表头列数变化，重新初始化（指的是初始化对话框里的listview的内容）
        QStringList strList;
        for (int i=0;i<theModel->columnCount();i++)//获取现有的表头标题
            strList.append(theModel->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
        dlgSetHeaders->setHeaderList(strList);//对话框初始化显示
    }

    int ret = dlgSetHeaders->exec();//以模态方式显示对话框
    if(ret==QDialog::Accepted)//OK 键被按下
    {
        QStringList strList = dlgSetHeaders->headerList();
        theModel->setHorizontalHeaderLabels(strList);//设置模型的表头标题
    }
}

