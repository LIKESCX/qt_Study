#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnIniItems_clicked();

    void on_btnIni2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox2_currentIndexChanged(const QString &arg1);

    void on_btnToComboBox_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
