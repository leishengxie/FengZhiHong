#ifndef CSQLOPERATE_H
#define CSQLOPERATE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "Singleton.h"

#include "collection_jokebook/Joke.h"

///
/// \brief The CSqlOperate class mysql数据库操作
///
class CSqlOperate : public QObject, public CSingleton<CSqlOperate>
{
    Q_OBJECT
public:
    explicit CSqlOperate(QObject *parent = 0);

    // 连接数据库
    static bool connectSqlite(QString strDbName);
    static bool connectMySqDdatabase(QString strHostName, QString strDbName, QString strUserName, QString strPasswd, int port);

    // 创建表
     void createTable();

     bool saveUserUploadJoke(const T_Joke & tJoke);


public slots:

private:
    QSqlQuery query;
};

#endif // CSQLOPERATE_H
