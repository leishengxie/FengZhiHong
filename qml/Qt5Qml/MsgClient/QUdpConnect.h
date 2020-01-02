#ifndef QUDPCONNECT_H
#define QUDPCONNECT_H
#include <QUdpSocket>

class QTimer;
class QJsonDocument;


class QUdpConnect : public QObject
{
	Q_OBJECT
public:
	QUdpConnect(QObject *parent=0);

public slots:
	void sendDatagram(QString strAddr, QString strMsg, unsigned int unType);
	void recvDatagram();

private:
	QString getLocalIp();
private:
	QUdpSocket *udpSocket;
	QHostAddress strAddress;
	//QTimer *timer;

};

#endif // QUDPCONNECT_H
