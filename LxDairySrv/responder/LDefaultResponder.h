#ifndef CLDEFAULTRESPONDER_H
#define CLDEFAULTRESPONDER_H

#include "IResponder.h"


class CLDefaultResponder : public IResponder
{
    Q_OBJECT
public:
    CLDefaultResponder(CLHttpRequest* req, CLHttpResponse* resp);
    ~CLDefaultResponder();


    int prepare();

    ///
    /// \brief handle
    /// \return 0 - end; 1 - not end
    ///
    int handle();

};


#endif // CLDEFAULTRESPONDER_H
