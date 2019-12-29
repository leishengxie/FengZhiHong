#include "LDairyService.h"
#include "filelogger.h"
#include "LHttpConfig.h"
#include "LHttpDef.h"
#include "LDiaryResponderCreator.h"
#include "LResponderFactory.h"
#include <QDir>
#include <QFile>

using namespace stefanfrings;

#define APPNAME         "LxDairyService"
#define ORGANISATION    "lx"                // Publisher of this application
#define DESCRIPTION     "Lx Dairy Service"  // Short description of the Windows service

// Logger class
FileLogger* logger;

///
/// \brief searchConfigFile Search the configuration file
/// \return
///
QString searchConfigFile()
{
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QString fileName(appName+".ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../../etc"); // for development without shadow build
    searchList.append(binDir+"/../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            // found
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Cannot find config file %s",qPrintable(fileName));
    return "";
}

void CLDairyService::start()
{
    // Initialize the core application
    QCoreApplication* app = application();
    app->setApplicationName(APPNAME);
    app->setOrganizationName(ORGANISATION);


    // Find the configuration file
    QString configFileName=searchConfigFile();

    // Configure logging into a file
    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat,app);
    logSettings->beginGroup("logging");
    logger=new FileLogger(logSettings,10000,app);
    logger->installMsgHandler();

    // 加载全局配置文件, 加载失败需要退出程序
    CLHttpServerConfig & config = CLHttpServerConfig::instance();
    if(!config.loadConfig(CONFIG_FILE_NAME))
    {
        return;
    }

    // 设置样本
    CLDiaryResponderCreator* pDiaryResponderCreator = new CLDiaryResponderCreator();
    CLResponderFactory::setCreatorSample(pDiaryResponderCreator);


    qDebug("CLDairyService: Starting service");

    // 启动服务线程
    serverThread = new CLWorkerHostThread<CLHttpServer>(0);
    serverThread->start();

    qWarning("CLDairyService: Service has started");
}

void CLDairyService::stop()
{
    // Note that this method is only called when the application exits itself.
    // It is not called when you close the window, press Ctrl-C or send a kill signal.

    serverThread->exit();
    serverThread->deleteLater();

    qWarning("Startup: Service has been stopped");
}


CLDairyService::CLDairyService(int argc, char *argv[])
    : QtService<QCoreApplication>(argc, argv, APPNAME)
{
    setServiceDescription(DESCRIPTION);
    setStartupType(QtServiceController::AutoStartup);
}

