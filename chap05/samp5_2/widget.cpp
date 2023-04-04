#include "widget.h"
#include "ui_widget.h"

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
