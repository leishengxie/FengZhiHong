#ifndef DAIRYSTATISTICSWIDGET_H
#define DAIRYSTATISTICSWIDGET_H

#include <QWidget>
#include <QItemSelection>
#include "Dairy.h"

namespace Ui {
class CDairyStatisticsWidget;
}

class CDairyStatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDairyStatisticsWidget(QWidget *parent = 0);
    ~CDairyStatisticsWidget();

public slots:
    void showStatisticsByTag(const QString & strTag, const QList<T_Dairy> &lstDairy);
    void showStatisticsByDate(const QString & strYear, const QString & strMonth, const QList<T_Dairy> &lstDairy);


signals:
   void openDairyClicked(const T_Dairy & dairy);

private slots:
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on_btnOpenDairy_clicked();

private:
    Ui::CDairyStatisticsWidget *ui;
};

#endif // DAIRYSTATISTICSWIDGET_H
