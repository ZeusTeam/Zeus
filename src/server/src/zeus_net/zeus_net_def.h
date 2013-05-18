#ifndef ZEUS_NET_DEF_H_
#define ZEUS_NET_DEF_H_

#include <memory>
#include <thread>
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

class TcpConnection;
class InetAddress;

//smart ptr
typedef std::shared_ptr<std::thread> ThreadPtr;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

#endif