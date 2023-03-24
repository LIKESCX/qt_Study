#ifndef QWDLGMANUAL_H
#define QWDLGMANUAL_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>

class QWDlgManual : public QDialog
{
    Q_OBJECT

private:
    //复选框组件
    QCheckBox *chkBoxUnder;
    QCheckBox *chkBoxItalic;
    QCheckBox *chkBoxBold;

    //单选按钮组件
    QRadioButton *rBtnBlack;
    QRadioButton *rBtnRed;
    QRadioButton *rBtnBlue;

    //普通文本编辑组件
    QPlainTextEdit *txtEdit;

    //确定 取消 关闭 按钮组件
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QPushButton *btnClose;

    void iniUi();  //UI创建与初始化
    void iniSignalSlots(); //初始化信号与槽的链接

private slots:
    void on_chkBoxUnder(bool checked);    // Underline的槽函数
    void on_chkBoxItalic(bool checked);   // Italic的槽函数
    void on_chkBoxBold(bool checked);     // Bold的槽函数
    void setTextFontColor();              // 设置字体颜色

public:
    QWDlgManual(QWidget *parent = 0);
    ~QWDlgManual();
};

#endif // QWDLGMANUAL_H
