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

signals:
    void saveDairyfinished(const CDairy & dairySaveBefore, const CDairy & dairySaved);

protected:
    void closeEvent(QCloseEvent *event);//重写关闭事件

public slots:
    // 槽函数命名方式采用与qml一样的方式
    void onSave();
    void onCopy();

private slots:


private:
    Ui::CDairyEditWidget *ui;

};

#endif // DAIRYEDITWIDGET_H
