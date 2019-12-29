#ifndef CUSERINFO_H
#define CUSERINFO_H
#include <QObject>
#include <QDataStream>

///
/// \brief The T_UserInfo struct 用户信息表实体
///
struct T_UserInfo
{

    int uid;
    QString strNickName;

    T_UserInfo()
    {
        init();
    }

    void init()
    {
        uid = -1;
    }

    friend QDataStream & operator>>(QDataStream & in, T_UserInfo & data);
    friend QDataStream & operator<<(QDataStream & out, const T_UserInfo & data);
};

#endif // CUSERINFO_H
