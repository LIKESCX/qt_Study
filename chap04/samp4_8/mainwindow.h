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

private:
    Ui::MainWindow *ui;

private:
    //枚举类型treeItemType，创建节点时用作type参数，自定义类型必须大于1000
    enum treeItemType {
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
