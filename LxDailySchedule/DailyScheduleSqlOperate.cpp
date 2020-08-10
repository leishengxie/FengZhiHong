#include "DailyScheduleSqlOperate.h"
#include<QVariant>
#include<QCoreApplication>
#include<QDir>
#include<QPixmap>
#include<QDebug>
#include <QSqlQuery>
#include <QSqlError>

//#include <time.h>




CDailyScheduleSqlOperate::CDailyScheduleSqlOperate(QObject* parent) : QObject(parent)
{


}

bool CDailyScheduleSqlOperate::connectSqlite(QString strDbName)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(strDbName);
    if ( !m_db.open())
    {
        return false;
    }
    //    QSqlQuery query;
    //    query.exec("create table zhanghao (zhanghao int primary key,mima varchar,"
    //               "wangming varchar,qianming varchar,beizhu varchar,touxiang varcher,"
    //               "ziti varcher,beijing varcher)");
    //    query.exec("create table mobile (zhanghao int ,time varchar,wather varchar,xinqing varchar,neirong varcher)");
    m_sqlQuery = QSqlQuery();
    return true;
}

///
/// \brief CDailyScheduleSqlOperate::createTable
/// 思考：由于本应用界面操作只有保存 T_DailySchedule， 而T_ScheduleItem的单项操作不提交到数据库，即添加，删除T_ScheduleItem
/// 不会提交到数据库，所以把T_ScheduleItem转换成二进制数据作为tDailySchedule表的一个字段使用，而不单独创建tScheduleItem，这样可以
///  一个 数据表 就可以了
///

void CDailyScheduleSqlOperate::createTable()
{

    // 增加content_data 20200809
    m_sqlQuery.clear();
    m_strSql = "CREATE TABLE IF NOT EXISTS tDailySchedule(" \
             "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1," \
             "name TEXT," \
             "create_date_time TEXT, " \
             "content_data blob)";
    if (!m_sqlQuery.exec(m_strSql))
    {
        qDebug() << m_sqlQuery.lastError();
    }

///改进，不需要tScheduleItem表了
//    m_strSql = "CREATE TABLE IF NOT EXISTS tScheduleItem(" \
//             "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL DEFAULT 1," \
//             "schedule_id INTEGER NOT NULL," \
//             "start_time TEXT," \
//             "end_time  TEXT," \
//             "content TEXT," \
//             "use_alarm_clock INTEGER)";
//    if (!m_sqlQuery.exec(m_strSql))
//    {
//        qDebug() << m_sqlQuery.lastError();
//    }

}



QList<T_DailySchedule> CDailyScheduleSqlOperate::getDailyScheduleList()
{
    QSqlQuery query;
    QList<T_DailySchedule> lstDailySchedule;
    query.exec("select * from tDailySchedule");
    while (query.next())
    {
        T_DailySchedule tDailySchedule;
        tDailySchedule.id = query.value("id").toInt();
        tDailySchedule.strScheduleName = query.value("name").toString();
        tDailySchedule.strCreateDateTime = query.value("create_date_time").toString();
        tDailySchedule.deserializationScheduleItemList(query.value("content_data").toByteArray());
        lstDailySchedule.append(tDailySchedule);
    }
    return lstDailySchedule;
}

bool CDailyScheduleSqlOperate::saveDailySchedule(const T_DailySchedule &tDailySchedule, QString & strError)
{
    QSqlQuery query;
    if (tDailySchedule.isNew())
    {
        //m_db.transaction();
        bool ok = query.prepare("INSERT INTO tDailySchedule(name, create_date_time, content_data) VALUES (?, ?, ?)");
        query.bindValue(0, tDailySchedule.strScheduleName);
        query.bindValue(1, tDailySchedule.strCreateDateTime);
        query.bindValue(2, tDailySchedule.serializaScheduleItemList());
        ok = query.exec();
        if (!ok)
        {
            strError = query.lastError().text();
            return false;
        }


//        QVariantList var_list_start_time, var_list_end_time, var_list_content, var_list_UseAlarmClock;
//        foreach(T_ScheduleItem tScheduleItem, tDailySchedule.lstScheduleItem)
//        {
//            var_list_start_time << tScheduleItem.strStartTime;
//            var_list_end_time << tScheduleItem.strEndTime;
//            var_list_content << tScheduleItem.strContent;
//            var_list_UseAlarmClock << tScheduleItem.bUseAlarmClock;

//        }
//        query.execBatch();

        /// QT SQLITE使用事务批量插入数据
        /***************

        方法一，批处理方式：
         dbT1.transaction();	 	//开始启动事务
           inQry.prepare("insert into datatable values (?,?,?)");
           while(!ReadDat.atEnd())
           {
               strTextData = ReadDat.readLine();
               listIndex << datIndex;
               tmStamp << tmStampCnt;
               dtData << strTextData;
               datIndex++;
               DatWin->append(strTextData);
           }
           //绑定数据，顺序应与表结构字段数据一致
           inQry.addBindValue(listIndex);	//绑定数据
           inQry.addBindValue(tmStamp);		//绑定数据
           inQry.addBindValue(dtData);		//绑定数据
           inQry.execBatch();		//进行批处理操作
           dbT1.commit();		//提交事务，此时打开数据库文件执行SQL语句

           //不加下面三句，重复操作上面语句时，数据库不会有新的添加
           //因为作为主键的listIndex内有原数据，此时数据库不会保存主键值重复的内容
           listIndex.clear();
           tmStamp.clear();
           dtData.clear();



        方法二，占位符方式：
           dbT1.transaction();
           while(!ReadDat.atEnd())
           {
               strTextData = ReadDat.readLine();
               inQry.prepare("insert into datatable(tIndex, tTimStamp, tDistance)"
                                 "values(:tIndex, :tTimStamp, :tDistance)");
                inQry.bindValue(0,datIndex);
                inQry.bindValue(1,tmStampCnt);
                inQry.bindValue(2,strTextData);
                inQry.exec();
                datIndex++;
                DatWin->append(strTextData);
           }
           dbT1.commit();
        */
    }
    else
    {


        m_strSql = "update tDailySchedule set name = :name, content_data = :content_data where id = :id";
        query.prepare(m_strSql);
        query.bindValue(":name", tDailySchedule.strScheduleName);
        query.bindValue(":content_data", tDailySchedule.serializaScheduleItemList());
        query.bindValue(":id", tDailySchedule.id);
        //注意：执行了prepare后，exec里不要再加入语句了
        //bool ok = query.exec(m_strSql);
        bool ok = query.exec();
        if (!ok)
        {
            strError = query.lastError().text();
            return false;
        }
    }
    return true;
}



