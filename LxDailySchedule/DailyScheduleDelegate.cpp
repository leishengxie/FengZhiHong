#include "DailyScheduleDelegate.h"
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include "DailyScheduleModel.h"
#include "StartEndTimeEditor.h"

#define LINE_COLOR      QColor(233,237,243)

static QRect checkBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)/*const*/
{
    //绘制按钮所需要的参数
    QStyleOptionButton checkBoxStyleOption;
    //按照给定的风格参数 返回元素子区域
    QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);
    //返回QCheckBox坐标
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - checkBoxRect.width() / 2,
                         viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - checkBoxRect.height() / 2);
    //返回QCheckBox几何形状
    return QRect(checkBoxPoint, checkBoxRect.size());
}


CDailyScheduleDelegate::CDailyScheduleDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void CDailyScheduleDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return QStyledItemDelegate::paint(painter, option, index);
    }
    T_ScheduleItem tScheduleItem = qvariant_cast<T_ScheduleItem>(index.data());

    QStyleOptionViewItem  view_option(option);
    QRect rect = view_option.rect;

    auto role = QPalette::Text;
    if (view_option.state & QStyle::State_Selected)
    {
        role = QPalette::HighlightedText;
        painter->fillRect( view_option.rect, view_option.palette.highlight() );

    }
    else if (view_option.state & QStyle::State_MouseOver)
    {
        painter->fillRect(view_option.rect, view_option.palette.light());
    }
    else
    {
        painter->fillRect(view_option.rect, qvariant_cast<QBrush>(index.data(Qt::BackgroundRole)));
    }


    if (index.column() == 0)
    {
        QApplication::style()->drawItemText ( painter
                                              , rect
                                              , Qt::AlignLeft | Qt::AlignVCenter
                                              , QApplication::palette()
                                              , true
                                              , tScheduleItem.startAndEndRime()
                                              , role);
    }

    if (index.column() == 1)
    {
        QApplication::style()->drawItemText ( painter
                                              , rect
                                              , Qt::AlignLeft | Qt::AlignVCenter
                                              , QApplication::palette()
                                              , true
                                              , tScheduleItem.strContent
                                              , role);
    }
    if (index.column() == 2)
    {
        QStyleOptionButton checkBoxStyleOption;
        checkBoxStyleOption.state |= QStyle::State_Enabled;
        checkBoxStyleOption.state |= tScheduleItem.bUseAlarmClock? QStyle::State_On : QStyle::State_Off;
        checkBoxStyleOption.rect = checkBoxRect(option);

        QApplication::style()->drawControl(QStyle::CE_CheckBox,&checkBoxStyleOption,painter);

    }

    painter->save();
    painter->setPen(LINE_COLOR);
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->restore();
}

QSize CDailyScheduleDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 20);
}

QWidget *CDailyScheduleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 0)
    {
        CStartEndTimeEditor *editor = new CStartEndTimeEditor(parent);
        //connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
        return editor;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void CDailyScheduleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == 0)
    {
        T_ScheduleItem tScheduleItem = qvariant_cast<T_ScheduleItem>(index.data());
        CStartEndTimeEditor *pStartEndTimeEditor = qobject_cast<CStartEndTimeEditor *>(editor);
        pStartEndTimeEditor->setEndStartTime(tScheduleItem.strStartTime, tScheduleItem.strEndTime);
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void CDailyScheduleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == 0)
    {
        CStartEndTimeEditor *pStartEndTimeEditor = qobject_cast<CStartEndTimeEditor *>(editor);
        CDailyScheduleModel *pDailyScheduleModel = qobject_cast<CDailyScheduleModel *>(model);
        pDailyScheduleModel->setStartEndTimeData(index, pStartEndTimeEditor->startTime(), pStartEndTimeEditor->endTime());
    }
    else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

bool CDailyScheduleDelegate::editorEvent(QEvent *event, QAbstractItemModel *model
                                         , const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(index.column() == 2)
    {
        if((event->type() == QEvent::MouseButtonRelease) || (event->type() == QEvent::MouseButtonDblClick))
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() != Qt::LeftButton || !checkBoxRect(option).contains(mouseEvent->pos()))
            {
                return true;
            }
            if(event->type() == QEvent::MouseButtonDblClick)
            {
                return true;
            }
        }
        else if(event->type() == QEvent::KeyPress)
        {
            if(static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space && static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select)
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        T_ScheduleItem tScheduleItem = qvariant_cast<T_ScheduleItem>(index.data());
        bool checked = tScheduleItem.bUseAlarmClock;
        return model->setData(index, !checked, Qt::EditRole);
    }
    else
    {
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }
}

void CDailyScheduleDelegate::commitAndCloseEditor()
{
    //    StarEditor *editor = qobject_cast<StarEditor *>(sender());
    //    emit commitData(editor);
    //    emit closeEditor(editor);
}
