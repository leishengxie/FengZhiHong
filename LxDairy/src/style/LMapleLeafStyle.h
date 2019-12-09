#ifndef CLMAPLELEAFSTYLE_H
#define CLMAPLELEAFSTYLE_H



#include <QProxyStyle>


class CLMapleLeafStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit CLMapleLeafStyle(QStyle *style = Q_NULLPTR);

    void polish(QPalette &palette);
    void polish(QWidget *widget);
    void unpolish(QWidget *widget);

    int styleHint(StyleHint which, const QStyleOption *option,
                  const QWidget *widget = 0,
                  QStyleHintReturn *returnData = 0) const;

    int pixelMetric(PixelMetric which, const QStyleOption *option,
                    const QWidget *widget = 0) const;


    void drawPrimitive(PrimitiveElement which, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;

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

    QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *opt
                           , const QWidget *widget = Q_NULLPTR) const Q_DECL_OVERRIDE;

    QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *option = Q_NULLPTR
            , const QWidget *widget = Q_NULLPTR) const Q_DECL_OVERRIDE;

signals:

public slots:

protected:
    bool event(QEvent *e);

private:
    void drawPECheckBoxIndicator(const QStyleOption *option, QPainter *painter) const;
    void drawPERadioButtonIndicator(const QStyleOption *option, QPainter *painter) const;
    void drawPEArrowDownIndicator(const QStyleOption *option, QPainter *painter) const;
    void drawPEPanelButtonCommand(const QStyleOption *option, QPainter *painter) const;

private:
    static void setTexture(QPalette &palette, QPalette::ColorRole role, const QPixmap &pixmap);
    static QPainterPath roundRectPath(const QRect &rect);


};

#endif // CLMAPLELEAFSTYLE_H
