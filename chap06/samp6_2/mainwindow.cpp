#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwdialogsize.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(0,5,this);//数据模型
    theSelection = new QItemSelectionModel(theModel);//选择模式
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    setCentralWidget(ui->tableView); //

    //创建状态栏组件
    LabCellPos = new QLabel("当前单元格：",this);
    LabCellPos->setMinimumWidth(180);
    LabCellPos->setAlignment(Qt::AlignHCenter);

    LabCellText = new QLabel("单元格内容：",this);
    LabCellText->setMinimumWidth(200);


    ui->statusbar->addWidget(LabCellPos);
    ui->statusbar->addWidget(LabCellText);

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
        //这里说明一下，没有上面的 LabCellPos = new QLabel("当前单元格：",this); 和 LabCellText = new QLabel("单元格内容：",this);
        //这里在设置好行和列的情况，下点击确定按钮，后，会自动触发此槽函数，默认选择的是(0,0),就会因LabCellPos为空指针或未初始化而报错。
        //这个错误不好看到。
        LabCellPos->setText(QString::asprintf("当前单元格： %d行, %d列",current.row(),current.column()));
        QStandardItem *aItem = theModel->itemFromIndex(current);
        LabCellText->setText("单元格内容："+aItem->text());
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

