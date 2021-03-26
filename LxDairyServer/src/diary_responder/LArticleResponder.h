#ifndef __JOKE_RESPONDER_H
#define __JOKE_RESPONDER_H

#include "IResponder.h"

class CLArticleResponder : public IResponder
{
    Q_OBJECT
public:
    CLArticleResponder(CLHttpRequest* req, CLHttpResponse* resp);

    virtual int handle();

signals:

public slots:
};

#endif // __JOKE_RESPONDER_H
