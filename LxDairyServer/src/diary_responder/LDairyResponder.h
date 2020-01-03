#ifndef CLDAIRYRESPONDER_H
#define CLDAIRYRESPONDER_H

#include "IResponder.h"

class CLDairyResponder : public IResponder
{
    Q_OBJECT
public:
    CLDairyResponder(CLHttpRequest* req, CLHttpResponse* resp);

    virtual int handle();

signals:

public slots:
};
#endif // CLDAIRYRESPONDER_H
