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

signals:
    // 请求tts处理 -中转S1
    void requireTTSspeakS1(const QString & txt);
    // 请求播放音乐 -中转S1
    void requirePlayMusicS1();
    void musicFinishedS1();

protected:
    void closeEvent(QCloseEvent *event);
    void actSaveEvent();
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:

    void onSaveDairyfinished(const CDairy & dairySaveBefore, const CDairy & dairySaved);

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
