#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(0,FixedColumnCount,this);//数据模型
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

    //为各列设置自定义代理组件
    ui->tableView->setItemDelegateForColumn(0,&intSpinDelegate);//测探
    ui->tableView->setItemDelegateForColumn(1,&floatSpinDelegate);//垂深
    ui->tableView->setItemDelegateForColumn(2,&floatSpinDelegate);//方位
    ui->tableView->setItemDelegateForColumn(3,&floatSpinDelegate);//总位移
    ui->tableView->setItemDelegateForColumn(4,&comboBoxDelegate);//固井质量
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
    curPath="D:/software/QT_Book/Study/chap05/samp5_3";//测试先写死
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
    //设置表头，一个或多个空格、TAB等分割符隔开的字符串，分解为一个StringList
    QString header = aFileContent.at(0);//at函数返回类型，返回类型为 const QString&，但是左值可以是 QString,将右侧引用的值，复制给QString变量
    //正则表达式中\s匹配任何空白字符，包括空格、制表符、换页符等等
    //而“\s+”则表示匹配任意多个上面的字符
    QStringList headerList = header.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerList);
    //设置表格数据
    QStandardItem *aItem;
    QStringList tmpList;
    int j;
    for (int i=1; i<rowCount; i++) {//i从1开始去除表头那行
        QString aLineText = aFileContent.at(i);
        tmpList = aLineText.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        for (j=0;j<FixedColumnCount-1 ;j++) {
            //不包含最后一列
            aItem = new QStandardItem(tmpList.at(j));
            theModel->setItem(i-1,j,aItem);//为模型的某个行列位置设置Item
        }
        aItem = new QStandardItem(tmpList.at(j));
        aItem->setCheckable(true);//设置为Checkable
        if(tmpList.at(j) == "0")
            aItem->setCheckState(Qt::Unchecked);
        else
            aItem->setCheckState(Qt::Checked);
        theModel->setItem(i-1,j,aItem);
    }

}

//添加行
void MainWindow::on_actAppend_triggered()
{//在表格最后添加行
    QList<QStandardItem*> aItemList;//列表类
    QStandardItem *aItem;
    for (int i=0;i<FixedColumnCount-1;i++ ) {//不包含最后1列
        aItem = new QStandardItem("0");//创建Item
        aItemList<<aItem;//添加到列表
    }
    //创建最后一列，并添加到列表
    //获取最后一列的表头文字
    QString str = theModel->headerData(theModel->columnCount()-1,Qt::Horizontal,Qt::DisplayRole).toString();
    aItem = new QStandardItem(str);//创建 "测井取样" Item
    aItem->setCheckable(true);
    aItemList<<aItem;//添加到列表

    theModel->insertRow(theModel->rowCount(),aItemList);//插入一行

    //当添加一行后，使当前选择区域变成新增的哪一行的第一个item.
    QModelIndex curIndex = theModel->index(theModel->rowCount()-1,0);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);

}

//插入行
void MainWindow::on_actInsert_triggered()
{//在表格中插入行
    QList<QStandardItem*> aItemList;//列表类
    QStandardItem *aItem;
    for (int i=0;i<FixedColumnCount-1;i++ ) {//不包含最后1列
        aItem = new QStandardItem("0");//创建Item
        aItemList<<aItem;//添加到列表
    }
    //创建最后一列，并添加到列表
    //获取最后一列的表头文字
    QString str = theModel->headerData(theModel->columnCount()-1,Qt::Horizontal,Qt::DisplayRole).toString();
    aItem = new QStandardItem(str);//创建 "测井取样" Item
    aItem->setCheckable(true);
    aItemList<<aItem;//添加到列表

    QModelIndex curIndex = theSelection->currentIndex();//获取当前选择的区域,如果区域涉及多行，那么返回区域左下角那个item的index
    bool isValid = curIndex.isValid();
    if(!isValid)
        qDebug()<< "index无效" << curIndex.row();
    else
        qDebug()<< "index有效" << curIndex.row();
    int curRow = curIndex.row();
    theModel->insertRow(curRow,aItemList);//在curRow的前面插入一行

    //当插入一行后，使当前选择区域变成新增的哪一行的第一个item.
    QModelIndex index = theModel->index(curRow,0);//那么刚插入的那一个行就是curRow的大小，之前的curRow自增1
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index,QItemSelectionModel::Select);
}

