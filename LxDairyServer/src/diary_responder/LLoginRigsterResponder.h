#ifndef CLLOGINRIGSTERRESPONDER_H
#define CLLOGINRIGSTERRESPONDER_H

#include "IResponder.h"

class CLLoginRigsterResponder : public IResponder
{
    Q_OBJECT
public:
    CLLoginRigsterResponder(CLHttpRequest* req, CLHttpResponse* resp);

    virtual int handle();

signals:

public slots:
};
#endif // CLLOGINRIGSTERRESPONDER_H
