#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTreeWidgetItem>
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
    void on_actAddFolder_triggered();

    void on_actAddFiles_triggered();

    void on_treeFiles_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actDeleteItem_triggered();

    void removeItem(QTreeWidgetItem *item);//书上没有的

    void on_actScanItems_triggered();

    void on_actZoomFitH_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomRealSize_triggered();

    void on_actDockVisible_triggered(bool arg1);

    void on_actDockFloat_triggered(bool checked);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_dockWidget_topLevelChanged(bool topLevel);

private:
    Ui::MainWindow *ui;

private:
    //枚举类型treeItemType，创建节点时用作type参数，自定义类型必须大于1000
    enum treeItemType { //枚举中只给第一个参数赋值，后面的参数不显示赋值，自动会+1赋值。
       itTopItem = 1001,
       itGroupItem,
       itImageItem
    };
    //目录树列的编号
    enum treeColNum {
        colItem = 0,
        colItemType = 1
    };

    //用于状态栏文件名显示
    QLabel *LabFileName;
    //当前的图片
    QPixmap curPixmap;
    //当前图片缩放比例
    float pixRatio;

    //目录树初始化
    void initTree();
    //添加目录
    void addFolderItem(QTreeWidgetItem *parItem, QString dirName);
    //提取目录名称
    QString getFinalFolderName(const QString &fullPathName);
    //添加图片
    void addImageItem(QTreeWidgetItem *parItem, QString aFileName);
    //显示一个图片节点的图片
    void displayImage(QTreeWidgetItem *item);
    //遍历改变节点标题
    void changeItemCaption(QTreeWidgetItem *item);













};

#endif // MAINWINDOW_H
