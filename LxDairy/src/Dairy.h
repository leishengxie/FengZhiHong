#ifndef CDAIRY_H
#define CDAIRY_H

#include <QObject>
#include "def/func.h"

#define FORMAT_DATETIME    "yyyy-MM-dd hh:mm:ss"

class CDairy : public QObject
{
    Q_OBJECT
public:
    explicit CDairy(QObject *parent = 0);

    SETGET(QString, strTitle, Title)
    SETGET(QString, strDateTime, DateTime)
    SETGET(QString, strWeather, Weather)
    SETGET(QString, strTag, Tag)
    SETGET(QString, strContent, Content)
signals:

public slots:


private:

};

#endif // CDAIRY_H
