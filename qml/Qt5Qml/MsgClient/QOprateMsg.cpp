#include "QOprateMsg.h"
#include "ui_QOprateMsg.h"
#include "QUdpConnect.h"


QOprateMsg::QOprateMsg(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::QOprateMsg)
{
	ui->setupUi(this);
	m_pUdpConnect = new QUdpConnect();
	ui->editAddr->setPlaceholderText("192.168.5.21");
	ui->editContent->setPlaceholderText("hello");
	connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(onSendMsg()));
	connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(onDisconnect()));
}

QOprateMsg::~QOprateMsg()
{
	delete ui;
}

void QOprateMsg::onSendMsg()
{
	m_pUdpConnect->sendDatagram(ui->editAddr->text(), ui->editContent->text(), 1);
}

void QOprateMsg::onDisconnect()
{
	m_pUdpConnect->sendDatagram(ui->editAddr->text(),  ui->editContent->text(), 2);
	close();
}
