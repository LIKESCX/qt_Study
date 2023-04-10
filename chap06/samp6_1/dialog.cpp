#include "dialog.h"
#include "ui_dialog.h"
#include <QDir>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnOpen_clicked()
{//选择单个文件
    QString curPath = QDir::currentPath();//获取应用程序当前目录
    QString dlgTitle="选择一个文件";
    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if(!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}

void Dialog::on_btnOpenMulti_clicked()
{//选择多个文件
    QString curPath = QDir::currentPath();//获取应用程序当前目录
    QString dlgTitle="选择一个文件";
    QString filter="文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
    QStringList fileList = QFileDialog::getOpenFileNames(this,dlgTitle,curPath,filter);
    for(int i=0;i<fileList.count();i++)
    {
        ui->plainTextEdit->appendPlainText(fileList.at(i));
    }
}


void Dialog::on_btnSelDir_clicked()
{//选择文件夹
    QString curPath = QCoreApplication::applicationDirPath();//返回可执行文件所在的目录
    QString dlgTitle="选择一个目录";
    QString selectedDir = QFileDialog::getExistingDirectory(this,dlgTitle,curPath,QFileDialog::ShowDirsOnly);//返回值是选择的目录名称的字符串
    if(!selectedDir.isEmpty())
        ui->plainTextEdit->appendPlainText(selectedDir);
}


void Dialog::on_btnSave_clicked()
{//保存文件
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle="保存文件";
    QString filter="文件(*.h);;C++文件(*.cpp);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);
    if(!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}


void Dialog::on_btnColor_clicked()
{//选择颜色
    QPalette pal = ui->plainTextEdit->palette();//palette表示调色板,获取现有的调色板
    QColor iniColor = pal.color(QPalette::Text);//现有的文字颜色，即当前的文字颜色
    QColor color = QColorDialog::getColor(iniColor,this,"选择颜色");//打开选择颜色框，这里传入iniColor目的及作用，是当打开颜色选择框时，不选颜色，直接点击确定，就显示这个iniColor的颜色。
    if(color.isValid())//没有选择颜色，直接点击取消时，为false
    {
        pal.setColor(QPalette::Text,color);
        ui->plainTextEdit->setPalette(pal);
    }
}


void Dialog::on_btnFont_clicked()
{//选择字体
    const QFont& iniFont = ui->plainTextEdit->font();
    bool ok = false;
    //If the user clicks OK, the selected font is returned. If the user clicks Cancel, the initial font is returned.
//    QFont font = QFontDialog::getFont(&ok,iniFont);
    QFont font = QFontDialog::getFont(&ok,iniFont,this,"选择字体");//getFont静态函数返回的QFont,没有isValid()的函数，所以这里通过传入的ok变量，来判断用户是否选择了字体,没有选择直接取消或直接点击确定，就显示传入的iniFont的字体。
    if(ok)
        ui->plainTextEdit->setFont(font);

}


void Dialog::on_btnInputString_clicked()
{//输入字符串
    QString dlgTitle="输入文字对话框";
    QString txtLabel="请输入文件名";
    QString defaultInput="新建文件.txt";
    //设置输入模式
    QLineEdit::EchoMode echoMode = QLineEdit::Normal;//普通文本
//    QLineEdit::EchoMode echoMode = QLineEdit::Password;//密码输入
    bool ok = false;
    QString text = QInputDialog::getText(this,dlgTitle,txtLabel,echoMode,defaultInput,&ok);
    if(ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);

}


void Dialog::on_btnInputInt_clicked()
{//输入整数
    QString dlgTitle="输入整数对话框";
    QString txtLabel="设置字体大小";
    int defaultValue = ui->plainTextEdit->font().pointSize();
    int minValue=6, maxValue=50, stepValue=1;
    bool ok = false;
    int inputValue = QInputDialog::getInt(this,dlgTitle,txtLabel,defaultValue,minValue,maxValue,stepValue,&ok);
    if(ok)
    {
        QFont font = ui->plainTextEdit->font();
        font.setPointSize(inputValue);
        ui->plainTextEdit->setFont(font);
    }
    //这里 font()函数原型是 const QFont &font() const 即返回类型是 const QFont & ，但是这里我们用QFont font来接收返回值，也是可以的。
    //用Font font来接收的话，就是程序自动把返回的引用对应的对象，赋值给 Font font，相当于拷贝一个新的对象，可以修改这个新的对象。而用const QFont &接收，
    //返回的是一个引用变量，指向函数返回值，无新对象创建，不能通过此引用变量修改对象内容。
}


void Dialog::on_btnInputInt_2_clicked()
{//输入浮点数
    QString dlgTitle="输入浮点数对话框";
    QString txtLabel="输入一个浮点数";
    float defaultValue=3.13;
    float minValue=0, maxValue=1000;
    int decimals=2;//小数点位数,在输入栏里最多只能输入到小数点第2位
    bool ok = false;
    float inputValue = QInputDialog::getDouble(this,dlgTitle,txtLabel,defaultValue,minValue,maxValue,decimals,&ok);
    if(ok)
    {
        QString str = QString::asprintf("输入一个浮点数:%.2f",inputValue);//%.2f:表示小数点后显示2位小数，不足的补零。
        ui->plainTextEdit->appendPlainText(str);
    }
}


void Dialog::on_btnInputItem_clicked()
{//条目选择输入
    QStringList items;
    items << "优秀" << "良好" << "合格" << "不合格";
    QString dlgTitle = "条目选择对话框";
    QString txtLabel = "请选择级别";
    int curIndex = 2; //初始选择项
    bool editable = true;//Combox是否可编辑
    bool ok = false;
    QString text = QInputDialog::getItem(this,dlgTitle,txtLabel,items,curIndex,editable,&ok);
    if(ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);
}


void Dialog::on_btnMsgInformation_clicked()
{//information
    QString dlgTitle = "information消息框";
    QString strInfo = "文件已打开，字体大小已设置";
    QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok,QMessageBox::NoButton);
}


void Dialog::on_brnMsgWarning_clicked()
{//warning
    QString dlgTitle = "warning消息框";
    QString strInfo = "文件内容已经被修改";
    QMessageBox::warning(this,dlgTitle,strInfo);
}


void Dialog::on_brnMsgCritical_clicked()
{//critical
    QString dlgTitle = "critical消息框";
    QString strInfo = "有不明程序访问网络";
    QMessageBox::critical(this,dlgTitle,strInfo);
}


void Dialog::on_btnMsgAbout_clicked()
{//about
    QString dlgTitle = "about消息框";
    QString strInfo = "我开发的数据查看软件V1.0\n 保留所有版权";
    QMessageBox::about(this,dlgTitle,strInfo);
}


void Dialog::on_btnMsgQuestion_clicked()
{
    QString dlgTitle = "Question消息框";
    QString strInfo = "文件已被修改，是否保存修改？";
    QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton;
    QMessageBox::StandardButton result;//返回选择的按钮
    result =QMessageBox::question(this,dlgTitle,strInfo,QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,defaultBtn);
    if(result==QMessageBox::Yes)
        ui->plainTextEdit->appendPlainText("Question消息框: Yes 被选择");
    else if(result==QMessageBox::No)
        ui->plainTextEdit->appendPlainText("Question消息框: No 被选择");
    else
        ui->plainTextEdit->appendPlainText("Question消息框: 无选择");
}

