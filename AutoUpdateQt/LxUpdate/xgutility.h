/******************************************************************************
**
** @file
** xgutility.h
** @brief
** 跨平台系统函数封装
** @par
** 不支持多线程，未处理C++异常
** @author
** panxf
** @date
** 2016-8-17
******************************************************************************/

#ifndef __XG_UTILITY_H__
#define __XG_UTILITY_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <string>
#include <map>

#if !defined(_MSC_VER)
  #include <unistd.h>
  #include <ext/pool_allocator.h>

#elif _MSC_VER >= 1300
  #define snprintf _snprintf
  #define atoll _atoi64
  #define strcasecmp _stricmp
  #define strncasecmp _strnicmp

#endif

#ifdef WIN32
  #include <windows.h>
  #include <process.h>
  #include <tchar.h>

  #if defined(__GNUC__) && __GNUC__ < 5 // mingw 4.x
    int P_strnicmp (const char*, const char*, size_t);
    #define strncasecmp P_strnicmp
  #endif

  #define THREADRETURN unsigned __stdcall
  typedef unsigned (__stdcall *THREAD_FUN)(void*);

  #define DIR_SEP '\\' // 路径分隔符

#else
  #include <errno.h>
  #include <time.h>
  #include <pthread.h>
  #include <sys/stat.h>
  #include <sys/time.h>

  typedef void* THREADRETURN;
  typedef THREADRETURN (*THREAD_FUN)(void*);

  typedef unsigned char UCHAR;
  typedef unsigned char BYTE;
  typedef unsigned short WORD;
  typedef int BOOL;
  typedef unsigned int UINT;
  typedef unsigned long DWORD;
  typedef unsigned long ULONG;
  typedef const char* LPCSTR;
  typedef long long LONGLONG;
  typedef unsigned long long ULONGLONG;

  #define TRUE 1
  #define FALSE 0

  #define DIR_SEP '/' // 路径分隔符

#endif // WIN32



