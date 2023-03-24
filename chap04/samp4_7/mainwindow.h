#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
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
    void on_actListIni_triggered();

    void on_actListInsert_triggered();

    void on_actListDelete_triggered();

    void on_actListClear_triggered();

    void on_actSelALL_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;

private:
    void setActionsForButton();//为toolBox下的toolButton设置action
    void createSelectionPopMemu();//为QtoolButton按钮设计下拉菜单
};

#endif // MAINWINDOW_H
