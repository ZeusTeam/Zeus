#ifndef ZEUS_NET_TCP_SERVER_H_
#define ZEUS_NET_TCP_SERVER_H_

#include <common.h>
#include <boost/noncopyable.hpp>
#include <memory>
#include "acceptor.h"
#include "io_service.h"

class InetAddress;
class TcpServer 
    : private boost::noncopyable
{
public:
    TcpServer(const InetAddress& listenAddress, IOService& service, uint32 threadNums);
    virtual ~TcpServer();

public:
    void start();
    void stop();

public:
    void setNewConnectionCallback(const NewConnectionCallback& cb);
    void setWriteCompletedCallback(const WriteCompletedCallback& cb);
    void setReadCompletedCallback(const ReadCompletedCallback& cb);
    void setConnectionClosedCallback(const ConnectionClosedCallback& cb);

private:
    void newConnectionCallback(const TcpConnectionPtr& connection);
    void connectionClosedCallback(const TcpConnection& connection);

private:
    Acceptor _acceptor;
    bool _started;
    boost::asio::signal_set _signals;

    NewConnectionCallback _newConnectionCallback;
    WriteCompletedCallback _writeCompletedCallback;
    ReadCompletedCallback _readCompletedCallback;
    ConnectionClosedCallback _connectionClosedCallback;

    IOService& _io_service;
};

#endif