#ifndef CLBASEWIDGET_H
#define CLBASEWIDGET_H

#include <QWidget>

class CLBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CLBaseWidget(QWidget *parent = 0);


signals:

public slots:

protected:
    // 自定义来自action的事件
    virtual void actSaveEvent(){}
};

#endif // CLBASEWIDGET_H
