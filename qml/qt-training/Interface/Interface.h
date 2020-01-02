#ifndef INTERFACE_H
#define INTERFACE_H
#include <QObject>

class Interface : public QObject
{
			Q_OBJECT
public:
	explicit Interface (QObject *parent = 0);

//	Q_PROPERTY(QString strMessage READ strMessage  NOTIFY strMessageChanged) // 消息索引

//	QString strMessage() const;

//signals:

//	void strMessageChanged();
};

#endif // INTERFACE_H
