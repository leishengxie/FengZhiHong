#ifndef RESPONDERMANAGER_H
#define RESPONDERMANAGER_H

#include <QObject>

#include "IResponder.h"
#include "LHttpConfig.h"

class CLHttpServer;
class CLHttpRequest;
class CLHttpResponse;


class CLResponderFactory : public QObject
{
    Q_OBJECT
public:
    CLResponderFactory(QObject *parent=Q_NULLPTR);

    static IResponder* createResponder(CLHttpRequest *request, CLHttpResponse *resp);
};


#endif // RESPONDERMANAGER_H
