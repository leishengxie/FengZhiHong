
#include <signal.h>
#include <QSettings>

#ifdef QT_NO_DEBUG
#include "LDairyService.h"
#include <QDir>
#else
#include "LDairyApp.h"
#endif


///
/// \brief 信号处理函数
/// \param sig_num
///
static void signal_handler(int sig_num)
{
    switch(sig_num)
    {
#ifndef WIN32
    case SIGQUIT:
    case SIGSTOP:
    case SIGHUP:
#endif
    case SIGTERM:
    case SIGABRT:
        fprintf(stdout, "exit by signal %d\n", sig_num);
        fflush(stdout);
        exit(2);
        break;
    case SIGFPE:
    case SIGSEGV:
    case SIGILL:
        fprintf(stdout, "exit by error %d\n", sig_num);
        fflush(stdout);
        exit(1);
        break;
    }
}


///
/// \注册信号处理函数
///
static void register_signal()
{
#ifndef WIN32
    struct sigaction sigact;
    sigact.sa_handler = signal_handler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;

    sigaction(SIGHUP, &sigact, NULL);   //发送给具有Terminal的Controlling Process，当terminal 被disconnect时候发送
    sigaction(SIGQUIT, &sigact, NULL);  //输入Quit Key的时候（CTRL+\）发送给所有Foreground Group的进程
    sigaction(SIGINT, &sigact, NULL);   //由Interrupt Key产生，通常是CTRL+C或者DELETE。发送给所有ForeGround Group的进程
    sigaction(SIGTERM, &sigact, NULL);  //请求中止进程，kill命令缺省发送
    sigaction(SIGABRT, &sigact, NULL);  //由调用abort函数产生，进程非正常退出
    sigaction(SIGFPE, &sigact, NULL);   //数学相关的异常，如被0除，浮点溢出，等等
    sigaction(SIGSEGV, &sigact, NULL);  //非法内存访问
    sigaction(SIGILL, &sigact, NULL);   //非法指令异常

    /* ignore SIGPIPE, this signal will be triggered when remote close socket abnormally */
    sigact.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &sigact, NULL);  //在reader中止之后写Pipe的时候发送
#else
    signal(SIGTERM, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGFPE, signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGILL, signal_handler);
#endif
}


//-i -install 安装服务。
//-u -uninstall 卸载服务。
//-e -exec 作为独立应用程序执行。
//-t -terminate 停止服务。
//-p -pause 暂停服务。
//-r -resume 恢复暂停的服务。
//-c cmd --command cmd 将用户定义的命令代码cmd发送到服务应用程序。
//-v -version 显示版本和状态信息。
// 具体看代码
int main(int argc, char *argv[])
{
    // 注册信号处理函数
    //register_signal();

#ifdef QT_NO_DEBUG

#if !defined(Q_WS_WIN)
    // QtService stores service settings in SystemScope, which normally require root privileges.
    // To allow testing this example as non-root, we change the directory of the SystemScope settings file.
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, QDir::tempPath());
    qWarning("(Example uses dummy settings file: %s/QtSoftware.conf)", QDir::tempPath().toLatin1().constData());
#endif // Q_WS_WIN

    CLDairyService service(argc, argv);
    return service.exec();

#else

    CLDairyApp a(argc, argv);
    return a.exec();

#endif //QT_NO_DEBUG



}
