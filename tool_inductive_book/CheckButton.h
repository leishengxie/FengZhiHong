#ifndef CCHECKBUTTON_H
#define CCHECKBUTTON_H
#include <QWidget>

class CCheckButton : public QWidget
{
    Q_OBJECT
            Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
    Q_PROPERTY(QString text READ Text WRITE setText)
public:
    explicit CCheckButton(QWidget *parent = Q_NULLPTR);
    explicit CCheckButton(const QString &text, QWidget *parent = Q_NULLPTR);

signals:
    void clicked(bool bChecked);

public:
    bool isChecked()
    {
        return m_bCkecked;
    }

    void setChecked(bool bChecked)
    {
        m_bCkecked = bChecked;
        update();
    }

    QString Text()
    {
        return m_strText;
    }

    void setText(QString strText)
    {
        m_strText = strText;
        update();
    }

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    virtual QSize sizeHint() const;

private:
    void init();

private:
    QString m_strText;
    bool m_bCkecked;
    bool m_bMousePress;
};

#endif // CCHECKBUTTON_H
