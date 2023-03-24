#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QListWigdet的使用");
    setCentralWidget(ui->splitter);//发现这行加不加不受影响
    setActionsForButton();
    createSelectionPopMemu();
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);//需要在Listwidget上设置菜单策略,默认的是DefaultContextMenu否则按默认的策略，右键时，触发不了槽函数，不弹框，也可以在UI中搜索设置。
}

MainWindow::~MainWindow()
{
    delete ui;
}

//actListIni实现listWidget的列表项初始化
void MainWindow::on_actListIni_triggered()
{//初始化列表
    QListWidgetItem *aItem = Q_NULLPTR; //每一行是一个QListWidgetItem
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk = ui->chkBoxListEditable->isChecked();//是否可编辑
    ui->listWidget->clear();
    for(int i=0; i<10; i++)
    {
        QString str = QString::asprintf("Item %d",i);
        aItem = new QListWidgetItem();
        aItem->setText(str);//设置文字标签
        aItem->setIcon(aIcon);//设置图标
        aItem->setCheckState(Qt::Checked);//设置为选中状态
        if(chk) //可编辑，设置flags
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled); //里面用到了QFlags<menu>
        else//不可编辑，设置flags
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        ui->listWidget->addItem(aItem);//增加一个项
    }
}

//插入项功能槽函数
void MainWindow::on_actListInsert_triggered()
{//插入一项
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk = ui->chkBoxListEditable->isChecked();//是否可编辑
    QListWidgetItem *aItem = new QListWidgetItem("New Insert Item");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Checked);
    if(chk) //可编辑，设置flags
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled); //里面用到了QFlags<menu>
    else//不可编辑，设置flags
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    int row = ui->listWidget->currentRow();
    //qDebug()<< row;
    ui->listWidget->insertItem(row,aItem);//插入一个项
}

//删除当前项
void MainWindow::on_actListDelete_triggered()
{//删除当前项
    int row = ui->listWidget->currentRow();
    qDebug() << row;
    //Items removed from a list widget will not be managed by Qt, and will need to be deleted manually.
    QListWidgetItem *aItem = ui->listWidget->takeItem(row);
    if(aItem != Q_NULLPTR){
        delete aItem;//手动删除对象(堆中)
    }
}

//清空列表框所有项
void MainWindow::on_actListClear_triggered()
{
    ui->listWidget->clear();
}

//全选 actSelALL的槽函数
void MainWindow::on_actSelALL_triggered()
{//全选
    int cnt = ui->listWidget->count();
    for(int i=0; i<cnt; i++)
    {
        //qDebug() << i;
        QListWidgetItem *aItem = ui->listWidget->item(i);//获取一个项
        aItem->setCheckState(Qt::Checked);//设置选中
    }

}

//为listWidget的currentItemChanged()信号编写槽函数【在QListWigdet界面中右键选择go to slot进入之后，找到对应的信号，自动生成对应的槽函数】
void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{//listWidget当前选中项发生变化
    QString str;
    if(current != Q_NULLPTR) //Qt中空指针 推荐使用Q_NULLPTR
    {
        if(previous == Q_NULLPTR)
            str = "当前项："+current->text();
        else
            str = "前一项："+previous->text()+";当前项："+current->text();
        ui->editCutItemText->setText(str);
    }
}

void MainWindow::setActionsForButton()
{//为QToolButton按钮设置Action
    ui->tBtnListIni->setDefaultAction(ui->actListIni);
    ui->tBtnListClear->setDefaultAction(ui->actListClear);
    ui->tBtnListInsert->setDefaultAction(ui->actListInsert);
    ui->tBtnListAppend->setDefaultAction(ui->actListAppend);
    ui->tBtnListDelete->setDefaultAction(ui->actListDelete);

    ui->tBtnSelAll->setDefaultAction(ui->actSelALL);
    ui->tBtnSelNone->setDefaultAction(ui->actSelNone);
    ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);
}

void MainWindow::createSelectionPopMemu()
{//创建下拉菜单
    QMenu *menuSelection = new QMenu(this);//创建弹出式菜单
    menuSelection->addAction(ui->actSelALL);
    menuSelection->addAction(ui->actSelNone);
    menuSelection->addAction(ui->actSelInvs);
    //listWidget上方的tBtnSelectItem按钮
    ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);//设置弹出菜单的模式，也可在Ui中设置
    ui->tBtnSelectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置标题文字的位置，也可在Ui中设置
    ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu);//关联Action
    ui->tBtnSelectItem->setMenu(menuSelection);//设置下拉菜单
    //工具栏上的 下拉式菜单按钮
    QToolButton *aBtn = new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);
    aBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//按钮样式
    aBtn->setDefaultAction(ui->actSelPopMenu);//关联Action
    aBtn->setMenu(menuSelection);//设置下拉菜单
    ui->mainToolBar->addWidget(aBtn);//工具栏添加按钮
    //工具栏添加分割条,和"退出按钮"
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actQuit);

}

//创建右键快捷菜单 为listWidget组件的customContextMenuRequested()信号创建槽函数
void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
//    qDebug() << "coming";
   Q_UNUSED(pos);
   QMenu *menuList = new QMenu(this);//创建菜单
   //添加Actions创建菜单项
   menuList->addAction(ui->actListIni);
   menuList->addAction(ui->actListClear);
   menuList->addAction(ui->actListInsert);
   menuList->addAction(ui->actListAppend);
   menuList->addAction(ui->actListDelete);
   menuList->addSeparator();
   menuList->addAction(ui->actSelALL);
   menuList->addAction(ui->actSelNone);
   menuList->addAction(ui->actSelInvs);
//   qDebug() << "弹框打开";
   //静态函数QCursor::pos()获取鼠标光标当前位置。
   menuList->exec(QCursor::pos());//在鼠标光标位置显示右键快捷菜单 //菜单弹出后，会阻塞到这里，当选中一项后，弹窗消失，执行下面的delete 删除堆中对象
//   qDebug() << "弹框消失";
   delete menuList;
}
