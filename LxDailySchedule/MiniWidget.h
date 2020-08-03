#ifndef CMINIWIDGET_H
#define CMINIWIDGET_H

#include <QWidget>

class CMiniWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMiniWidget(QWidget *parent = nullptr);

public:
    void showText(const QString & strText);
    QSize sizeHint() const;

signals:

protected:
    void paintEvent(QPaintEvent *event);


private:
    QString m_strText;

};

#endif // CMINIWIDGET_H
