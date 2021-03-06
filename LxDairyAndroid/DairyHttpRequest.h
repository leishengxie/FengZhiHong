#ifndef CQMLHTTPREQUEST_H
#define CQMLHTTPREQUEST_H

#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include <QJSValueList>

class CDairyHttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit CDairyHttpRequest(QObject *parent = 0);

signals:

public slots:
//    void get(const QUrl& urlRequest, int nTimeout = 6000);
//    void post(const QUrl &urlRequest, const QByteArray &data, int nTimeout = 6000);

    /*Q_INVOKABLE */void login(QString strUserName, QString strPasswd, QJSValue jsCallback);
    void dairyList();
    void uploadDairy(int did, QString strTitle, QString strContent, QJSValue jsCallback);
    void deleteDairy(int did, QJSValue jsCallback);

private:
    QJSValue m_jsValue;
};

#endif // CQMLHTTPREQUEST_H
