#ifndef ZEUS_NETWORK_PACKET_HANDLER_H_
#define ZEUS_NETWORK_PACKET_HANDLER_H_

#include <common.h>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>

class NetworkPacketHandler 
    : private boost::noncopyable, public std::enable_shared_from_this<NetworkPacketHandler>
{
public:
    void append();
};

#endif