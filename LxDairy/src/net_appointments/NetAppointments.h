#ifndef NET_APPOINTMENTS_H
#define NET_APPOINTMENTS_H

//#define APPOINTMENT_DATASTREAM
//#define APPOINTMENT_JSON
//#define APPOINTMENT_PROTOBUFF

#ifdef APPOINTMENT_DATASTREAM
    #include "datastream_type/NetDataStream.h"

    #include "collection_jokebook/Joke.h"
#endif

#ifdef APPOINTMENT_JSON
    #include "NetJson.h"
#endif

#ifdef APPOINTMENT_PROTOBUFF
    #include "NetProtobuff.h"
#endif

/////////////////////// 网络通信约定 //////////////////
#include <QDataStream>
#include <QByteArray>


extern const char * const VIRTUAL_DIR_PATH_REGISTER;
extern const char * const VIRTUAL_DIR_PATH_LOGIN;

extern const char * const VIRTUAL_DIR_PATH_JOKE_ROOT;
extern const char* const VIRTUAL_DIR_PATH_JOKE_UPLOAD;


struct T_NetAppointment
{
    enum E_RequsetType
    {
        ER_Get,
        ER_Post
    };

    T_NetAppointment();

    ///// url 组成 /////
    // 协议 --http: or https: 分隔号//
    QString strProtocol;

    // 域名 --名称或ip 分隔号:
    QString strDomainName;

    // 端口 --果省略端口部分，将采用默认端口
    int nPort;

    // 虚拟目录 --可选
    QString strVirtualDirectory;

    // 文件名部分 --可选
    QString strName;

    // 参数部分 --可选, 从“？”开始到“#”为止之间的部分为参数部分，又称搜索部分、查询部分。参数与参数之间用“&”作为分隔符
    QStringList strlstPrams;

    // 锚部分 --可选, 从最后一个“#”开始到最后，都是锚部分
    QString strAnchor;

    QString url();


    /////// 通讯接口函数 //////
    E_RequsetType eRequsetType;

    QByteArray byteBody;
};



class CNetAppointments
{
public:
    CNetAppointments();

    static QString urlRegister();
    static QString urlLogin();
    static QString urlUploadJoke();

    template<typename T>
    static QByteArray serializa(const T & t)
    {
        QByteArray byteArray;
        QDataStream out(&byteArray, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_6);
        out << t;
        return byteArray;
    }

    /// 当函数模板的返回值是模板类型参数时
    /// ，编译器无法通过函数调用来推断返回值的具体类型。此时，在调用函数时必须提供一个显式模板实参
    template<typename T>
    static T deserialization(const QByteArray & byteArray)
    {
        T t;
        QByteArray byteArrayTemp = byteArray;
        QDataStream in(&byteArrayTemp, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_6);
        in >> t;
        return t;
    }

    static void loadSetting();




public:
    static T_NetAppointment s_tNetAppointment;




};


/////////// 定义返回码-扩展 ///////////////////////
enum E_HttpStatusCode
{
    EH_Ok = 200,


    // 扩展
    EH_Ex_SystemError = 601,
    EH_Ex_AccountAlreadyExists,    // The account already exists
    EH_Ex_SqlError, // 数据库操作异常

    EH_Ex_AccountNotExists,
    EH_Ex_PasswdError
};

struct T_HttpStatusMsg
{
    T_HttpStatusMsg()
        : nStatusCode(EH_Ok)
        , strMsg("很好")
    {

    }

    int nStatusCode;
    QString strMsg;
};


#endif // NET_DEF_H
