#ifndef DAIRYEDITMAINWIDGET_H
#define DAIRYEDITMAINWIDGET_H

#include <QWidget>
#include "Dairy.h"

namespace Ui {
class CDairyEditMainWidget;
}

class QMdiSubWindow;

class CDairyEditMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDairyEditMainWidget(QWidget *parent = 0);
    ~CDairyEditMainWidget();


    void saveDairy();
    void saveAllDairy();

    bool closeAllSubWindows();

public slots:
    void slot_displayDairy(const CDairy &dairy);

private slots:
        void slotUpdateMenu(QMdiSubWindow *pMdiSubWindow);

        void onSaveDairyfinished(const CDairy & dairySaveBefore, const CDairy & dairySaved);

    void on_btnTTSPlay_clicked();

    void on_btnPlayMusic_clicked();

private:
    Ui::CDairyEditMainWidget *ui;

    // 当前活动的日记
    CDairy m_dairyActive;
};

#endif // DAIRYEDITMAINWIDGET_H
