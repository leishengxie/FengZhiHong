#ifndef CLBASEWIDGET_H
#define CLBASEWIDGET_H

#include <QWidget>

class CSaveEvent;

class CLBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLBaseWidget(QWidget *parent = 0);


signals:

public slots:

protected:

    virtual bool event(QEvent *event);
    //void customEvent(QEvent *event);
    //重写的以上两个函数都可以处理自定义事件，可以二选一

    // 自定义来自action的事件
    virtual void actSaveEvent(){}
};

#endif // CLBASEWIDGET_H
