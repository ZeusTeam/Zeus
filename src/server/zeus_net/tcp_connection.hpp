#ifndef ZEUS_NET_TCP_CONNECTION_H_
#define ZEUS_NET_TCP_CONNECTION_H_

#include <common.h>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <mutex>
#include "zeus_net_def.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class TcpConnection 
    : private boost::noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(boost::asio::io_service& io_service)
        : _socket(io_service),
        _strand(io_service)
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
        if (!data)
        {
            std::cout << "empty data." << std::endl;
            return;
        }

        _socket.async_send(
            boost::asio::buffer(data, size),
            _strand.wrap(
                boost::bind(
                    &TcpConnection::handleWrite, 
                    shared_from_this(), 
                    boost::asio::placeholders::error, 
                    boost::asio::placeholders::bytes_transferred
                )
            )
        );
    }

    void close()
    {
        _socket.shutdown(socket_base::shutdown_both);
        _socket.close();
    }

    tcp::socket& socket()
    {
        return _socket;
    }

    bool isOpen() const
    {
        return _socket.is_open();
    }

public:
    void setWriteCompletedCallback(const WriteCompletedCallback& cb)
    {
        _writeCompletedCallback = cb;
    }

private:
    void handleWrite(
        const boost::system::error_code& error, // Result of operation.
        std::size_t bytes_transferred           // Number of bytes sent.
    )
    {
        if (error)
        {
            //Initiate graceful connection closure.
            boost::system::error_code ignored_ec;
            _socket.shutdown(tcp::socket::shutdown_both, ignored_ec);

            std::cout << error.value() << ":" << error.message() << std::endl;
            return;
        }
        else
        {
            std::cout << "bytes_transferred = " << bytes_transferred << std::endl;
            if (!_writeCompletedCallback._Empty())
            {
                _writeCompletedCallback(shared_from_this(), bytes_transferred);
                std::cout << "_writeCompletedCallback not NULL." << std::endl;
            }
            else
            {
                std::cout << "write complected." << std::endl;
            }
        }
    }

private:
    tcp::socket _socket;
    WriteCompletedCallback _writeCompletedCallback;
    
    // Strand to ensure the connection's handlers are not called concurrently.
    boost::asio::io_service::strand _strand;
    mutable std::mutex _mutex;
};


#endif