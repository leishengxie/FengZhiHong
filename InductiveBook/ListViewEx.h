#ifndef CLISTVIEWEX_H
#define CLISTVIEWEX_H

#include <QListView>

class CListViewEx : public QListView
{
    Q_OBJECT
public:
    explicit CListViewEx(QWidget *parent = Q_NULLPTR);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void btnAddClicked();

public slots:

private:
    QRect m_rectAdd;
};

#endif // CLISTVIEWEX_H
