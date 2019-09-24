#ifndef DAIRYEDITWIDGET_H
#define DAIRYEDITWIDGET_H

#include <QWidget>

#include "Dairy.h"

namespace Ui {
class CDairyEditWidget;
}

class CDairyEdit;

class CDairyEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDairyEditWidget(QWidget *parent = 0);
    explicit CDairyEditWidget(CDairy dairy, QWidget *parent = 0);
    ~CDairyEditWidget();

    SETGETCONST(int, did, Did)

    void init();

    CDairyEdit* dairyEdit();

protected:
    void closeEvent(QCloseEvent *event);//重写关闭事件

public slots:
    void slot_save();
    void slot_copy();

private:
    Ui::CDairyEditWidget *ui;
};

#endif // DAIRYEDITWIDGET_H