namespace xgKtv {

///
/// @par 功能
/// 重载Windows系统函数GetTickCount()
/// @return - 系统毫秒计数
/// @note
/// Windows下技术是从程序启动开始计数，linux下是系统启动开始计数
///
inline UINT GetTickCount()
{
#ifdef WIN32
	static LARGE_INTEGER s_tStart = { {0, 0} };
	static LARGE_INTEGER s_tFrequency = { {0, 0} };
	static LARGE_INTEGER s_tHalfFreq = { {0, 0} };

	if (0 == s_tStart.QuadPart)
	{
		QueryPerformanceCounter(&s_tStart);
		s_tStart.QuadPart -= 10000000;
		QueryPerformanceFrequency(&s_tFrequency);
		s_tHalfFreq.QuadPart = s_tFrequency.QuadPart / 2;
	}

	LARGE_INTEGER tCurrent;
	QueryPerformanceCounter(&tCurrent);
	tCurrent.QuadPart -= s_tStart.QuadPart;

	// 四舍五入的计算方法
	return (UINT)((tCurrent.QuadPart * 1000 + s_tHalfFreq.QuadPart) / s_tFrequency.QuadPart);
#else
	timespec tTimeSpec;
	clock_gettime(CLOCK_MONOTONIC, &tTimeSpec);
	return (UINT)(tTimeSpec.tv_sec * 1000) + (UINT)(tTimeSpec.tv_nsec / 1000000);
#endif
}

///
/// @par 功能
/// 重载Windows系统函数Sleep()
/// @param[in]	unMillisecond - 等待的毫秒数
///
inline void SleepTime(UINT unMillisecond)
{
#ifdef _WIN32
//	::Sleep(unMillisecond);
#else
	usleep(1000 * unMillisecond);
#endif
}

///
/// @par 功能
/// 重载Windows系统函数GetLastError()
/// @return	出错代码
///
inline int GetLastError()
{
#ifdef WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}

///
/// @par 功能
/// 检查文件是否存在
/// @return
///
inline bool FileExists(LPCSTR pszPathName)
{
#ifdef WIN32
	return GetFileAttributesA(pszPathName) != INVALID_FILE_ATTRIBUTES;
#else
	struct stat tInfo;
	return stat(pszPathName, &tInfo) == 0;
#endif
}

///
/// @par 功能
/// 获取文件大小
/// @return
///
inline long long GetFileSize(LPCSTR pszPathName)
{
#ifdef WIN32
	WIN32_FILE_ATTRIBUTE_DATA tWfad;
	return GetFileAttributesExA(pszPathName, GetFileExInfoStandard, &tWfad)
			? (((long long)(tWfad.nFileSizeHigh) << 32) | tWfad.nFileSizeLow) : 0;
#else
	struct stat tInfo;
	return stat(pszPathName, &tInfo) == 0 ? tInfo.st_size : 0;
#endif
}

///
/// @par 功能
/// 执行系统命令
/// @return
///
inline int SystemExec(const char* pCmdFormat, ...)
{
	if (NULL == pCmdFormat || '\0' == *pCmdFormat)
	{
		return 0;
	}

	char szCmd[320] = "";

	va_list args;
	va_start(args, pCmdFormat);

	vsnprintf(szCmd, 319, pCmdFormat, args);
	va_end(args);

	return system(szCmd);
}

///
/// @par 功能
/// 线程包装类
///

class CThread
{
public:

#ifndef WIN32
	typedef pthread_t HANDLE;
#endif

	// 构造函数
	CThread()
		: m_unThreadId(0)
#ifdef WIN32
		, m_hThread(NULL)
#endif
	{
	}

	// 析构函数
	~CThread()
	{
		e_Close();
	}

	///
	/// @par 功能
	/// 启动线程
	/// @param[in]	fnRoutine - 线程回调函数
	/// @param[in]	args	  - 线程传入参数
	/// @return - 新线程是否成功启动
	///
	bool e_Begin(THREAD_FUN fnRoutine, void* args)
	{
		if (0 != m_unThreadId)
		{
			return false;
		}
#ifndef WIN32
		pthread_attr_t tAttr;
		pthread_attr_init(&tAttr);
		int bRet = false;
		if (pthread_create(&m_hThread, &tAttr, fnRoutine, args) == 0)
		{
			m_unThreadId = 1;
			bRet = true;
		}
		pthread_attr_destroy(&tAttr);
		return bRet;
#else
		UINT unThreadId = 0;
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, fnRoutine, args, 0, &unThreadId);
		m_unThreadId = unThreadId;
		return NULL != m_hThread;
#endif
	}

	///
	/// @par 功能
	/// 等待线程函数运行结束
	/// @param[in]	unTimeout - 等待超时时间，linux下此参数无效
	///
	void e_Wait(UINT unTimeout = -1)
	{
		if (0 != m_unThreadId)
		{
#ifndef WIN32
			void* pRet = NULL;
			if (UINT(-1) == unTimeout)
			{
				pthread_join(m_hThread, &pRet);
			}
			else
			{
				timespec ts;
				clock_gettime(CLOCK_REALTIME, &ts);
				ts.tv_sec  += unTimeout / 1000;
				ts.tv_nsec += (unTimeout % 1000) * 1000000;

				//pthread_timedjoin_np(m_hThread, &pRet, &ts);
				pthread_join(m_hThread, &pRet);
			}
#else
			WaitForSingleObject(m_hThread, unTimeout);
#endif

			m_unThreadId = 0;
		}
	}

	///
	/// @par 功能
	/// 关闭线程句柄
	///
	void e_Close()
	{
		if (0 != m_unThreadId)
		{
#ifndef WIN32
			pthread_detach(m_hThread);
#else
			CloseHandle(m_hThread);
#endif
			m_unThreadId = 0;
		}
	}

	///
	/// @par 功能
	/// 线程是否已开启
	///
	bool e_IsEmpty() const
	{
		return 0 == m_unThreadId;
	}

private:

	// 线程ID
	volatile UINT m_unThreadId;

	// 线程句柄
	HANDLE m_hThread;
};

///
/// @par 功能
/// 线程锁信号量包装类
///

class CMutex
{
	//禁止使用拷贝构造函数和等于
	CMutex(const CMutex&);
	CMutex& operator==(const CMutex&);

public:

	// 构造函数
	CMutex()
	{
#ifndef WIN32
		pthread_mutexattr_t tAttr;
		pthread_mutexattr_init(&tAttr);
		pthread_mutexattr_settype(&tAttr, PTHREAD_MUTEX_NORMAL);
		pthread_mutex_init(&m_tMutex, &tAttr);
		pthread_mutexattr_destroy(&tAttr);
#else
		InitializeCriticalSection(&m_tCriticalSection);
#endif
	}
	// 析构函数
	~CMutex()
	{
#ifndef WIN32
		pthread_mutex_destroy(&m_tMutex);
#else
		DeleteCriticalSection(&m_tCriticalSection);
#endif
	}

