#ifndef ZEUS_NET_TCP_CONNECTION_H_
#define ZEUS_NET_TCP_CONNECTION_H_

#include <common.h>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "callbacks.h"

using namespace boost::asio::ip;

class TcpConnection
    : private boost::noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(boost::asio::io_service& io_service);
    virtual ~TcpConnection();

public:
    void send(byte* data, size_t size);
    void close();
    tcp::socket& socket();
    bool isOpen();

public:
    void setWriteCompletedCallback(const WriteCompletedCallback& cb);

private:
    void handleWrite(const boost::system::error_code& error, std::size_t bytes_transferred);

private:
    tcp::socket _socket;
    WriteCompletedCallback _writeCompletedCallback;
    
    //Strand to ensure the connection's handlers are not called concurrently.
    boost::asio::io_service::strand _strand;
};

#endif