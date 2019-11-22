#ifndef CLISTVIEWEX_H
#define CLISTVIEWEX_H

#include <QListView>

///
/// \brief The CListViewEx class    画列表为空时列表的内容显示
///
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
