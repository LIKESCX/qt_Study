#ifndef QWMAINWINDOW_H
#define QWMAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class QWMainWindow; }
QT_END_NAMESPACE

class QWMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QWMainWindow(QWidget *parent = nullptr);
    ~QWMainWindow();

    void paintEvent(QPaintEvent *event);
private:
    Ui::QWMainWindow *ui;
};
#endif // QWMAINWINDOW_H
