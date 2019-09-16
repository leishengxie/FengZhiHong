#ifndef CDAIRY_H
#define CDAIRY_H

#include <QObject>

class CDairy : public QObject
{
    Q_OBJECT
public:
    explicit CDairy(QObject *parent = 0);

signals:

public slots:

private:
    QString strTitle;
    QString strDateTime;
    QString strWeather;
    QString strTag;
    QString strContent;
};

#endif // CDAIRY_H
