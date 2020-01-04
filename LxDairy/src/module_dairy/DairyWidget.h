#ifndef DAIRYWIDGET_H
#define DAIRYWIDGET_H

#include "LBaseWidget.h"
#include "Dairy.h"

namespace Ui {
class CDairyWidget;
}


class QCloseEvent;


class CDairyWidget : public CLBaseWidget
{
    Q_OBJECT

public:
    enum E_PageIndex
    {
        EP_Dairy,
        EP_Statistics
    };

    explicit CDairyWidget(QWidget *parent = 0);
    ~CDairyWidget();

    void saveAllDairy();


signals:
    // 请求tts处理 -中转S1
    void requireTTSspeakS1(const QString & txt);
    // 请求播放音乐 -中转S1
    void requirePlayMusicS1();
    void musicFinishedS1();

public:
    void requestDairyList(const T_DairyListRequest &tDairyListRequest, bool bAppend = false);

protected:
    void closeEvent(QCloseEvent *event);
    void actSaveEvent();
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:

    void on_calendarWidget_clicked(const QDate &date);

private:
    void init();


private:
    Ui::CDairyWidget *ui;




};

#endif // DAIRYWIDGET_H
