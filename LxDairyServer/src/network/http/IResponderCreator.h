#ifndef I_RESPONDER_CREATOR_H
#define I_RESPONDER_CREATOR_H

#include <QObject>


class CLHttpRequest;
class CLHttpResponse;
class IResponder;


class IResponderCreator
{

public:
    IResponderCreator();
    virtual ~IResponderCreator();

    //service
    virtual IResponder* service(CLHttpRequest *request, CLHttpResponse *resp) = 0;

    //virtual IResponderCreator* clone();


private:

};


#endif // I_RESPONDER_CREATOR_H
