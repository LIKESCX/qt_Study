#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"
#include <QPainter>
QWMainWindow::QWMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QWMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();//清除所有页面
    //ui->tabWidget->tabsClosable();//
    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized);//窗口最大化显示
}

QWMainWindow::~QWMainWindow()
{
    delete ui;
}

void QWMainWindow::paintEvent(QPaintEvent *event)
{//绘制窗口背景图片
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,ui->mainToolBar->height(),this->width(),
                       this->height()-ui->mainToolBar->height()-ui->statusBar->height(),
                       QPixmap(":/images/icons/back2.jpg"));
}

