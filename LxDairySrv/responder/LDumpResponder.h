#ifndef CLDUMPRESPONDER_H
#define CLDUMPRESPONDER_H

#include "IResponder.h"

class CLDumpResponder : public IResponder
{
    Q_OBJECT
public:
    CLDumpResponder(CLHttpRequest* req, CLHttpResponse* resp);

    virtual int handle();

signals:

public slots:
};

#endif // CLDUMPRESPONDER_H
