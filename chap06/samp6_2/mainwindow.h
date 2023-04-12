#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "qwdialogheaders.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *LabCellPos;//当前单元格行列号
    QLabel *LabCellText;//当前单元格内容
    QStandardItemModel *theModel;//数据模型
    QItemSelectionModel *theSelection;//选择模型

    QWDialogHeaders *dlgSetHeaders = nullptr;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //当前选择单元格发生变化
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actTab_SetSize_triggered();

    void on_actTab_SetHeader_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
