#ifndef __DAIRY_EDIT_H
#define __DAIRY_EDIT_H

#include <QTextEdit>
#include "Dairy.h"

class CDairyEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit CDairyEdit(QWidget *parent = 0);
    explicit CDairyEdit(CDairy dairy, QWidget *parent = 0);
    bool save();

    
signals:
    
public slots:



protected:
    void closeEvent(QCloseEvent *);//重写关闭事件

private slots:

private:
    void init();
    void contextMenuEvent(QContextMenuEvent *event);

    
};

#endif // __DAIRY_EDIT_H
