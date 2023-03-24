#include "qwdlgmanual.h"

//下面这两个引入一个就行了，因为他们都指向同一个头文件 qboxlayout.h
#include <QHBoxLayout>
#include <QVBoxLayout>

//3个checkBox的响应槽函数定义
void QWDlgManual::on_chkBoxUnder(bool checked)
{
    QFont font = txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxItalic(bool checked)
{
    QFont font = txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxBold(bool checked)
{
    QFont font = txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

//3个颜色设置的RadioButton的共同响应槽函数定义
void QWDlgManual::setTextFontColor()
{
   QPalette plet =  txtEdit->palette();
   if(rBtnBlack->isChecked())
       plet.setColor(QPalette::Text,Qt::black);
   else if(rBtnBlue->isChecked())
       plet.setColor(QPalette::Text,Qt::blue);
   else if(rBtnRed->isChecked())
       plet.setColor(QPalette::Text,Qt::red);
   else
       plet.setColor(QPalette::Text,Qt::black);
   txtEdit->setPalette(plet);
}

//initUi()函数实现界面组件的创建与布局，以及属性设置。下面是iniUi()的完整代码。
void QWDlgManual::iniUi()
{
    //创建 Underline,Italic,Bold 3个checkBox,并水平布局
    chkBoxUnder = new QCheckBox(tr("Underline"));//使用tr()函数进行包裹，方便以后进行国际化翻译,tr()函数是QObject下的函数
    chkBoxItalic = new QCheckBox(tr("Italic"));
    chkBoxBold = new QCheckBox(tr("Bold"));
    QHBoxLayout *HLay1 = new QHBoxLayout(); //水平布局
    HLay1->addWidget(chkBoxUnder);
    HLay1->addWidget(chkBoxItalic);
    HLay1->addWidget(chkBoxBold);

    //创建 Black, Red, Blue 3个RadioButton，并水平布局
    rBtnBlack = new QRadioButton(tr("Black"));
    rBtnRed = new QRadioButton(tr("Red"));
    rBtnBlue = new QRadioButton(tr("Blue"));
    QHBoxLayout *HLay2 = new QHBoxLayout(); //水平布局
    HLay2->addWidget(rBtnBlack);
    HLay2->addWidget(rBtnRed);
    HLay2->addWidget(rBtnBlue);

    //创建 确定，取消，退出 3个PushButton,并水平布局
    btnOK = new QPushButton(tr("确定"));
    btnCancel = new QPushButton(tr("取消"));
    btnClose = new QPushButton(tr("退出"));
    QHBoxLayout *HLay3 = new QHBoxLayout(); //水平布局
    HLay3->addStretch();
    HLay3->addWidget(btnOK);
    HLay3->addWidget(btnCancel);
    HLay3->addStretch();
    HLay3->addWidget(btnClose);

    //创建 文本框，并设初始化字体
    txtEdit = new QPlainTextEdit();
    txtEdit->setPlainText("Hello world It is my demo");
    QFont font = txtEdit->font();  //获取字体
    font.setPointSize(20);     //修改字体大小
    txtEdit->setFont(font);    //设置字体

    //创建垂直布局，并设置为主布局
    QVBoxLayout *VLay = new QVBoxLayout();
    VLay->addLayout(HLay1);     //添加字体类型组
    VLay->addLayout(HLay2);     //添加字体颜色组
    VLay->addWidget(txtEdit);     //添加 PlainTextEdit
    VLay->addLayout(HLay3);     //添加 按键组
    setLayout(VLay);            //设置为窗体的主布局
}

//信号与槽的关联  函数iniSignalSlots
void QWDlgManual::iniSignalSlots()
{
    //三个颜色QRadioButton的clicked()信号与setTextFontColor()槽函数关联
    connect(rBtnBlack,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(rBtnBlue,SIGNAL(clicked()),this,SLOT(setTextFontColor()));
    connect(rBtnRed,SIGNAL(clicked()),this,SLOT(setTextFontColor()));

    //三个字体设置的 QCheckBox的clicked(bool)信号与相应的槽函数的关联
    connect(chkBoxUnder,SIGNAL(clicked(bool)),this,SLOT(on_chkBoxUnder(bool)));
    connect(chkBoxItalic,SIGNAL(clicked(bool)),this,SLOT(on_chkBoxItalic(bool)));
    connect(chkBoxBold,SIGNAL(clicked(bool)),this,SLOT(on_chkBoxBold(bool)));

    //三个按钮的信号与窗体的槽函数的关联
    connect(btnOK,SIGNAL(clicked()),this,SLOT(accept()));
    connect(btnCancel,SIGNAL(clicked()),this,SLOT(reject()));
    connect(btnClose,SIGNAL(clicked()),this,SLOT(close()));
 }

QWDlgManual::QWDlgManual(QWidget *parent) : QDialog(parent)
{
    iniUi();//界面创建与布局
    iniSignalSlots();//信号与槽的关联
    setWindowTitle("From created mannually");//设置窗体主题
}

QWDlgManual::~QWDlgManual()
{
    //清理分配的自由存储区(堆区内存) -- 不用手动删除，QObject的派生类会自动被回收
    //复选框组件
//    delete chkBoxUnder;
//    delete chkBoxItalic;
//    delete chkBoxBold;

    //单选按钮组件
//    delete rBtnBlack;
//    delete rBtnRed;
//    delete rBtnBlue;

    //普通文本编辑组件
//    delete txtEdit;

    //确定 取消 关闭 按钮组件
//    delete btnOK;
//    delete btnCancel;
//    delete btnClose;
}

