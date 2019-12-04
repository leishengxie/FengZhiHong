#ifndef CDAIRYAPPSTATION_H
#define CDAIRYAPPSTATION_H

#include <QObject>
#include "Singleton.h"

///
/// \brief The CDairyAppStation class   全局中转站，由于qt信号槽类似观察者模式
///
class CDairyAppStation : public QObject, public CSingleton<CDairyAppStation>
{
    Q_OBJECT
public:
    CDairyAppStation();

signals:
    void bgPixmapChanged(const QPixmap & pixmap);
    void ttsSpeak(const QString &txt);
    void playMusic();

public slots:
};

#endif // CDAIRYAPPSTATION_H
