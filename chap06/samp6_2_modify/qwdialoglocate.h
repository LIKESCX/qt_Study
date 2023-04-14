#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class QWDialogLocate;
}

//利用信号和槽实现交互操作
class QWDialogLocate : public QDialog
{
    Q_OBJECT
private: //定义为私有的话，这个函数是在关闭对话框时自动调用的。不能通过对象显示调用
    void closeEvent(QCloseEvent *event);//其实每一个继承Widget类的组件都有这个函数，只是执行默认的，这里相当于重写父类的方法。
    void showEvent(QShowEvent *event);
public:
    explicit QWDialogLocate(QWidget *parent = nullptr);
    ~QWDialogLocate();

    void setSpinRange(int rowCount, int colCount);//设置最大值

public slots: //这种槽函数 ，也可以通知对象.或指针->来显示调用。兼具普通函数的使用
    void setSpinValue(int rowNo, int colNo);//设置初始值

private slots:
    void on_btnSetText_clicked();

signals:
    void changeCellText(int row, int column, QString &text);
    void changeActionEnable(bool en);

private:
    Ui::QWDialogLocate *ui;
};

#endif // QWDIALOGLOCATE_H
