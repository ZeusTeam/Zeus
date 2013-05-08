#ifndef ZEUS_NET_CONNECTOR_H_
#define ZEUS_NET_CONNECTOR_H_

#include <common.h>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost;
using namespace boost::asio::ip;

class Connector 
    : public boost::noncopyable, public boost::enable_shared_from_this<Connector>
{
public:
    Connector(asio::io_service io_service)
       : _socket(io_service)
    {
    }

public:
    tcp::socket& socket()
    {
        return _socket;
    } 

private:
    tcp::socket _socket;
};

#endif