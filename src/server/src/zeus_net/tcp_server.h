#ifndef ZEUS_NET_TCP_SERVER_H_
#define ZEUS_NET_TCP_SERVER_H_

#include <common.h>
#include <boost/noncopyable.hpp>
#include "acceptor.h"
#include "callbacks.h"

class InetAddress;
class TcpServer : boost::noncopyable
{
public:
    TcpServer(const InetAddress& listenAddress, boost::asio::io_service& io_service, uint32 threadNums);
    virtual ~TcpServer();

public:
    void start();
    void stop();

public:
    void setNewConnectionCallback(const NewConnectionCallback& cb);
    void setWriteComplectedCallback(const WriteCompletedCallback& cb);

private:
    Acceptor _acceptor;
    bool _started;
    boost::asio::signal_set _signals;
};

#endif