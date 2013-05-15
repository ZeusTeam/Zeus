#ifndef ZEUS_NET_DEF_H_
#define ZEUS_NET_DEF_H_

#include <boost/function.hpp>
#ifdef _WIN32
#include <windows.h>
#else
#include <sysconf.h>
#endif


namespace zeus
{
namespace net_params
{
    inline int32 smart_thread_nums()
    {
#ifdef _WIN32
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        return si.dwNumberOfProcessors;
#else
        return sysconf(_SC_NPROCESSORS_CONF);
#endif
    }
}
}



//forward declarations 
class TcpConnection;

//smart ptr
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef std::shared_ptr<std::thread> ThreadPtr;


typedef struct  connected
{
	int               type;           //0为未使用，1为使用中
	int               index;          //索引
	TcpConnectionPtr  connectionPtr;
}CONNECTED;

//callbacks
typedef boost::function<void (const CONNECTED&, const InetAddress& )> NewConnectionCallback;

#endif