#include "delegate.h"
#include<QComboBox>
#include<QLineEdit>
#include <QtDebug>
# pragma execution_character_set("utf-8")
Delegate::Delegate(QObject *parent): QItemDelegate(parent)
{
}
Delegate::~Delegate()
{
}
void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const
 {
     QItemDelegate::paint(painter, option, index);
 }
QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
     return QItemDelegate::sizeHint(option, index);
 }
QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid() && index.column() == AGECOLUM)
    {
        qDebug() << "isValid";
       InputAgeDlg *editor=new InputAgeDlg(parent);
       editor->installEventFilter(const_cast<Delegate *>(this));
       return editor;
    }
    else
    {
        qDebug() << "not Valid";
        return QItemDelegate::createEditor(parent, option, index);
    }
}
void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid() && index.column() == AGECOLUM)
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        InputAgeDlg *inputdge = qobject_cast<InputAgeDlg *>(editor);
        if(!value.isEmpty())
        {
            if(value.contains(tr("岁")))
            {
                inputdge->set_age_uint(tr("岁"));
                inputdge->set_Age(value.remove(tr("岁")));
            }
            if(value.contains(tr("月")))
            {
                inputdge->set_age_uint(tr("月"));
                inputdge->set_Age(value.remove(tr("月")));
            }
            if(value.contains(tr("天")))
            {
                inputdge->set_age_uint(tr("天"));
                inputdge->set_Age(value.remove(tr("天")));
            }
            if(value.contains(tr("小时")))
            {
                inputdge->set_age_uint(tr("小时"));
                inputdge->set_Age(value.remove(tr("小时")));
            }
        }
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}
void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.isValid() && index.column() == AGECOLUM)
    {
        InputAgeDlg *inputdge = qobject_cast<InputAgeDlg *>(editor);
        if(inputdge->age.isEmpty()||inputdge->age==" ")
            model->setData(index, "");
        else
            model->setData(index, inputdge->age+inputdge->age_uint);
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}
