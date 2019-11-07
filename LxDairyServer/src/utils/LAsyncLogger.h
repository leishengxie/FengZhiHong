#ifndef _L_ASYNCLOG_H_
#define _L_ASYNCLOG_H_
#include <QObject>

class AsyncLoggerPrivate;

///
/// \brief The Async Logger
///
class AsyncLogger
{
private:
    AsyncLogger();
    AsyncLogger(const AsyncLogger &);
    AsyncLogger & operator =(const AsyncLogger &);

public:
    ~AsyncLogger();

    void loadConfig(QString strConfigPath);

    static AsyncLogger &getInstance();

    // 设置级别
    void setLogLevel(int level);

    // 日志过滤
    void addLogFilter(const QString &tag, int level);

    void debug();
    void info();
    void warn();
    void error();
    void flush();
    void tid();

    // 成员函数运算符重载
    AsyncLogger & operator<<(QChar t);
    AsyncLogger & operator<<(bool t);
    AsyncLogger & operator<<(char t);
    AsyncLogger & operator<<(signed short i);
    AsyncLogger & operator<<(unsigned short i);
    AsyncLogger & operator<<(signed int i);
    AsyncLogger & operator<<(unsigned int i);
    AsyncLogger & operator<<(signed long l);
    AsyncLogger & operator<<(unsigned long l);
    AsyncLogger & operator<<(qint64 i);
    AsyncLogger & operator<<(quint64 i);
    AsyncLogger & operator<<(float f);
    AsyncLogger & operator<<(double f);
    AsyncLogger & operator<<(const char * s);
    AsyncLogger & operator<<(const QString & s);
    AsyncLogger & operator<<(const QStringRef & s);
    AsyncLogger & operator<<(QLatin1String s);
    AsyncLogger & operator<<(const QByteArray & b);
    AsyncLogger & operator<<(const void * p);

private:
    AsyncLoggerPrivate *m_d;
};

//单目运算符重载
//格式：
//    全局函数：operator#(M)；
//    成员函数：M.operator#()

//4.2 双目运算符重载
//格式：
//    全局函数：operator#(L, R);
//    成员函数：L.operator#(R)


// 定义函数指针类型
typedef AsyncLogger & (*LPFN_AsyncLoggerFunction)(AsyncLogger &);

// 将运算符重载为全局函数时，形参中至少要有一个为自定义的数据类型，即不能全为基本数据类型
// 全局函数运算符重载
// 值得注意的是，‘+’ 用全局函数或成员函数都能实现重载；但 ‘<<’ 只能用全局函数实现重载。
inline AsyncLogger &operator << (AsyncLogger &s, LPFN_AsyncLoggerFunction f)
{
    return (*f)(s);
}

// 函数
AsyncLogger & endl(AsyncLogger &s);
AsyncLogger & flush(AsyncLogger &s);
AsyncLogger & debug(AsyncLogger &s);
AsyncLogger & info(AsyncLogger &s);
AsyncLogger & warn(AsyncLogger &s);
AsyncLogger & error(AsyncLogger &s);
AsyncLogger & tid(AsyncLogger &s);

#define aLog() AsyncLogger::getInstance()
#define aDebug() AsyncLogger::getInstance() << debug
#define aInfo() AsyncLogger::getInstance() << info
#define aWarn() AsyncLogger::getInstance() << warn
#define aError() AsyncLogger::getInstance() << error

//AsyncLogger* pAsyncLogger
//pAsyncLogger<<warn 会被解释成 operator<<(pAsyncLogger, warn)

#endif // _L_ASYNCLOG_H_
