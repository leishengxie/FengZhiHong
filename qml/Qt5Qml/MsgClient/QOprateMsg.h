#ifndef QOPRATEMSG_H
#define QOPRATEMSG_H

#include <QWidget>

namespace Ui {
class QOprateMsg;
}

class QUdpConnect;

class QOprateMsg : public QWidget
{
	Q_OBJECT

public:
	explicit QOprateMsg(QWidget *parent = 0);
	~QOprateMsg();

private slots:
	void onSendMsg();
	void onDisconnect();

private:
	Ui::QOprateMsg *ui;
	QUdpConnect *m_pUdpConnect;
};

#endif // QOPRATEMSG_H
