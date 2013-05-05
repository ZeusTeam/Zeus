#ifndef ZUES_NET_ACCEPTOR_H_
#define ZUES_NET_ACCEPTOR_H_

#include <boost/system/error_code.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <thread>
#include "inet_address.hpp"
#include "connection.h"


using namespace boost::asio;
using namespace boost::asio::ip;

class EventLoop;
class Acceptor : boost::noncopyable
{
public:
    Acceptor(EventLoop* eventLoop, const InetAddress& bindAddr)
        : _eventLoop(eventLoop),
        _bindAddr(bindAddr),
        _listenning(false),
        _acceptor(_io_service)
    {
        tcp::endpoint endpoint(tcp::v4(), bindAddr.port());
        _acceptor.open(tcp::v4());
        _acceptor.bind(endpoint);
    }

public:
    void listen(int32 backlog = socket_base::max_connections)
    {
        _acceptor.listen(backlog);
        _listenning = true;
    }

    void startAccept()
    {
        Connection* newConnection = new Connection(_io_service);
        _acceptor.async_accept(newConnection->socket(),
            std::bind(&Acceptor::acceptHandler, this, newConnection,
            std::placeholders::_1));
        std::thread t(&Acceptor::workerThread, this);
        t.join();
    }

    bool listenning() const { return _listenning; }

private:
    void workerThread()
    {
    
    }

    void acceptHandler(Connection* connection, const asio::error_code& error)
    {
        if (!error)
        {
            SocketHandler *handler=handlerFactory_->CreateHandler(conn);
            handler->start();

            new_connection_ = new AsioTcpConnection(io_service_);
            acceptor_.async_accept(new_connection_->socket(),
                std::bind(&Acceptor::acceptHandler, this ,new_connection_,
                std::placeholders::_1));
        }
        else 
        {
            //EZLOGGERSTREAM<<error.message()<<std::endl;
        }
    }

private:
    bool _listenning;
    InetAddress _bindAddr;
    tcp::acceptor _acceptor;
    io_service _io_service;
    EventLoop* _eventLoop;
};

#endif