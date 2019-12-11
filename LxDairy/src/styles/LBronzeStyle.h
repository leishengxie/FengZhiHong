#ifndef _L_BRONZESTYLE_H
#define _L_BRONZESTYLE_H

#include <QProxyStyle>


// 青铜样式 --棕色、亮棕色、暗棕色等
class CLBronzeStyle : public QProxyStyle
{
    Q_OBJECT

public:
    CLBronzeStyle() {}

    // 以下三个函数在装载Style和卸载Style时调用,它可以是适当修改窗口部件和调色板
    void polish(QPalette &palette);
    void polish(QWidget *widget);
    void unpolish(QWidget *widget);


    int styleHint(StyleHint which, const QStyleOption *option,
                  const QWidget *widget = 0,
                  QStyleHintReturn *returnData = 0) const;

    int pixelMetric(PixelMetric which, const QStyleOption *option,
                    const QWidget *widget = 0) const;


    void drawPrimitive(PrimitiveElement which,
                       const QStyleOption *option, QPainter *painter,
                       const QWidget *widget = 0) const;

    // 画控件(窗口部件)
    // drawControl()函数被各种 QStyle 的子类重新实现，用于绘制 QPushButiön 和其他的一些简单的 窗口部件
    void drawControl(ControlElement element, // 要绘制的窗口部件的类型
                     const QStyleOption *option,
                     QPainter *painter,
                     const QWidget *widget) const;


    void drawComplexControl(ComplexControl which,
                            const QStyleOptionComplex *option,
                            QPainter *painter,
                            const QWidget *widget = 0) const;

    QRect subControlRect(ComplexControl whichControl,
                         const QStyleOptionComplex *option,
                         SubControl whichSubControl,
                         const QWidget *widget = 0) const;

public slots:
    // 获取用在用户界面上的标准图标。
    QIcon standardIconImplementation(StandardPixmap which,
                                     const QStyleOption *option,
                                     const QWidget *widget = 0) const;

private:
    void drawBronzeFrame(const QStyleOption *option,
                         QPainter *painter) const;
    void drawBronzeBevel(const QStyleOption *option,
                         QPainter *painter) const;
    void drawBronzeCheckBoxIndicator(const QStyleOption *option,
                                     QPainter *painter) const;
    void drawBronzeSpinBoxButton(SubControl which,
                                 const QStyleOptionComplex *option,
                                 QPainter *painter) const;
};

#endif // _L_BRONZESTYLE_H
