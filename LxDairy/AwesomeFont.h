#ifndef CAWESOMEFONT_H
#define CAWESOMEFONT_H

#include <QObject>

class QLabel;
class QPushButton;

class CAwesomeFont : public QObject
{
    Q_OBJECT
public:
    explicit CAwesomeFont(QObject *parent = 0);

    void setIcon(QLabel* label, QChar ch, int nPoitSize = 10);
    void setIcon(QPushButton* btn, QChar ch, int nPoitSize = 10);

signals:

public slots:

private:
    void initFont();

private:
    static bool s_bInitFont;
    static QFont s_iconFont;
};

#endif // CAWESOMEFONT_H
