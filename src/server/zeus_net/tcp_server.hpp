#ifndef ZEUS_NET_TCP_SERVER_H_
#define ZEUS_NET_TCP_SERVER_H_

#include <common.h>
#include <boost/noncopyable.hpp>
#include "acceptor.hpp"

class InetAddress;
class TcpServer : boost::noncopyable
{
public:
    TcpServer(const InetAddress& listenAddress, boost::asio::io_service& io_service, uint32 threadNums)
        : _acceptor(listenAddress, io_service, threadNums),
        _started(false),
        _signals(io_service)
    {
        //Ìí¼Ó²¶×½ÐÅºÅ
        _signals.add(SIGINT);
        _signals.add(SIGTERM);

#if defined(SIGQUIT)
        _signals.add(SIGQUIT);
#endif
        _signals.async_wait(boost::bind(&TcpServer::stop, this));  
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

        _acceptor.listen();
        _acceptor.startAccept();
    }

    void stop()
    {
        //stop acceptor
        _acceptor.stopAccept();

        //close all alived connections
        // ...

    }

public:
    void setNewConnectionCallback(const NewConnectionCallback& cb)
    {
        _acceptor.setNewConnectionCallback(cb);
    }

    void setWriteComplectedCallback(const WriteCompletedCallback& cb)
    {
        _acceptor.setWriteComplectedCallback(cb);
    }

private:
    Acceptor _acceptor;
    bool _started;
    boost::asio::signal_set _signals;
};

#endif