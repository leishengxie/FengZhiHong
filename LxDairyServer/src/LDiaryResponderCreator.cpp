#include "LDiaryResponderCreator.h"
#include <QMap>
#include <QString>
#include "LHttpRequest.h"
#include "LHttpResponse.h"
#include "IResponder.h"
#include "LHttpServer.h"
#include "responder/LDumpResponder.h"
#include "responder/LDefaultResponder.h"
#include "diary_responder/LJokeResponder.h"
#include "diary_responder/LLoginRigsterResponder.h"
#include "diary_responder/LDairyResponder.h"

#include <QTime>
#include "utils/LAsyncLogger.h"
#include "NetAppointments.h"

CLDiaryResponderCreator::CLDiaryResponderCreator()
{

}

IResponder* CLDiaryResponderCreator::service(CLHttpRequest *request, CLHttpResponse *resp)
{

    QByteArray path = request->getPath();
    qDebug("RequestMapper: path=%s", path.data());
    IResponder* pResponder = NULL;
    if (path.startsWith("/dump"))
    {
        pResponder = new CLDumpResponder(request, resp);

    }
    else if (path.startsWith(VIRTUAL_DIR_PATH_DAIRY_ROOT))
    {
        pResponder = new CLDairyResponder(request, resp);

    }
    else if (path.startsWith(VIRTUAL_DIR_PATH_JOKE_ROOT))
    {
        pResponder = new CLJokeResponder(request, resp);

    }
    else if (path.startsWith(VIRTUAL_DIR_PATH_REGISTER) || path.startsWith(VIRTUAL_DIR_PATH_LOGIN))
    {
        pResponder = new CLLoginRigsterResponder(request, resp);

    }
//    else if (path.startsWith("/template"))
//    {
//        TemplateController().service(request, response);
//    }
//    else if (path.startsWith("/form"))
//    {
//        FormController().service(request, response);
//    }
//    else if (path.startsWith("/file"))
//    {
//        FileUploadController().service(request, response);
//    }
//    else if (path.startsWith("/session"))
//    {
//        SessionController().service(request, response);
//    }
//    // All other pathes are mapped to the static file controller.
//    // In this case, a single instance is used for multiple requests.
    else
    {
        pResponder = new CLDefaultResponder(request, resp);

    }
//    qDebug("RequestMapper: finished request");
//    // Clear the log buffer
//    if (logger)
//    {
//       logger->clear();
//    }
    return pResponder;
}
