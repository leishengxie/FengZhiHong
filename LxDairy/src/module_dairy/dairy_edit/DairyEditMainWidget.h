#ifndef DAIRYEDITMAINWIDGET_H
#define DAIRYEDITMAINWIDGET_H

#include <QWidget>
#include "Dairy.h"

namespace Ui
{
    class CDairyEditMainWidget;
}

class QMdiSubWindow;

class CDairyEditMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CDairyEditMainWidget(QWidget* parent = 0);
    ~CDairyEditMainWidget();


    void saveDairy();
    void saveAllDairy();

    bool closeAllSubWindows();

public slots:
    void slot_displayDairy(const CDairy & dairy);
    void onMusicFinished();

signals:
    // 中转信号S1
    void saveDairyfinishedS1(const CDairy & dairySaveBefore, const CDairy & dairySaved);
    // 请求tts处理
    void requireTTSspeak(const QString & txt);
    // 请求播放音乐
    void requirePlayMusic();

private slots:
    void slotUpdateMenu(QMdiSubWindow* pMdiSubWindow);



    void on_btnTTSPlay_clicked();

    void on_btnPlayMusic_clicked();

private:
    Ui::CDairyEditMainWidget* ui;

    // 当前活动的日记
    CDairy m_dairyActive;
};

#endif // DAIRYEDITMAINWIDGET_H
