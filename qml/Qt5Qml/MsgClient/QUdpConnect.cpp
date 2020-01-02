#include "QUdpConnect.h"
#include <QTimer>
#include <iostream>
#include "CGlobal.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QNetworkInterface>

QUdpConnect::QUdpConnect(QObject *parent): QObject(parent)
{

    udpSocket = new QUdpSocket;
    //udpSocket -> bind(QHostAddress::LocalHost,4399);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(recvDatagram()));
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));
//    timer->start(1000);
}

void QUdpConnect::sendDatagram(QString strAddr, QString strMsg, unsigned int unType)
{
    QJsonObject json;
	json.insert("msg", strMsg);
	json.insert("from",getLocalIp());
	json.insert("msgType", (int)unType);

    QJsonDocument document;
    document.setObject(json);
    QByteArray datagram = document.toJson(QJsonDocument::Compact);
	udpSocket->writeDatagram(datagram.data(), datagram.size(),QHostAddress(strAddr), 33259);
}

void QUdpConnect::recvDatagram()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress strSenderIp;
        quint16 nPort;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &strSenderIp, &nPort);
        qDebug()<<tr("Received from ip: \"%1\" port: \"%2\", datagram: \"%3\"")
                  .arg(strSenderIp.toString(), QString::number(nPort), datagram.data());
    }
}

QString QUdpConnect::getLocalIp()
{
	QList <QHostAddress> list = QNetworkInterface::allAddresses();
	foreach(QHostAddress address, list)
	{
		if(address.protocol() == QAbstractSocket::IPv4Protocol &&
				address != QHostAddress::Null && address != QHostAddress::LocalHost)
		{
			if(address.toString().contains("127.0."))
			{
				continue;
			}
			return address.toString();
		}
	}
	return QString();
}
