#ifndef CUSER_H
#define CUSER_H

#include <QObject>

class CUser : public QObject
{
    Q_OBJECT
public:
    explicit CUser(QObject *parent = 0);

signals:

public slots:
};

#endif // CUSER_H