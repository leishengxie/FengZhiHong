#include "LResponderFactory.h"
#include "IResponderCreator.h"

IResponderCreator* CLResponderFactory::s_pResponderCreator = NULL;

CLResponderFactory::CLResponderFactory(QObject *parent) : QObject(parent)
{

}

void CLResponderFactory::setCreatorSample(IResponderCreator *responderCreator)
{
    s_pResponderCreator = responderCreator;
}


IResponder* CLResponderFactory::createResponder(CLHttpRequest *request, CLHttpResponse *resp)
{
    IResponder* pResponder = NULL;
    if ( NULL == s_pResponderCreator)
    {
        return pResponder;
    }
    return s_pResponderCreator->service(request, resp);
}
