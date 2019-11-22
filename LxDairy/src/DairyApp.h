#ifndef CDAIRYAPP_H
#define CDAIRYAPP_H

#include <QApplication>

class CDairyApp : public QApplication
{
    Q_OBJECT
public:
    explicit CDairyApp(int argc, char *argv[]);
    ~CDairyApp();

    bool notify(QObject *obj, QEvent *e);


signals:

public slots:
};

#endif // CDAIRYAPP_H
