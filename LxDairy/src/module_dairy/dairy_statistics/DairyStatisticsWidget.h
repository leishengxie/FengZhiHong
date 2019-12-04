#ifndef DAIRYSTATISTICSWIDGET_H
#define DAIRYSTATISTICSWIDGET_H

#include <QWidget>
#include <QItemSelection>

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
    void showStatisticsByTag(const QString & strTag);
    void showStatisticsByDate(const QString & strYear, const QString & strMonth);

signals:
    // 打开id为did的日记
   void expandDairy(int did);

private slots:
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on_btnOpenDairy_clicked();

private:
    Ui::CDairyStatisticsWidget *ui;
};

#endif // DAIRYSTATISTICSWIDGET_H
