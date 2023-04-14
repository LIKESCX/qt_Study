#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "qwdialogheaders.h"
#include "qwdialoglocate.h"
#include <QCloseEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *LabCellPos = nullptr;//当前单元格行列号
    QLabel *LabCellText = nullptr;//当前单元格内容
    QStandardItemModel *theModel = nullptr;//数据模型
    QItemSelectionModel *theSelection = nullptr;//选择模型

    QWDialogHeaders *dlgSetHeaders = nullptr;

    //QWDialogLocate *dlgLocate = nullptr;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void closeEvent(QCloseEvent *event);//主窗口添加closeEvent()事件处理

private slots:
    //当前选择单元格发生变化
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actTab_SetSize_triggered();

    void on_actTab_SetHeader_triggered();

    void on_actTab_Locate_triggered();

    void on_tableView_clicked(const QModelIndex &index);

public slots:
    void setACellText(int row, int column, QString &text);//设置单元格内容
    void setActLocateEnable(bool enable);//设置actTab_Locate的enable属性
signals:
    void cellIndexChanged(int rowNo,int colNo);//当前单元格发生变化

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
