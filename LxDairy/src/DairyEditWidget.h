#ifndef DAIRYEDITWIDGET_H
#define DAIRYEDITWIDGET_H

#include <QWidget>

#include "Dairy.h"

namespace Ui {
class CDairyEditWidget;
}

class CDairyEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDairyEditWidget(QWidget *parent = 0);
    explicit CDairyEditWidget(CDairy dairy, QWidget *parent = 0);
    ~CDairyEditWidget();

    SETGETCONST(int, did, Did)

private:
    Ui::CDairyEditWidget *ui;
};

#endif // DAIRYEDITWIDGET_H
