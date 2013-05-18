#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "tcp_connection.h"
#include "zeus_net_def.h"

TcpConnection::TcpConnection(boost::asio::io_service& io_service)
    : _socket(io_service),
    _strand(io_service)
{
}

TcpConnection::~TcpConnection()
{
    close();
    std::cout << "connection destroyed." << std::endl;
}

void TcpConnection::send(byte* data, size_t size)
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

void TcpConnection::close()
{
    _socket.shutdown(boost::asio::socket_base::shutdown_both);
    _socket.close();
}

tcp::socket& TcpConnection::socket()
{
    return _socket;
}

bool TcpConnection::isOpen()
{
    return _socket.is_open();
}

void TcpConnection::setWriteCompletedCallback(const WriteCompletedCallback& cb)
{
    _writeCompletedCallback = cb;
}

void TcpConnection::handleWrite(
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
