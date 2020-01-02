#ifndef CLABEL_H
#define CLABEL_H
#include <QLabel>

class QClickLabel:public QLabel
{
public:
    QClickLabel();

    Q_OBJECT
public:
    explicit QClickLabel(QWidget *parent=0);
    explicit QClickLabel(QWidget *parent=0, Qt::WindowFlags f=0);
    explicit QClickLabel(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);

private:
protected:
    virtual void mouseReleaseEvent(QMouseEvent *ev);
signals:
    void clicked(void);
};

#endif // CLABEL_H
