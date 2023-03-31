#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitterMain);
    //状态栏初始化创建
    labCellIndex = new QLabel("当前单元格坐标：",this);
    labCellIndex->setMinimumWidth(200);

    labCellType = new QLabel("当前单元格类型：",this);
    labCellType->setMinimumWidth(200);

    labStudID = new QLabel("学生ID: ",this);
    labStudID->setMinimumWidth(200);

    //加入到状态栏
    ui->statusBar->addWidget(labCellIndex);
    ui->statusBar->addWidget(labCellType);
    ui->statusBar->addWidget(labStudID);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//设置表头
void MainWindow::on_btnSetHeader_clicked()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"姓 名"<<"性 别"<<"出生日期"<<"民 族"<<"分 数"<<"是否党员";
//    ui->tableInfo->setHorizontalHeaderLabels(headerText);//简单设置行表头,如果需要样式的话，需要给行表头的每个单元格进行单独设置，如下

    ui->tableInfo->setColumnCount(headerText.count());//headerText.count()返回headerText中value值的个数
    for(int i = 0;i<ui->tableInfo->columnCount();i++){
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font();
        font.setBold(true);//设置为粗体
        font.setPointSize(12);//设置字体大小
        headerItem->setTextColor(Qt::black);//设置字体颜色
        headerItem->setFont(font);
        ui->tableInfo->setHorizontalHeaderItem(i,headerItem);
    }
}

//设置行号
void MainWindow::on_btnSetRowCount_clicked()
{
    int rowCount = ui->rowCountBox->value();//获取spinBox中设置的值
    //qDebug() << rowCount;
    ui->tableInfo->setRowCount(rowCount);//设置数据区行数
}

//初始化表格内容
void MainWindow::on_btnIniData_clicked()
{
    QString strName,strSex;
    bool isParty=false;
    QDate birth;
    birth.setDate(1980,4,7);//初始化一个日期
    ui->tableInfo->clearContents();//只清空工作区，不清除表头
    int Rows = ui->tableInfo->rowCount();//数据区行数
    for(int i=0;i<Rows;i++)
    {
        strName = QString::asprintf("学生%d",i);
        if((i % 2) == 0) //分奇数、偶数行设置性别，及其图标
            strSex="男";
        else
            strSex="女";
        createItemsARow(i, strName, strSex, birth, "汉族", isParty, 70);
        birth.addDays(20);//日期加20天
        isParty = !isParty;
    }
}

//为表格一行的各个单元格生成QTableWidgetItem对象
void MainWindow::createItemsARow(int rowNo, QString name, QString sex, QDate birth, QString nation, bool isPM, int score)
{
    QTableWidgetItem *item;
    QString str;
    uint studID=201605000;//学号基数
    //姓名
    item = new QTableWidgetItem(name,MainWindow::ctName);
    item->setTextAlignment(Qt::AlignCenter);//设置文字对齐方式，水平居中，垂直居中 这个地方的设置的源码待后面再深究
    studID +=rowNo;//学号=基数+行号
    item->setData(Qt::UserRole,QVariant(studID));//设置studID为data
    ui->tableInfo->setItem(rowNo,MainWindow::colName,item);
    //性别
    QIcon icon;
    if(sex == "男")
        icon.addFile(":/images/icons/boy.ico");
    else
        icon.addFile(":/images/icons/girl.ico");
    item = new QTableWidgetItem(sex,MainWindow::ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colSex,item);
    //出生日期
    str = birth.toString("yyyy-MM-dd");//日期转为字符串
    item = new QTableWidgetItem(str,MainWindow::ctBirth);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colBirth,item);
    //民族
    item = new QTableWidgetItem(nation,MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colNation,item);
    //是否党员
    item = new QTableWidgetItem("党员",MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignCenter);
    if(isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    item->setBackgroundColor(Qt::yellow);//设置单元格背景色
    ui->tableInfo->setItem(rowNo,MainWindow::colPartyM,item);
    //分数
    str.setNum(score);
    item = new QTableWidgetItem(str,MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colScore,item);
}


