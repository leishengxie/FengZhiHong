#ifndef CLDAIRYAPP_H
#define CLDAIRYAPP_H

#include <QCoreApplication>
#include "LHttpServer.h"

class CLDairyApp : public QCoreApplication
{
    Q_OBJECT
public:

    CLDairyApp(int &argc, char **argv);

private:

    CLWorkerHostThread<CLHttpServer> *serverThread;
};

#endif // CLDAIRYAPP_H
