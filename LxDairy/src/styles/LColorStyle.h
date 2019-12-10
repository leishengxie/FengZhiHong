#ifndef CLCOLORSTYLE_H
#define CLCOLORSTYLE_H

#include <QProxyStyle>

class CLColorStyle : public QProxyStyle
{
    Q_OBJECT
public:
    explicit CLColorStyle(QStyle *style = Q_NULLPTR);

    void polish(QPalette &palette);
    void polish(QWidget *widget);
    void unpolish(QWidget *widget);


signals:

public slots:

};

#endif // CLCOLORSTYLE_H
