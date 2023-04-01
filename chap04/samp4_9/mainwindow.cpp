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

//初始化表格内容,注意再删除行时rowCount也自动增减，所以都删除都需要重新设置行号，才能进行初始化表格
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
        birth = birth.addDays(20);//日期加20天
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



void MainWindow::on_tableInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{//当前选择单元格发生变化时的响应
    QTableWidgetItem *item = ui->tableInfo->item(currentRow,currentColumn);
    //编译器支持C++11，Q_NULLPTR 会变为nullptr，不支持变为NULL。所以直接用Q_NULLPTR就好了
    if(item == Q_NULLPTR)
        return;
    labCellIndex->setText(QString::asprintf("当前单元格坐标:%d 行, %d列",currentRow,currentColumn));
    int cellType = item->type();//获取单元格的类型
    labCellType->setText(QString::asprintf("当前单元格类型：%d",cellType));
    item = ui->tableInfo->item(currentRow,MainWindow::colName);//第1列的item
    int ID = item->data(Qt::UserRole).toInt();//读取用户自定义数据
    labStudID->setText(QString::asprintf("学生ID: %d",ID));//学生ID
}


void MainWindow::on_btnInsertRow_clicked()
{//插入行
    int curRow = ui->tableInfo->currentRow();
    //在行号为curRow的前面插入一行，如果curRow等于或大于总行数，则在表格最后添加一行。
    ui->tableInfo->insertRow(curRow);//插入一行，不会自动为单元格创建item
    createItemsARow(curRow,"新学生","男",QDate::fromString("1990-1-1","yyyy-M-d"),"苗族",true,80);
}



void MainWindow::on_btnAppendRow_clicked()
{//添加一行
    int curRow = ui->tableInfo->rowCount();//获取表格总行数
    ui->tableInfo->insertRow(curRow);//在表格尾部添加一行
    createItemsARow(curRow,"新生","女",QDate::fromString("2000-1-1","yyyy-M-d"),"满族",true,85);
}


void MainWindow::on_btnDelCurRow_clicked()
{//删除当前行及其items
    int curRow = ui->tableInfo->currentRow();
    ui->tableInfo->removeRow(curRow);//删除当前行及其items，会释放item在堆中的内存
}

//用表格可编辑 复选框 控制 单元格是否可编辑,其实QTableWidget的editTriggers属性默认是可以编辑的，这个可以在UI界面看到，这里在UI上把默认值改为不可编辑。
void MainWindow::on_chkBoxTabEditable_clicked(bool checked)
{//设置编辑模式
    if(checked)
        ui->tableInfo->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);//双击或获取焦点后单击，进入编辑状态
    else
        ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑模式
}

