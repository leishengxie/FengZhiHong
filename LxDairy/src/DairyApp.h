#ifndef CDAIRYAPP_H
#define CDAIRYAPP_H

#include <QApplication>
#include "UserInfo.h"

///
/// \brief The CDairyApp class CDairyApp应用的唯一实例，可以保持全局的一些对象
/// 我们在项目中为了保存一些全局性的数据，从QApplication派生了一个子类，
/// 并增加了一些新的方法来保存运行时的数据
///
class CDairyApp : public QApplication
{
    Q_OBJECT
public:
    explicit CDairyApp(int argc, char *argv[]);
    ~CDairyApp();

    bool notify(QObject *obj, QEvent *e);

    enum E_LoginType
    {
        EL_Local,
        EL_Net
    };

    static setUserInfoLocal(const T_UserInfo & tUserInfo);
    static setUserInfoNet(const T_UserInfo & tUserInfo);
    static T_UserInfo userInfoLocal();
    static T_UserInfo userInfoNet();
    static T_UserInfo userInfo();

signals:

public slots:

private:
    void init();

private:
    static E_LoginType s_eLoginType;
    static T_UserInfo s_tUserInfoLocal;
    static T_UserInfo s_tUserInfoNet;

};

#endif // CDAIRYAPP_H
