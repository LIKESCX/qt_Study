#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(2,FixedColumnCount,this);//数据模型
    theSelection = new QItemSelectionModel(theModel);//选择模型

    //选择当前单元格变化时的信号与槽
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));

    ui->tableView->setModel(theModel);//设置数据模型
    ui->tableView->setSelectionModel(theSelection);//设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);//设置选择模式
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    setCentralWidget(ui->splitter);

    //设置下方的状态栏
    LabCurFile = new QLabel("当前文件:");
    LabCurFile->setMinimumWidth(200);
    LabCellPos = new QLabel("单元格位置:");
    LabCellPos->setMinimumWidth(150);
    LabCellText = new QLabel("单元格内容:");

    ui->statusbar->addWidget(LabCurFile);
    ui->statusbar->addWidget(LabCellPos);
    ui->statusbar->addWidget(LabCellText);
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{//选择单元格变化时的响应
    Q_UNUSED(previous);
    if(current.isValid())
    {
        LabCellPos->setText(QString::asprintf("当前单元格: %d行，%d列",current.row(),current.column()));
        QStandardItem *aItem = theModel->itemFromIndex(current);
        LabCellText->setText("单元格内容："+aItem->text());
        QFont font = aItem->font();
        ui->actFontBold->setChecked(font.bold());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//槽函数
void MainWindow::on_actOpen_triggered()
{//打开文件
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this,"打开一个文件",curPath,"井数据文件(*.txt);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return;
    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text))//打开文件
    {
        QTextStream aStream(&aFile);//用文本流读取数据
        ui->plainTextEdit->clear();
        while(!aStream.atEnd())
        {
            QString str = aStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fFileContent.append(str);
        }
        aFile.close();
        this->LabCurFile->setText("当前文件:"+aFileName);//状态栏显示
        iniModelFromStringList(fFileContent);//初始化数据模型
    }
}

void MainWindow::iniModelFromStringList(QStringList& aFileContent)
{//从一个StringList 获取数据，初始化数据模型
    int rowCount = aFileContent.count();//文本行数，第一行是标题
    theModel->setRowCount(rowCount-1);

}

