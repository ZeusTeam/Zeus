#ifndef ZEUS_NET_TCP_SERVER_H_
#define ZEUS_NET_TCP_SERVER_H_

#include <common.h>
#include <boost/noncopyable.hpp>
#include "acceptor.hpp"

class InetAddress;
class TcpServer : boost::noncopyable
{
public:
    TcpServer(const InetAddress& listenAddress, boost::asio::io_service& io_service)
        : _io_service(io_service),
        _accptor(listenAddress, _io_service),
        _started(false)
    {
    }

    virtual ~TcpServer()
    {
    
    }

public:
    void start()
    {
        if (!_started)
        {
            _started = true;
        }
        else
        {
            stop();
        }

        _accptor.listen();
        _accptor.startAccept();
    }

    void stop()
    {
    }

public:
    void setNewConnectCallback(const NewConnectionCallback& cb)
    {
        _accptor.setNewConnectCallback(cb);
    }

private:
    boost::asio::io_service& _io_service;
    Acceptor _accptor;
    bool _started;

};

#endif