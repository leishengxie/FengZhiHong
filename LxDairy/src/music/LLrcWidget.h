#ifndef CLLRCWIDGET_H
#define CLLRCWIDGET_H

#include <QObject>
#include <QWidget>
#include "LLrc.h"

///////QT多重继承的时候,要把QObject放在最前面,否则报错
///
/// \brief The CLLrcWidget class 歌词独立窗口，类似酷狗的歌词
///
class CLLrcWidget : public QWidget, public CLLrc
{
    Q_OBJECT
public:

//    enum E_WidgetType
//    {
//        E_InnerWidget,
//        E_DndependentWidget
//    };

    explicit CLLrcWidget(QWidget *parent = 0);

    void clearCurLrc();

    virtual QSize sizeHint() const;

signals:

public slots:
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 duration);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);



private slots:
    // 开始显示本句歌词
    void start();

    // 定时器更新本句歌词位置
    void onTimeOut();

    // 结束本句歌词显示
    void stop();

private:
    void init();

private:
    QLinearGradient m_linearGradient;
    QFont font;
    QTimer *m_pTimer;

    //
    QPoint m_ptOffset;

    QLinearGradient m_linearGradientMask;
    qreal m_dLrcMaskWidth;
    qreal m_dLrcMaskWidthInterval;


};

#endif // CLLRCWIDGET_H
