#ifndef CDAILYSCHEDULETABLEVIEW_H
#define CDAILYSCHEDULETABLEVIEW_H

#include "DailyScheduleBookModel.h"
#include <QTableView>

class CDailyScheduleModel;
class QMenu;

class CDailyScheduleTableView : public QTableView
{
    Q_OBJECT
public:
    explicit CDailyScheduleTableView(QWidget *parent = nullptr);

    void addItem();

public slots:
    void slotLoadBook(const T_DailyScheduleBook & book);

signals:

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void slotOrderByTime();
    void slotFixCrossItem();

private:
    CDailyScheduleModel* m_pDailyScheduleModel;
    QMenu *m_menu;

};

#endif // CDAILYSCHEDULETABLEVIEW_H
