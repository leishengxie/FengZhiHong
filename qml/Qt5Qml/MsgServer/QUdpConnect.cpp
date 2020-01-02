
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include "QUdpConnect.h"
#include <iostream>

QUdpConnect::QUdpConnect(QObject *pParent) : QObject(pParent)
{
    strAddress = QHostAddress("192.168.5.21");
    udpSocket = new QUdpSocket;
    udpSocket->bind(QHostAddress(strAddress), 4399, QUdpSocket::ShareAddress);
    QObject::connect(udpSocket,SIGNAL(readyRead()),this,SLOT(recvDatagram()));
    qDebug() << "udp init completed";
}


void QUdpConnect::sendDatagram()
{
    QByteArray datagram = "192.168.5.149|CallService|0|GetIpByRoomCode|29008";
    udpSocket->writeDatagram(datagram.data(), datagram.size(),QHostAddress("192.168.5.211"), 4399);
}

void QUdpConnect::recvDatagram()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress strSenderIp;
        quint16 nPort;
        //
        udpSocket->readDatagram(datagram.data(), datagram.size(), &strSenderIp, &nPort);

        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(datagram, &json_error);
        if (json_error.error == QJsonParseError::NoError)
        {
            if (parse_doucment.isObject())
            {
                QString strMsg;
                QString strFrom;
				unsigned int msgType;
                QJsonObject obj = parse_doucment.object();
                if (obj.contains("msg"))
                {
                    QJsonValue jsonMsg = obj["msg"];
                    if (jsonMsg.isString())
                    {
                        strMsg = jsonMsg.toString();
                        QString ff("说到底发生");
                        qDebug() << strMsg << ff;
                    }
                }
                if (obj.contains("from"))
                {
                    QJsonValue jsonFrom = obj.take("from");
                    if (jsonFrom.isString())
                    {
                        strFrom = jsonFrom.toString();
                    }
                }
				if (obj.contains("msgType"))
				{
					QJsonValue jsonFrom = obj.take("msgType");
					msgType = jsonFrom.toInt();
				}
                qDebug() << strMsg << strFrom;
				emit sendMsg(strMsg, strFrom, msgType);
            }
        }
    }

}
