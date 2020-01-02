#ifndef QUDPCONNECT_H
#define QUDPCONNECT_H
#include <QObject>
#include <QUdpSocket>


class QUdpConnect : public  QObject
{

Q_OBJECT

public:
    QUdpConnect(QObject* pParent = 0);

signals:
	void sendMsg(QString strMsg, QString strFroom, unsigned int unType);


public slots:
 void sendDatagram();
 void recvDatagram();

private:
    QUdpSocket *udpSocket;
    QHostAddress strAddress;
};

#endif // QUDPCONNECT_H
