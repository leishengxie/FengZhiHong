#ifndef CCHESSWIDGET_H
#define CCHESSWIDGET_H

#include "core/GobangGame.h"
#include <QWidget>

class QTimer;

QT_BEGIN_NAMESPACE
namespace Ui { class CGobangGameWidget; }
QT_END_NAMESPACE

class CGobangGameWidget : public QWidget, public CGobangGame
{
    Q_OBJECT

public:
    CGobangGameWidget(QWidget *parent = nullptr);
    ~CGobangGameWidget();

private slots:
    void on_btnStart_clicked();

    void on_btnTakeBackChess_clicked();

    void slotTimerSchedulerTimeOut();

protected:
    void paintEvent(QPaintEvent *event);

protected:
    // 派生类实现接口
    void drawBoard() {}
    void drawChesses() {}

private:
    Ui::CGobangGameWidget *ui;

    // 时间调度，用于指定裁判去执行相应的动作。
    QTimer* m_timerScheduler;

    // 背景图片
    QPixmap m_pixBg;
};
#endif // CCHESSWIDGET_H
