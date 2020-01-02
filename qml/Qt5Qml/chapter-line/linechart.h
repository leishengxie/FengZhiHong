#ifndef LINECHART_H
#define LINECHART_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>

class LineChart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit LineChart(QQuickPaintedItem *parent = 0);
    void paint(QPainter *painter);
    Q_PROPERTY(QColor color READ color WRITE setColor)
    QColor color() const;
    void setColor(const QColor &color);
    Q_INVOKABLE void clearChart();

signals:
    void chartCleared();

public slots:

private:
    //QString m_name;
    QColor m_color;
    int monthCount;
    int nameWidth;
    int monthNow;
    int dayNow;
    int topDistance;//上部距离

};

#endif // LINECHART_H
