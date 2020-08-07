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


private:
    QString m_strText;

};

#endif // CMINIWIDGET_H
