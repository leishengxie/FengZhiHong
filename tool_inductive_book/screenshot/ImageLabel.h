#ifndef _IMAGE_LABEL_H
#define _IMAGE_LABEL_H

#include<QLabel>


// 同一时间只能存在一个绘制类型
enum E_DrawType
{
    ED_None,
    ED_Line,
    ED_Rectangle,
    ED_Round,
    ED_Arrow,
    ED_Text
};

struct T_DarwData
{
    E_DrawType eDrawType;
    QPoint ptStart;
    QPoint ptEnd;

    QString strText;

    T_DarwData()
    {

    }

    // ED_Line, ED_Rectangle, ED_Round, ED_Arrow
    T_DarwData(E_DrawType eDrawType, const QPoint & ptStart, const QPoint & ptEnd)
        : eDrawType(eDrawType)
        , ptStart(ptStart)
        , ptEnd(ptEnd)
    {

    }

    // ED_Text
    T_DarwData(E_DrawType eDrawType
               , const QPoint & ptStart
               , const QPoint & ptEnd
               , const QString & strText)
        : eDrawType(eDrawType)
        , ptStart(ptStart)
        , ptEnd(ptEnd)
        , strText(strText)
    {

    }
};

class QTextEdit;

class CImageLabel : public QLabel
{
    Q_OBJECT
public:

    CImageLabel(QWidget* parent);

    static void drawArrow(QPoint startpoint, QPoint endpoint, QPainter & p);

    void setDrawType(E_DrawType eDrawType);

    void setTextEditToVector();


    void setImageToLabel(const QImage & image);
    QImage resultImage();

public slots:
    void ontextchanged();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    QImage m_imageSelect;
    bool m_bPressed;
    QPoint m_ptStart;
    QPoint m_PtEnd;

    QVector<T_DarwData> m_vecDarwData;

    // 绘制文本额外需要
    QTextEdit* m_plaintextedit;


    E_DrawType m_eDrawType;


};

#endif // _IMAGE_LABEL_H
