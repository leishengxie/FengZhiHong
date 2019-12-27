

#ifndef STAREDITOR_H
#define STAREDITOR_H

#include <QWidget>

///
/// \brief The CStarEditor class    五星评分控件, 支持小数
///
class CStarEditor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
public:
    CStarEditor(QWidget* parent = 0);

    static void drawFiveStarRating(QPainter* painter, const QRect & rect, const QPalette &palette
                                   , qreal dRating, bool bReadOnly = false);


    QSize sizeHint() const Q_DECL_OVERRIDE;

    qreal rating() const
    {
        return m_dRating;
    }
    void setRating(qreal dRating)
    {
        m_dRating = dRating;
        update();
    }

    int maxStarCount() const
    {
        return m_nMaxStarCount;
    }

    void setMaxStarCount(int maxStarCount)
    {
        m_nMaxStarCount = maxStarCount;
    }

    bool isReadOnly()
    {
        return m_bReadOnly;
    }

    void setReadOnly(bool bReadOnly)
    {
        m_bReadOnly = bReadOnly;
    }

signals:
    void editingFinished();
    void editingFinished(qreal dRating);

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:



private:
    // 评分
    qreal m_dRating;

    int m_nMaxStarCount;

    bool m_bReadOnly;

    bool bLeftMousePress;
    bool bDelegateEedit;    // 区分是qt 处于itemDelegate（需要鼠标点击进入编辑）还是单独的编辑控件

};


#endif
