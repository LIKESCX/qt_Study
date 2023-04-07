#include "qwintspindelegate.h"

#include <QSpinBox>

QWIntSpinDelegate::QWIntSpinDelegate(QObject *parent):QStyledItemDelegate(parent)
{

}

QWidget *QWIntSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{//创建代理编辑组件
    QSpinBox *editor = new QSpinBox(parent);
    editor->setFrame(false);//设置为无边框
    editor->setMinimum(0);
    editor->setMaximum(10000);
    return editor;
}

void QWIntSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{//从数据模型获取数据，显示到代理组件中
   int value = index.model()->data(index,Qt::EditRole).toInt();
   QSpinBox* spinBox = static_cast<QSpinBox*>(editor);//static_cast<T>作用等价于隐式转换
   spinBox->setValue(value);
}

void QWIntSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{//将代理组件中的数据保存到数据模型
    QSpinBox* spinBox = static_cast<QSpinBox*>(editor);//static_cast<T>作用等价于隐式转换
    spinBox->interpretText();//这里的interpretText()函数,是为了让我们获得到的是spin box中最新的的数据
    int value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void QWIntSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{//设置组件大小
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
