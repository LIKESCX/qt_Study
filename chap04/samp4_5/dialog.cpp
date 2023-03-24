#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    fTimer = new QTimer(this);
    fTimer->stop();
    fTimer->setInterval(1000);//设置定时周期，单位：毫秒
    ui->spinIntv->setValue(1000);
    connect(fTimer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btnGetTime_clicked()
{
    //获取当前日期时间，为三个专用编辑器设置时间、日期、日期时间
    QDateTime curDateTime = QDateTime::currentDateTime();
    ui->timeEdit->setTime(curDateTime.time());
    ui->editTime->setText(curDateTime.toString(TIMEFORMAT));
    ui->dateEdit->setDate(curDateTime.date());
    ui->editDate->setText(curDateTime.toString(DATEFORMAT));
    ui->dateTimeEdit->setDateTime(curDateTime);
    ui->editDateTime->setText(curDateTime.toString(DATETIMEFORMAT));
}

//设置时间
void Dialog::on_btnSetTime_clicked()
{
    QString str = ui->editTime->text();
    if(!str.isEmpty())
    {
       QTime time = QTime::fromString(str,TIMEFORMAT);//静态函数
       ui->timeEdit->setTime(time);
    }
}

//设置日期
void Dialog::on_btnSetDate_clicked()
{
    QString str = ui->editDate->text();
    if(!str.isEmpty())
    {   /**
         * @brief date
         * 将yyyy-MM-dd格式的字符串日期转为QDate类型，如果没有QDate指定格式默认是 yyyy/M/d格式展示。
         * 可以通过给dateEdit的displayFormat设置其格式，通过Ui设置的话，初始化UI时就会自动按其设定格式展示。
         * 如果通过代码可以写到ui->setupUi(this);后面。如果写到槽函数中，只有当槽函数被执行时才会设置格式
         * 其他两个timeEdit和dateTimeEdit是一样的道理
         */
        QDate date = QDate::fromString(str,DATEFORMAT);
        ui->dateEdit->setDate(date);
    }
}

//设置日期时间
void Dialog::on_btnSetDateTime_clicked()
{
    QString str = ui->editDateTime->text();
    str = str.trimmed();
    if(!str.isEmpty())
    {
        QDateTime dateTime = QDateTime::fromString(str,DATETIMEFORMAT);
        ui->dateTimeEdit->setDateTime(dateTime);
    }
}

void Dialog::on_calendarWidget_selectionChanged()
{  //在日历上选择日期
    QDate date = ui->calendarWidget->selectedDate();
    QString str = date.toString("yyyy年M月d日");
    ui->editCalendar->setText(str);
}

void Dialog::on_timer_timeout()
{
    //定时器中断响应
    QTime curTime = QTime::currentTime();//获取当前时间
    ui->LCDHour->display(curTime.hour());//显示 小时
    ui->LCDMin->display(curTime.minute());//显示 分钟
    ui->LCDSec->display(curTime.second());//显示 秒

    //设置进度条显示
    int va = ui->progressBar->value();
    va++;
    if(va > 100)
        va = 0;
    ui->progressBar->setValue(va);
}

void Dialog::on_btnStart_clicked()
{
    fTimer->start();//定时器开始工作
    fTimeCounter.start();//计时器开始工作
    ui->btnStart->setEnabled(false); //将开始按钮置为不可点击
    ui->btnStop->setEnabled(true);   //将停止按钮置为可点击
    ui->btnSetIntv->setEnabled(false);//将设置周期按钮置为不可点击
}

void Dialog::on_btnStop_clicked()
{
    fTimer->stop(); //定时器停止
    int tmMsec = fTimeCounter.elapsed();//毫秒数
    int sec = tmMsec/1000; //获取秒数
    int ms = tmMsec%1000;//获取毫秒数
    QString str = QString::asprintf("流逝时间：%d 秒, %d 毫秒",sec,ms);
    ui->LabElapsTime->setText(str);
    ui->btnStart->setEnabled(true); //将开始按钮置为可点击
    ui->btnStop->setEnabled(false);   //将停止按钮置为不可点击
    ui->btnSetIntv->setEnabled(true);//将设置周期按钮置为可点击

}

//设置周期
void Dialog::on_btnSetIntv_clicked()
{
    int val = ui->spinIntv->value();
    fTimer->setInterval(val);//设置定时周期，单位：毫秒
}
