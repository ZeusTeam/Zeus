#include <boost/asio.hpp>
#include "inet_address.hpp"
#include "tcp_server.h"

TcpServer::TcpServer(const InetAddress& listenAddress, boost::asio::io_service& io_service, uint32 threadNums)
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
    _signals.async_wait(std::bind(&TcpServer::stop, this));  
}

TcpServer::~TcpServer()
{
    
}

void TcpServer::start()
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

void TcpServer::stop()
{
    //stop acceptor
    _acceptor.stopAccept();

    //close all alived connections
    // ...

}

void TcpServer::setNewConnectionCallback(const NewConnectionCallback& cb)
{
    _acceptor.setNewConnectionCallback(cb);
}

void TcpServer::setWriteComplectedCallback(const WriteCompletedCallback& cb)
{
    _acceptor.setWriteComplectedCallback(cb);
}
