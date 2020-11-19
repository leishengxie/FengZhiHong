#ifndef CLSORTBUTTON_H
#define CLSORTBUTTON_H

#include <QWidget>

class CLSortButton : public QWidget
{
    Q_OBJECT
public:
    enum E_SortType
    {
        ES_Up,
        ES_Down
    };
    explicit CLSortButton(const QPixmap &pixUp, const QPixmap &pixDown, QWidget *parent = nullptr);
    explicit CLSortButton(QWidget *parent = nullptr);
    ~CLSortButton();

    QSize sizeHint() const;
    void setPixmap(const QPixmap &pixUp, const QPixmap &pixDown);

signals:
    void clicked(E_SortType eSortType);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void init();

private:
    QPixmap* m_pixUp;
    QPixmap* m_pixDown;
    E_SortType m_eSortType;
    bool m_bPressed;
};

#endif // CLSORTBUTTON_H
