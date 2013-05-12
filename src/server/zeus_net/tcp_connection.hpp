#ifndef ZEUS_NET_TCP_CONNECTION_H_
#define ZEUS_NET_TCP_CONNECTION_H_

#include <common.h>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class TcpConnection 
    : boost::noncopyable
{
public:
    TcpConnection(boost::asio::io_service& io_service)
        : _socket(io_service)
    {
    }

    virtual ~TcpConnection()
    {
        close();
        std::cout << "connection destroyed." << std::endl;
    }

public:
    void send(byte* data, size_t size)
    {
        _socket.send(buffer(data, size));
    }

    void close()
    {
        _socket.shutdown(socket_base::shutdown_both);
        _socket.close();
    }

public:
    tcp::socket& socket()
    {
        return _socket;
    }

    bool isOpen() const
    {
        return _socket.is_open();
    }

private:
    tcp::socket _socket; 
};

#endif