#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFileSystemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

private:
    QFileSystemModel *model;//定义一个QFileSystemModel类的指针变量model
};

#endif // MAINWINDOW_H
