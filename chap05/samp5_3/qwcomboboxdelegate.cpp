#include "qwcomboboxdelegate.h"
#include <QComboBox>
#include <QDebug>
QWComboBoxDelegate::QWComboBoxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *QWComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{//创建代理编辑组件
    QComboBox *comboBox = new QComboBox(parent);
    //给comboBox赋值
    //第一种方式
//    QStringList strList;
//    strList<<"优"<<"良"<<"一般"<<"不及格";
//    comboBox->addItems(strList);

    //第二种方式
    comboBox->addItem("优");
    comboBox->addItem("良");
    comboBox->addItem("一般");
    comboBox->addItem("不及格");
    return comboBox;
}

void QWComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //从数据模型获取数据，显示到代理组件中
    QString str = index.model()->data(index,Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(str);//这里不设置的话，就会出现一双击时，出现待编辑的当前项 不是优的会自动变成优,因为当双击后，就展示的是comboBox控件内的内容了。
}

void QWComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //将代理组件中的数据，保存到数据模型
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString str = comboBox->currentText();
    model->setData(index,str,Qt::EditRole);
}

void QWComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{//设置组件大小
    editor->setGeometry(option.rect);
}

