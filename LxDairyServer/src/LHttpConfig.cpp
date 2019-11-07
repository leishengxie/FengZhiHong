#include "LHttpConfig.h"
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include "utils/LAsyncLogger.h"
#include "utils/LLogger.h"
#include "LHttpDef.h"
#include <QFileSystemWatcher>


CLHttpServerConfig::CLHttpServerConfig(QObject *parent)
    : QObject(parent)
{
    // 监听文件变化,从而实现动态加载配置
    m_fileWatcher = new QFileSystemWatcher(this);
    connect(m_fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(onConfigFileChanged(QString)));
}

CLHttpServerConfig::~CLHttpServerConfig()
{
}

CLHttpServerConfig & CLHttpServerConfig::instance()
{
    static CLHttpServerConfig config;
    return config;
}

bool CLHttpServerConfig::loadConfig(const char *config)
{
    QString strConfig = config;
    if(!config || !QFile::exists(config))
    {
        strConfig = CONFIG_FILE_NAME;
    }

    if(!QFile::exists(strConfig))
    {
        aWarn()<<"HttpServerConfig::loadConfig failed: no "<< strConfig << endl;
        return false;
    }

    m_fileWatcher->addPath(strConfig);
    parseConfig(strConfig);
    return true;
}

void CLHttpServerConfig::onConfigFileChanged(const QString &path)
{
    aInfo() << "config changed " << path <<", reparse module options" << endl;
    parseConfig(path, true);
}

void CLHttpServerConfig::parseConfig(const QString &config, bool bPostEvent/*false*/)
{

    QSettings conf(config, QSettings::IniFormat);
    conf.beginGroup("server");
    m_address = QHostAddress::Any;
    QString strHost = conf.value("host", "").toString();
    if(!strHost.isEmpty() && !m_address.setAddress(strHost))
    {
        m_address = QHostAddress::LocalHost;
    }
    m_qu16Port = conf.value("port", 8080).toUInt();
    m_qu16MaxThreads = conf.value("worker_threads", 4).toUInt();
    m_nMaxConnections = conf.value("connections", 200).toInt();
    m_strDocumentRoot = conf.value("document_root", ".").toString();
    QString strAliases = conf.value("alias").toString();
    if(!strAliases.isEmpty())
    {
        QStringList aliasPairs = strAliases.split(";;");
        foreach(QString pair, aliasPairs)
        {
            int sep = pair.indexOf(',');
            if(sep != -1)
            {
                m_mapAlias.insert(pair.left(sep), pair.mid(sep+1));
            }
        }
    }
    QString strForbiddenPatterFile = conf.value("forbidden").toString();
    if(!strForbiddenPatterFile.isEmpty())
    {
        parseForbiddenPatters(strForbiddenPatterFile);
    }
    conf.endGroup();

}

void CLHttpServerConfig::parseForbiddenPatters(const QString &fileName)
{
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
        m_strlstForbiddenPatter.clear();
        QTextStream ts(&file);
        while(!ts.atEnd())
        {
            m_strlstForbiddenPatter.append(ts.readLine());
        }
    }
}
