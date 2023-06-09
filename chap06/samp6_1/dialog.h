#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnOpen_clicked();

    void on_btnOpenMulti_clicked();

    void on_btnSelDir_clicked();

    void on_btnSave_clicked();

    void on_btnColor_clicked();

    void on_btnFont_clicked();

    void on_btnInputString_clicked();

    void on_btnInputInt_clicked();

    void on_btnInputInt_2_clicked();

    void on_btnInputItem_clicked();

    void on_btnMsgInformation_clicked();

    void on_brnMsgWarning_clicked();

    void on_brnMsgCritical_clicked();

    void on_btnMsgAbout_clicked();

    void on_btnMsgQuestion_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
