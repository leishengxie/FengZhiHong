#ifndef CMINIWIDGET_H
#define CMINIWIDGET_H

#include "widgets/NoTitleMenuMainWidget.h"
#include <QMediaPlayer>

class CMiniWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMiniWidget(QWidget *parent = nullptr);

public:
    QSize sizeHint() const;

public slots:
    void slot_show(const QString & strText);

signals:

protected:
    void paintEvent(QPaintEvent *event);
    virtual void enterEvent(QEvent *event);

    void mouseMoveEvent( QMouseEvent * event);
    void mousePressEvent( QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void changeEvent(QEvent *event);

private:
    void slot_mediaPlayerStateChanged(QMediaPlayer::State newState);

private:
    QString m_strText;

    // 鼠标按下的位置
    QPoint m_ptMousePress;

    // 是否可以拖动窗口
    bool m_bCanDrag;

    // 媒体播放器
    QMediaPlayer* m_pMediaPlayer;

};

#endif // CMINIWIDGET_H
