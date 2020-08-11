#ifndef __L_SQL_OPERATE_H
#define __L_SQL_OPERATE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "Singleton.h"

#include "DailyScheduleBookModel.h"

///
/// \brief The CSqlOperate class mysql数据库操作
///
class CDailyScheduleSqlOperate : public QObject, public CSingleton<CDailyScheduleSqlOperate>
{
    Q_OBJECT
public:
    explicit CDailyScheduleSqlOperate(QObject *parent = 0);


    bool connectSqlite(QString strDbName);

    void createTable();

    QList<T_DailySchedule> getDailyScheduleList();

    bool saveDailySchedule(const T_DailySchedule & tDailySchedule, QString &strError);

    // 由于表DailySchedule数据不重要，所以采用物理删除，而非逻辑删除。
    bool deleteDailySchedule(int id, QString &strError);


public slots:

private:
    QSqlDatabase m_db;
    QSqlQuery m_sqlQuery;
    QString m_strSql;

};

#endif // __L_SQL_OPERATE_H