void MainWindow::on_actDelete_triggered()
{//删除行
    //qDebug() << theSelection->hasSelection();
    QModelIndex curIndex = theSelection->currentIndex();//获取模型索引
    int curRow = curIndex.row();
    qDebug() << curRow;
    if(curRow==theModel->rowCount()-1)//最后一行
    {
        theModel->removeRow(curRow);//删除最后一行
    }
    else
    {
        theModel->removeRow(curRow);//删除一行，并重新设置当前选择行
        theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
}


void MainWindow::on_actAlignLeft_triggered()
{//设置文字居左对齐
    if(!theSelection->hasSelection())//theSelection->currentIndex()返回有效的索引，并不代表hasSelection()返回true.至于两者的区别，暂不清楚。
        return;
    //获取选择的单元格的模型索引列表，可以是多选
    QModelIndexList selectedIndex = theSelection->selectedIndexes();//返回所有被选择的model item.而theSelection->currentIndex()返回当前the current item.
    for (int i=0;i<selectedIndex.count();i++) {
        QModelIndex aIndex = selectedIndex.at(i);
        QStandardItem *aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignLeft);
    }

}


void MainWindow::on_actAlignCenter_triggered()
{//设置文字居中对齐
    if(!theSelection->hasSelection())
        return;
    //获取选择的单元格的模型索引列表，可以是多选
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    for (int i=0;i<selectedIndex.count();i++) {
        QModelIndex aIndex = selectedIndex.at(i);
        QStandardItem *aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignCenter);
    }
}


void MainWindow::on_actAlignRight_triggered()
{//设置文字居右对齐
    if(!theSelection->hasSelection())
        return;
    //获取选择的单元格的模型索引列表，可以是多选
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    for (int i=0;i<selectedIndex.count();i++) {
        QModelIndex aIndex = selectedIndex.at(i);
        QStandardItem *aItem = theModel->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignRight);
    }
}


void MainWindow::on_actFontBold_triggered(bool checked)
{//设置文字粗体
    if(!theSelection->hasSelection())
        return;
    //获取选择的单元格的模型索引列表，可以是多选
    QModelIndexList selectedIndex = theSelection->selectedIndexes();
    for (int i=0;i<selectedIndex.count();i++) {
        QModelIndex aIndex = selectedIndex.at(i);
        QStandardItem *aItem = theModel->itemFromIndex(aIndex);
        QFont font = aItem->font();
        font.setBold(checked);//设置字体是否为粗体
        aItem->setFont(font);
    }
}

//数据另存为文件
void MainWindow::on_actSave_triggered()
{//保存为文件
   QString curPath = QCoreApplication::applicationDirPath();
   QString aFileName = QFileDialog::getOpenFileName(this,"选择一个文件",curPath,"井数据文件(*.txt);;所有文件(*.*)");
   if(aFileName.isEmpty())
       return;
   QFile aFile(aFileName);
   if(!(aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)))
       return;//以读写、覆盖原有内容方式打开文件
   QTextStream aStream(&aFile);
   QStandardItem *aItem;
   int i,j;
   QString str;
   ui->plainTextEdit->clear();//清空预览区

   //获取表头文字
   for (int i=0;i<theModel->columnCount();i++) {
       aItem = theModel->horizontalHeaderItem(i);//获取表头的项数据
       str=str+aItem->text()+"\t\t"; //以TAB隔开
   }
   aStream<<str<<"\n";//文件里需要加入换行符 \n
   ui->plainTextEdit->appendPlainText(str);
   //获取数据区文字
   for (i=0;i<theModel->rowCount();i++ )
   {
       str="";
       for (j=0;j<theModel->columnCount()-1;j++)
       {
          aItem = theModel->item(i,j);
          str = str+aItem->text()+"\t\t";
       }
       aItem = theModel->item(i,j);//最后一列是逻辑型
       if(aItem->checkState()==Qt::Checked)
           str=str+"1";
       else
           str=str+"0";
       ui->plainTextEdit->appendPlainText(str);
       aStream<<str<<"\n";
   }
}

