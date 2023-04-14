#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwdialogsize.h"
#include <QMessageBox>
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

void MainWindow::setACellText(int row, int column, QString &text)
{
    //定位到单元格，并设置字符串
    QModelIndex index = theModel->index(row,column);//获取指定单元格的模型索引
    theSelection->clearSelection();//重置选择区域
    theSelection->setCurrentIndex(index,QItemSelectionModel::Select);
    theModel->setData(index,text,Qt::DisplayRole);//设置单元格字符串
}

void MainWindow::setActLocateEnable(bool enable)
{
    //设置actTab_Locate的enable属性
    ui->actTab_Locate->setEnabled(enable);
}

//void MainWindow::setDlgLocateNull()
//{
//    dlgLocate = nullptr;
//}

//询问窗口是否退出,当 主窗口被关闭时，都会主动调此函数，进行提示，来最终确认
void MainWindow::closeEvent(QCloseEvent *event)
{//窗口关闭时询问是否退出，加下面的这个对话框，会导致一个问题，当定位 单元格对话框在打开的情况下，点击关闭主窗口，就会把确认的对话框显示到单元格对话框下面。而且还拖不动。导致无法操作了。
//    QMessageBox::StandardButton result = QMessageBox::information(this,"确认","确定要退出本程序吗？",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,QMessageBox::No);//最后一个参数 是默认选中的按钮，会在此按钮四周显示高亮。
//    if(result==QMessageBox::Yes)
//        event->accept();
//    else
//        event->ignore();
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
        dlgSetHeaders = new QWDialogHeaders(this);//这里传递this的目的是，自己手动没删除的话，会在MainWindow窗口销毁时，自动销毁dlgSetHeaders
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


void MainWindow::on_actTab_Locate_triggered()
{//创建StayOnTop的对话框，对话框关闭时自动删除
    QWDialogLocate *dlgLocate = new QWDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);//对话框关闭时 ，自动删除,作用相当于 delete ,可再对应的析构函数中添加提示，看是否调用了。
    Qt::WindowFlags flags = dlgLocate->windowFlags();//获取已有flags
    dlgLocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    dlgLocate->setSpinRange(theModel->rowCount(),theModel->columnCount());
    QModelIndex curIndex = theSelection->currentIndex();
    if(curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(),curIndex.column());
    //对话框发射信号，设置单元格文字
    connect(dlgLocate,SIGNAL(changeCellText(int,int,QString&)),
            this,SLOT(setACellText(int ,int, QString&)));

    //对话框发射信号，设置actTab_Locate的属性
    connect(dlgLocate,SIGNAL(changeActionEnable(bool)),
            this,SLOT(setActLocateEnable(bool)));

    //主窗口发射信号，修改对话框上的spinBox的值
    connect(this,SIGNAL(cellIndexChanged(int,int)),
            dlgLocate,SLOT(setSpinValue(int,int)));

    dlgLocate->show();//非模态显示对话框 ,程序不会阻塞。

}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{//单击单元格时，发射信号，传递单元格的行号、列号
    emit cellIndexChanged(index.row(),index.column());
}

