#ifndef CSHRINKWIDGET_H
#define CSHRINKWIDGET_H

#include <QWidget>

class CShrinkWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int fixSizeHeight READ fixSizeHeight WRITE setCusfixSizeHeight)
public:
    explicit CShrinkWidget(QWidget *parent = 0);

public:
    void setCusfixSizeHeight(int height)
    {
        setFixedHeight(height);
    }

    int fixSizeHeight()
    {
        return height();
    }

signals:

public slots:
};

#endif // CSHRINKWIDGET_H
