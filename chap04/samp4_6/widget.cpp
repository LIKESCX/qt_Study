#include "widget.h"
#include "ui_widget.h"
#include <QTextBlock>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("QComboBox和QPlainTextEdit");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnIniItems_clicked()
{//"初始化列表"按钮
    QIcon icon;
    icon.addFile(":/images/icons/aim.ico");
    ui->comboBox->clear();
    for(int i = 0;i < 20; i++)
        ui->comboBox->addItem(icon,QString::asprintf("Item %d",i));//带图标
//        ui->comboBox->addItem(QString::asprintf("Item %d",i));//不带图标
}

void Widget::on_btnIni2_clicked()
{//初始化具有自定义数据的comboBox
    QMap<QString, int> City_Zone;
    City_Zone.insert("北京",10);
    City_Zone.insert("上海",21);
    City_Zone.insert("天津",22);
    City_Zone.insert("大连",411);
    City_Zone.insert("锦州",416);
    City_Zone.insert("徐州",516);
    City_Zone.insert("福州",591);
    City_Zone.insert("青岛",532);
    ui->comboBox2->clear();
    foreach (const QString &str, City_Zone.keys()) {
        ui->comboBox2->addItem(str, City_Zone.value(str));
    }
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}

void Widget::on_comboBox2_currentIndexChanged(const QString &arg1)
{
    QString zone = ui->comboBox2->currentData().toString();  //项关联数据
    ui->plainTextEdit->appendPlainText(arg1+":区号="+zone);
}


void Widget::on_btnToComboBox_clicked()
{//plainTextEdit 的内容逐行添加到comboBox的项
    QTextDocument *doc = ui->plainTextEdit->document();//文本对象
    int cnt = doc->blockCount();//回车符是一个block
    QIcon icon(":/images/icons/aim.ico");
    ui->comboBox->clear();
    for(int i = 0; i < cnt; i++)
    {
        QTextBlock textLine = doc->findBlockByNumber(i);
        QString str = textLine.text();
        ui->comboBox->addItem(icon,str);
    }
}
