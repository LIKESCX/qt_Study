#ifndef DIALOG_H
#define DIALOG_H

#define TIMEFORMAT "HH:mm:ss"
#define DATEFORMAT "yyyy-MM-dd"
#define DATETIMEFORMAT "yyyy-MM-dd HH:mm:ss"

#include <QDialog>
#include <QTimer>
#include <QTime>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_btnGetTime_clicked();

    void on_btnSetTime_clicked();

    void on_btnSetDate_clicked();

    void on_btnSetDateTime_clicked();

    void on_calendarWidget_selectionChanged();

    void on_timer_timeout();//定时溢出处理槽函数

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnSetIntv_clicked();

private:
    Ui::Dialog *ui;
    QTimer *fTimer;     //定时器
    QTime fTimeCounter; //计时器
};

#endif // DIALOG_H
