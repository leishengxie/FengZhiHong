#ifndef CMINIWIDGET_H
#define CMINIWIDGET_H

#include "widgets/NoTitleMenuMainWidget.h"

class CMiniWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMiniWidget(QWidget *parent = nullptr);

public:
    void show(const QString & strText);
    QSize sizeHint() const;

signals:

protected:
    void paintEvent(QPaintEvent *event);
    virtual void enterEvent(QEvent *event);

    void mouseMoveEvent( QMouseEvent * event);
    void mousePressEvent( QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void changeEvent(QEvent *event);


private:
    QString m_strText;

    // 鼠标按下的位置
    QPoint m_ptMousePress;

    // 是否可以拖动窗口
    bool m_bCanDrag;

};

#endif // CMINIWIDGET_H
