#include "LDairyApp.h"
//#include "filelogger.h"
#include "LHttpConfig.h"
#include "LHttpDef.h"
#include "LDiaryResponderCreator.h"
#include "LResponderFactory.h"
#include "SqlOperate.h"

//using namespace stefanfrings;

CLDairyApp::CLDairyApp(int &argc, char **argv)
    : QCoreApplication(argc, argv)
{

//    QSettings* logSettings=new QSettings("lxDairyLog",QSettings::IniFormat,app);
//    logSettings->beginGroup("logging");
//    logger=new FileLogger(logSettings,10000,app);
//    logger->installMsgHandler();

    // 连接数据库
    CSqlOperate::connectMySqDdatabase("localhost", "lxdairy", "root", "0406", 3306);


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
    serverThread = new CLWorkerHostThread<CLHttpServer>(this);
    serverThread->start();
}
