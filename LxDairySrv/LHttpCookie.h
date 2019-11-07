/**
  @file
  @author Stefan Frings
*/

#ifndef HTTPCOOKIE_H
#define HTTPCOOKIE_H

#include <QList>
#include <QByteArray>
#include "LHttpDef.h"

//在网络有时候需要用户登录才进一步操作，用户输入用户名密码登录后，浏览了几个页面，由于HTTP的无状态性，服务器并不知道用户有没有登录。
//    Cookie是解决HTTP无状态性的有效手段

//2.服务器发送cookie给客户端
// 从服务器端，发送cookie给客户端，是对应的Set-Cookie。包括了对应的cookie的名称，值，以及各个属性。
// 例如：
//Set-Cookie: lu=Rg3vHJZnehYLjVg7qi3bZjzg; Expires=Tue, 15 Jan 2013 21:47:38 GMT; Path=/; Domain=.169it.com; HttpOnly
//Set-Cookie: made_write_conn=1295214458; Path=/; Domain=.169it.com
//Set-Cookie: reg_fb_gate=deleted; Expires=Thu, 01 Jan 1970 00:00:01 GMT; Path=/; Domain=.169it.com; HttpOnly

//3.从客户端把cookie发送到服务器
// 从客户端发送cookie给服务器的时候，是不发送cookie的各个属性的，而只是发送对应的名称和值。
// 例如：
//GET /spec.html HTTP/1.1
//Host: www.example.org
//Cookie: name=value; name2=value2
//Accept: */*



class DECLSPEC HttpCookie
{
public:

    /** Creates an empty cookie */
    HttpCookie();

    /**
      Create a cookie and set name/value pair.
      @param name name of the cookie
      @param value value of the cookie
      @param maxAge maximum age of the cookie in seconds. 0=discard immediately
      @param path Path for that the cookie will be sent, default="/" which means the whole domain
      @param comment Optional comment, may be displayed by the web browser somewhere
      @param domain Optional domain for that the cookie will be sent. Defaults to the current domain
      @param secure If true, the cookie will be sent by the browser to the server only on secure connections
      @param httpOnly If true, the browser does not allow client-side scripts to access the cookie
    */
    HttpCookie( const QByteArray name
               , const QByteArray value
               , const int maxAge
               , const QByteArray path = "/"
            , const QByteArray comment = QByteArray()
            , const QByteArray domain = QByteArray()
            , const bool secure = false
            , const bool httpOnly = false);

    /**
      Create a cookie from a string.
      @param source String as received in a HTTP Cookie2 header.
    */
    HttpCookie(const QByteArray source);

    /** Convert this cookie to a string that may be used in a Set-Cookie header. */
    QByteArray toByteArray() const ;

    /**
      Split a string list into parts, where each part is delimited by semicolon.
      Semicolons within double quotes are skipped. Double quotes are removed.
    */
    static QList<QByteArray> splitCSV(const QByteArray source);

    /** Set the name of this cookie */
    void setName(const QByteArray name);

    /** Set the value of this cookie */
    void setValue(const QByteArray value);

    /** Set the comment of this cookie */
    void setComment(const QByteArray comment);

    /** Set the domain of this cookie */
    void setDomain(const QByteArray domain);

    /** Set the maximum age of this cookie in seconds. 0=discard immediately */
    void setMaxAge(const int maxAge);

    /** Set the path for that the cookie will be sent, default="/" which means the whole domain */
    void setPath(const QByteArray path);

    /** Set secure mode, so that the cookie will be sent by the browser to the server only on secure connections */
    void setSecure(const bool secure);

    /** Set HTTP-only mode, so that he browser does not allow client-side scripts to access the cookie */
    void setHttpOnly(const bool httpOnly);

    /** Get the name of this cookie */
    QByteArray getName() const;

    /** Get the value of this cookie */
    QByteArray getValue() const;

    /** Get the comment of this cookie */
    QByteArray getComment() const;

    /** Get the domain of this cookie */
    QByteArray getDomain() const;

    /** Get the maximum age of this cookie in seconds. */
    int getMaxAge() const;

    /** Set the path of this cookie */
    QByteArray getPath() const;

    /** Get the secure flag of this cookie */
    bool getSecure() const;

    /** Get the HTTP-only flag of this cookie */
    bool getHttpOnly() const;

    /** Returns always 1 */
    int getVersion() const;

private:

    QByteArray name;
    QByteArray value;
    QByteArray comment;
    QByteArray domain;  // 域，表示当前cookie所属于哪个域或子域下面。
    int maxAge;         // cookie的有效期
    //Expire time/Max-age：表示了cookie的有效期。expire的值，是一个时间，过了这个时间，该cookie就失效了。
    //或者是用max-age指定当前cookie是在多长时间之后而失效。
    //如果服务器返回的一个cookie，没有指定其expire time，那么表明此cookie有效期只是当前的session，即是session cookie，当前session会话结束后，就过期了。
    //对应的，当关闭（浏览器中）该页面的时候，此cookie就应该被浏览器所删除了。
    QByteArray path;    // cookie的所属路径。
    bool secure;        // 表示该cookie只能用https传输
    bool httpOnly;      // 表示此cookie必须用于http或https传输。这意味着，浏览器脚本，比如javascript中，是不允许访问操作此cookie的。
    int version;

};


#endif // HTTPCOOKIE_H
