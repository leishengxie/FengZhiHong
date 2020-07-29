#ifndef CJOKEDELEGATE_H
#define CJOKEDELEGATE_H

#include <QStyledItemDelegate>

class CDailyScheduleDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    CDailyScheduleDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);


private slots:
    void commitAndCloseEditor();
};

#endif // CJOKEDELEGATE_H
