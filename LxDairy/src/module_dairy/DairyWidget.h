#ifndef DAIRYWIDGET_H
#define DAIRYWIDGET_H

#include "LBaseWidget.h"
#include "Dairy.h"

namespace Ui {
class CDairyWidget;
}


class QCloseEvent;
class CDairyTagListModel;
class CDairyDateTreeModel;

class CDairyWidget : public CLBaseWidget
{
    Q_OBJECT

public:
    explicit CDairyWidget(QWidget *parent = 0);
    ~CDairyWidget();



public slots:

    void onRequireExpand(const QModelIndex & index);

protected:
    void closeEvent(QCloseEvent *event);
    void actSaveEvent();
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:



    void on_treeDairy_clicked(const QModelIndex &index);



    void on_listViewTag_clicked(const QModelIndex &index);

    void on_calendarWidget_clicked(const QDate &date);


private:
    Ui::CDairyWidget *ui;

    // model管理
    CDairyTagListModel* pDairyTagListModel;
    CDairyDateTreeModel* pDairyDateTreeModel;

};

#endif // DAIRYWIDGET_H
