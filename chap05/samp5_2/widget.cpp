#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList theStrList;
    theStrList << "北京" << "上海" << "天津" << "广州" << "深圳" << "郑州" << "成都";
    theModel = new QStringListModel(this);
    theModel->setStringList(theStrList);//导入theStrList的内容
    ui->listView->setModel(theModel);//设置数据模型
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

}

Widget::~Widget()
{
    delete ui;
}

//添加项
void Widget::on_btnListAppend_clicked()
{//添加一行
    theModel->insertRow(theModel->rowCount());//在尾部插入一行
    QModelIndex index = theModel->index(theModel->rowCount()-1,0);//上面一行代码在模型中插入了一行，这里再获取rowCount()时，会多1.
    theModel->setData(index,"new item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);//设置当前选中的行

}

//插入项  在当前行的前面插入一行
void Widget::on_btnListInsert_clicked()
{//插入一行
    QModelIndex index = ui->listView->currentIndex();
    bool ret = theModel->insertRow(index.row());//例如：index.row() 返回 5，那么当前是第5行，从0开始
    //qDebug()<<ret;
    if(!ret)
        return;
    theModel->setData(index,"inserted item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);//设置当前选中的行
}


void Widget::on_btnListDelete_clicked()
{//删除当前行
    QModelIndex index = ui->listView->currentIndex();
    qDebug()<<index.row();
    bool ret = theModel->removeRow(index.row());
    qDebug()<<ret;
}


void Widget::on_btnListClear_clicked()
{//清空所有项
    theModel->removeRows(0,theModel->rowCount());
}


void Widget::on_btnTextImport_clicked()
{//显示数据模式的StringList
    QStringList tempList = theModel->stringList();
    ui->plainTextEdit->clear();
    for (int i=0;i<tempList.count() ;i++ )
        ui->plainTextEdit->appendPlainText(tempList.at(i));
}


void Widget::on_listView_clicked(const QModelIndex &index)
{//显示QModelIndex的行和列
    ui->LabInfo->setText(QString::asprintf("当前项：row=%d, column=%d",index.row(),index.column()));
}

