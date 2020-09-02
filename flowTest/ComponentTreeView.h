#ifndef CCOMPONENTTREEVIEW_H
#define CCOMPONENTTREEVIEW_H

#include <QTreeView>

class CComponentTreeModel;

class CComponentTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CComponentTreeView(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void performDrag(const QPoint & pt);

signals:

private:
    QPoint m_ptPress;
    CComponentTreeModel* m_pComponentTreeModel;

};

#endif // CCOMPONENTTREEVIEW_H
