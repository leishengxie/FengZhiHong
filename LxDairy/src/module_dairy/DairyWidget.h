#ifndef DAIRYWIDGET_H
#define DAIRYWIDGET_H

#include <QWidget>
#include <QItemSelection>
#include "Dairy.h"

namespace Ui {
class CDairyWidget;
}

class QMdiSubWindow;
class CLMusicPlayer;
class ITTS;
class QCloseEvent;

class CDairyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDairyWidget(QWidget *parent = 0);
    ~CDairyWidget();


    void saveDairy();
    void saveAllDairy();
    CLMusicPlayer* musicPlayer()
    {
        return m_pMusicPlayer;
    }

public slots:
    void slot_displayDairy(const CDairy &dairy);
    void onRequireExpand(const QModelIndex & index);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void slotUpdateMenu(QMdiSubWindow *pMdiSubWindow);

    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void onSaveDairyfinished(const CDairy & dairySaveBefore, const CDairy & dairySaved);

    void on_treeDairy_clicked(const QModelIndex &index);

    void on_btnOpenDairy_clicked();

    void on_listViewTag_clicked(const QModelIndex &index);

    void on_calendarWidget_clicked(const QDate &date);

    void on_btnTTSPlay_clicked();

    void on_btnPlayMusic_clicked();

private:
    Ui::CDairyWidget *ui;

    // 当前活动的日记
    CDairy m_dairyActive;
    CLMusicPlayer* m_pMusicPlayer;
    ITTS* m_pITTS;
};

#endif // DAIRYWIDGET_H
