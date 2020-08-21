#ifndef CLOGINWIDGET_H
#define CLOGINWIDGET_H

#include <QGraphicsView>

//class QGraphicsView;
//class QGraphicsWidget;

class CLoginWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CLoginWidget(QWidget *parent = nullptr);

private slots:
    void slot_rotate();

signals:


private:
    //QGraphicsView* m_pGraView;
    QGraphicsWidget *m_pGraWgtLogin;

};

#endif // CLOGINWIDGET_H
