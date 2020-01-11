#ifndef CDAIRYAPP_H
#define CDAIRYAPP_H

#include <QApplication>
#include "UserInfo.h"

///
/// \brief The CDairyApp class CDairyApp应用的唯一实例，可以保持全局的一些对象
/// 我们在项目中为了保存一些全局性的数据，从QApplication派生了一个子类，
/// 并增加了一些新的方法来保存运行时的数据
///
class CDairyAndroidApp : public QApplication
{
    Q_OBJECT
public:
    // 这里是否出现了问题
     //CDairyAndroidApp(int argc, char *argv[]);
#ifdef Q_QDOC
    CDairyAndroidApp(int &argc, char **argv);
#else
    CDairyAndroidApp(int &argc, char **argv, int nQtVersion = ApplicationFlags);
#endif

    ~CDairyAndroidApp();

    //bool notify(QObject *obj, QEvent *e);



    static void setUserInfo(const T_UserInfo & tUserInfo);
    static T_UserInfo userInfo();

signals:

public slots:

private:
    void init();

private:
    static T_UserInfo s_tUserInfo;

};

#endif // CDAIRYAPP_H
