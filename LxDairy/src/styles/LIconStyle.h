#ifndef _L_ICON_STYLE_H
#define _L_ICON_STYLE_H

#include <QCommonStyle>

// 参考Qt源码, qfunsionstyle
//QStyle优点：

//统一风格。特定类型的控件效果都统一,如果要多处用到同一种类型的控件，用QStyle会比较方便。
//QStyle缺点:
//实现涉及Qt GUI控件结构细节，涉及知识面太多太杂。
//只有Qt控件使用了QStyle，系统及第三方实现的控件不保证有效。
//实现起来太复杂，不如重写QWidget的paintEvent配合其他事件来实现灵活

/**@brief 定制菜单style
 *
    void drawControl(ControlElement control, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget) const;

    int pixelMetric ( PixelMetric pm, const QStyleOption * opt, const QWidget * widget) const;
*/
// QProxyStyle实现了QStyle所有的抽象接口,并且默认保持系统风格


//根据QT4文档的说明，windows下支持 "windows", "motif", "cde", "plastique" and "cleanlooks"
//而QT5文档说明，windows下只支持 "windows" and "fusion"
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    QStringList keyList = QStyleFactory::keys();

//        for(int i = 0; i < keyList.length(); i++)
//        {
//            qDebug(keyList.at(i).toUtf8());
//        }


//    //QApplication::setStyle(QStyleFactory::create("fusion"));
//    //QApplication::setStyle(QStyleFactory::create("Windows"));
//    //QApplication::setStyle(QStyleFactory::create("WindowsXP"));
//    QApplication::setStyle(QStyleFactory::create("WindowsVista"));
class CLIconStyle : public QCommonStyle
{
    Q_OBJECT

public:
    CLIconStyle();
    ~CLIconStyle();

    void setCustomSize(int);

    //protected:
    virtual int pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const;

private:
    int mSize;
};


#endif // _L_ICON_STYLE_H
