#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
     * 将ScrollArea组件设置为主窗口工作区的中心组件后，
     * DockWidget与ScrollArea之间自动出现分割条，可以分割两个组件的大小
     */
    setCentralWidget(ui->scrollArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}
