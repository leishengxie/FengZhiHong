#ifndef I_RESPONDER_FACTORY_H
#define I_RESPONDER_FACTORY_H

#include <QObject>

class IResponderCreator;
class CLHttpRequest;
class CLHttpResponse;
class IResponder;

class CLResponderFactory : public QObject
{
    Q_OBJECT
public:
    explicit CLResponderFactory(QObject *parent = 0);
    ~CLResponderFactory();

    static void setCreatorSample(IResponderCreator* responderCreator);

    static IResponder *createResponder(CLHttpRequest *request, CLHttpResponse *resp);

signals:

public slots:

private:
    static IResponderCreator* s_pResponderCreator;
};

#endif // I_RESPONDER_FACTORY_H
