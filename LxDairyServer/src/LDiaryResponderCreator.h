#ifndef CLDIARYHANDLER_H
#define CLDIARYHANDLER_H

#include "IResponderCreator.h"


class CLDiaryResponderCreator : public IResponderCreator
{
public:
    CLDiaryResponderCreator();

    IResponder *service(CLHttpRequest *request, CLHttpResponse *resp);
};

#endif // CLDIARYHANDLER_H
