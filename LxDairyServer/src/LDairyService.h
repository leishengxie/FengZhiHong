#ifndef CLDAIRYSERVICE_H
#define CLDAIRYSERVICE_H

#include <QtCore/QCoreApplication>
#include "qtservice.h"
#include "LHttpServer.h"


///
/// \brief The CLDairyService class: install and run the application as a windows service.
///
class CLDairyService : public QtService<QCoreApplication>
{
public:

    CLDairyService(int argc, char *argv[]);

protected:

    /** Start the service */
    void start();

    /**
      Stop the service gracefully.
      @warning This method is not called when the program terminates
      abnormally, e.g. after a fatal error, or when killed from outside.
    */
    void stop();

private:

    CLWorkerHostThread<CLHttpServer> *serverThread;
};


#endif // CLDAIRYSERVICE_H