	///
	/// @par 功能
	/// 锁定
	///
	void e_Lock()
	{
#ifndef WIN32
		pthread_mutex_lock(&m_tMutex);
#else
		EnterCriticalSection(&m_tCriticalSection);
#endif
	}

	///
	/// @par 功能
	/// 解锁
	///
	void e_Unlock()
	{
#ifndef WIN32
		pthread_mutex_unlock(&m_tMutex);
#else
		LeaveCriticalSection(&m_tCriticalSection);
#endif
	}

private:

#ifndef WIN32
	pthread_mutex_t m_tMutex;
#else
	CRITICAL_SECTION m_tCriticalSection;
#endif

};

///
/// @par 功能
/// 线程锁Event包装类
///

class CEvent
{
	//禁止使用拷贝构造函数和等于
	CEvent(const CMutex&);
	CEvent& operator==(const CMutex&);

public:

	// 构造函数
	CEvent()
	{
#ifndef WIN32
		pthread_mutexattr_t tAttr;
		pthread_mutexattr_init(&tAttr);
		pthread_mutexattr_settype(&tAttr, PTHREAD_MUTEX_NORMAL);
		pthread_mutex_init(&m_tMutex, &tAttr);
		pthread_mutexattr_destroy(&tAttr);
		pthread_cond_init(&m_tCond, NULL);
		m_bSignal = false;
#else
		m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
#endif
	}

	// 析构函数
	~CEvent()
	{
#ifndef WIN32
		pthread_mutex_destroy(&m_tMutex);
		pthread_cond_destroy(&m_tCond);
#else
		if (NULL != m_hEvent)
		{
			CloseHandle(m_hEvent);
		}
#endif
	}

	///
	/// @par 功能
	/// 等待事件发生
	///
	void e_Wait()
	{
#ifndef WIN32
		if (!m_bSignal)
		{
			pthread_mutex_lock(&m_tMutex);
			pthread_cond_wait(&m_tCond, &m_tMutex);
			pthread_mutex_unlock(&m_tMutex);
		}
		m_bSignal = false;
#else
		if (NULL != m_hEvent)
		{
			WaitForSingleObject(m_hEvent, INFINITE);
		}
#endif
	}

	///
	/// @par 功能
	/// 设置事件
	///
	void e_SetEvent()
	{
#ifndef WIN32
		if (m_bSignal)
		{
			return;
		}
		m_bSignal = true; // 必须放在发送信号的前面
		pthread_mutex_lock(&m_tMutex);
		pthread_cond_signal(&m_tCond);
		pthread_mutex_unlock(&m_tMutex);
#else
		if (NULL != m_hEvent)
		{
			SetEvent(m_hEvent);
		}
#endif
	}

private:

#ifndef WIN32
	pthread_mutex_t m_tMutex;
	pthread_cond_t  m_tCond;
	volatile bool m_bSignal;
#else
	HANDLE m_hEvent;
#endif
};

///
/// @par 功能
/// C++回调虚类
///

class CCallback
{
public:

	// 仅返回通知的回调函数
	virtual void e_OnNotify(int /*nCode*/) { }

