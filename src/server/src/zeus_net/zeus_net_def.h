#ifndef ZEUS_NET_DEF_H_
#define ZEUS_NET_DEF_H_

#include <functional>
#include <memory>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX_RECV_LEN    1024 * 4
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

    inline uint32 max_recv_length() { return MAX_RECV_LEN; }
}
}

class TcpConnection;
class InetAddress;

//smart ptr
typedef std::shared_ptr<std::thread> ThreadPtr;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

//callbacks
typedef std::function<void (const TcpConnectionPtr& connection, uint32 bytes_transferred)> WriteCompletedCallback;
typedef std::function<void (const TcpConnectionPtr& connection, uint32 bytes_transferred)> ReadCompletedCallback;
typedef std::function<void (const TcpConnectionPtr& connection)> AcceptedCallback;
typedef std::function<void (const TcpConnectionPtr& connection, const InetAddress& address)> NewConnectionCallback;
typedef std::function<void (const TcpConnectionPtr& connection)> ConnectionClosedCallback;

#endif