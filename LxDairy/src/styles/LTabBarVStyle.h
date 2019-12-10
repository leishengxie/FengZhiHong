#ifndef CLTABBARVSTYLE_H
#define CLTABBARVSTYLE_H

#include <QProxyStyle>

///
/// \brief The CLTabVStyle class 自定QTabWidget的标题竖向显示不被颠倒
/// 调用方式ui->tabWidget->tabBar()->setStyle(new CLTabVStyle);
///
class CLTabBarVStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit CLTabBarVStyle(QStyle *style = Q_NULLPTR);

    QSize sizeFromContents(ContentsType type, const QStyleOption *option
                           , const QSize &size, const QWidget *widget) const;

    void drawControl(ControlElement element, const QStyleOption *option
                     , QPainter *painter, const QWidget *widget) const;
};

#endif // CLTABBARVSTYLE_H