	// 传入两个参数的回调函数
	virtual int e_OnCallback(long /*lParam*/, long /*wParam*/) { return 0; }

};

///
/// @par 功能
/// 计算指定字符串的bkrd hash值
/// @param[in]	str - 指定字符串
/// @param[in]	hash - hash计算基础值
/// @return hash值
///
inline UINT bkrd_hash(const char* str, UINT hash = 0)
{
	for ( ; *str; ++str)
	{
		hash = hash * 131313 + (unsigned char)*str;  // 31 131 1313 13131 131313 etc..
	}
	return hash;
}

///
/// @par 功能
/// 计算指定范围字符串的bkrd hash值, 可计算字符中间有'\0'的情况
/// @param[in]	str - 指定字符串
/// @param[in]	tail - 指定字符串结尾(开区间)
/// @param[in]	hash - hash计算基础值
/// @return hash值
///
inline UINT bkrd_hash(const char* str, const char* tail, UINT hash = 0)
{
	for ( ; str != tail; ++str)
	{
		hash = hash * 131313 + (unsigned char)*str;  // 31 131 1313 13131 131313 etc..
	}
	return hash;
}

#ifdef _MSC_VER

typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> > String;
typedef std::map<xgKtv::String, xgKtv::String> MAP_Parameter;

#else

// 启用内存池的string
typedef std::basic_string<char, std::char_traits<char>, __gnu_cxx::__pool_alloc<char> >
		String;


// 启用内存池的map<string, string>
typedef std::map<xgKtv::String, xgKtv::String, std::less<xgKtv::String>,
		 __gnu_cxx::__pool_alloc<std::pair<const xgKtv::String, xgKtv::String> > > MAP_Parameter;

#endif

// 返回map中的值
inline const xgKtv::String& PARAM_At(const MAP_Parameter& mapParam, LPCSTR pszKey)
{
	const static xgKtv::String s_strEmpty;
	MAP_Parameter::const_iterator itor = mapParam.find(pszKey);
	return mapParam.end() != itor ? itor->second : s_strEmpty;
}

// 打印整个map的值
inline const xgKtv::String PARAM_Dump(const MAP_Parameter& mapParam)
{
	const int BUF_Len = 384;
	char szTextBuf[BUF_Len] = "";
	int nLen = 0;
	MAP_Parameter::const_iterator itor = mapParam.begin();
	for (; mapParam.end() != itor; ++itor)
	{
		nLen += snprintf(&szTextBuf[nLen], BUF_Len-1-nLen, "[%s=%s],", itor->first.c_str(), itor->second.c_str());
	}
	if (nLen > 0)
	{
		szTextBuf[nLen - 1] = '\0';
		return xgKtv::String(szTextBuf);
	}
	else
	{
		return xgKtv::String("(empty)");
	}
}

// 包装目录创建函数
#ifndef WIN32
  #define _mkdir(pathname) mkdir(pathname, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)
#else
  #define _mkdir(pathname) mkdir(pathname)
#endif // WIN32

///
/// @par 功能
/// 转换UTF8字符串到Unicode字符串
/// @param[in]	pszText - UTF-8目标字符串
/// @param[in]	wp - Unicode字符串
/// @param[in]	unCount - 目标字符串容量
/// @return hash值
///
char* UNICODE_2_UTF8(char* pszText, const wchar_t* wp, unsigned int unCount);

///
/// @par 功能
/// 转换Unicode字符串到UTF8字符串
/// @param[in]	pwszText - Unicode目标字符串
/// @param[in]	p - UTF8字符串
/// @param[in]	unCount - 目标字符串容量
/// @return hash值
///
wchar_t* UTF8_2_UNICODE(wchar_t* pwszText, const char* p, unsigned int unCount);

///
/// @par 功能
/// 转换字符串为无符号整数，防止转换大数字为负数
/// @param[in]	pszValue - 数字字符串
/// @return 数字
///
inline UINT atou(LPCSTR pszValue)
{
	return (NULL != pszValue) ? (UINT)atoll(pszValue) : (UINT)0;
}

} // namespace xgKtv

#if defined(_MSC_VER) && _MSC_VER > 1300
#define strncpy(d, s, n) strncpy_s(d, n, s, _TRUNCATE)
#endif

#define SAFE_Delete(p) if (p) { delete p; p = NULL; }
#define SAFE_DeleteArray(p) if (p) { delete [] p; p = NULL; }

template<class T>
inline T* SAFE_New(T*& p) { if (!p) p = new T(); return p; }

// 仿函数，删除容器指针
template<class T>
struct F_DeletePtr
{
	void operator()(T* p)
	{
		delete p;
	}
};

// 定义特殊值，OTHER
#define OTHER 0x22

// 媒体文件编码
typedef union T_Code
{
	struct
	{
		UINT low;
		UINT high;
	};
	ULONGLONG quad;

	T_Code() : quad(0) { }
	T_Code(UINT unLow, UINT unHighPart)
		: low(unLow)
		, high(unHighPart)
	{ }
	T_Code(ULONGLONG ullCode)
		: quad(ullCode)
	{ }

	// 小于操作符重载，用于在map中排序
	bool operator<(const T_Code& tCode) const
	{
		return quad < tCode.quad;
	}
	// 等于操作符重载，用于在map中排序
	bool operator==(const T_Code& tCode) const
	{
		return quad == tCode.quad;
	}
} T_Code;

#endif // __XG_UTILITY_H__
