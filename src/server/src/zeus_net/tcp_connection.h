#ifndef ZEUS_NET_TCP_CONNECTION_H_
#define ZEUS_NET_TCP_CONNECTION_H_

#include <common.h>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "zeus_net_def.h"
#include "io_service.h"

using namespace boost::asio::ip;

class TcpConnection
    : private boost::noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(IOService& io_service);
    virtual ~TcpConnection();

public:
    void write(byte* data, size_t size);
    void read();
    void shutdown();
    void close();
    tcp::socket& socket();
    bool isOpen();

public:
    void setWriteCompletedCallback(const WriteCompletedCallback& cb);
    void setReadCompletedCallback(const ReadCompletedCallback& cb);
    void setConnectionClosedCallback(const ConnectionClosedCallback& cb);

private:
    void onError(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error, std::size_t bytes_transferred);
    void handleRead(const boost::system::error_code& error, std::size_t bytes_transferred);

private:
    tcp::socket _socket;
    WriteCompletedCallback _writeCompletedCallback;
    ReadCompletedCallback _readComplectedCallback;
    ConnectionClosedCallback _connectionClosedCallback;
    boost::array<char, MAX_RECV_LEN> _recvBuffer;
    boost::asio::strand _strand;
    IOService& _io_service;
};

#endif