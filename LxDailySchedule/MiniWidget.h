#ifndef CMINIWIDGET_H
#define CMINIWIDGET_H

#include "DailyScheduleModel.h"
#include <QWidget>
#include <QMediaPlayer>

class CMiniWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMiniWidget(QWidget *parent = nullptr);

public:
    QSize sizeHint() const;

public slots:
    void slot_show(const T_ScheduleItem & tScheduleItem);
    void slot_timeout();

signals:

protected:
    void paintEvent(QPaintEvent *event);
    virtual void enterEvent(QEvent *event);

    void mouseMoveEvent( QMouseEvent * event);
    void mousePressEvent( QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void changeEvent(QEvent *event);

private slots:
    void slot_mediaPlayerStateChanged(QMediaPlayer::State newState);
    //void mediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    QString m_strText;

    // 鼠标按下的位置
    QPoint m_ptMousePress;

    // 是否可以拖动窗口
    bool m_bCanDrag;

    // 媒体播放器
    QMediaPlayer* m_pMediaPlayer;

    // 闹铃响的时候旋转头像
    QTimer *m_timer;
    unsigned int m_unAngle;

};

#endif // CMINIWIDGET_H
