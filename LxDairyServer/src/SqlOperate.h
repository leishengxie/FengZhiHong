#ifndef CSQLOPERATE_H
#define CSQLOPERATE_H

#include <QObject>
#include <QSqlDatabase>


///
/// \brief The CSqlOperate class mysql数据库操作
///
class CSqlOperate : public QObject
{
    Q_OBJECT
public:
    explicit CSqlOperate(QObject *parent = 0);

    static bool connect(QString strDbName);
    static void createTable();


public slots:
};

#endif // CSQLOPERATE_H
