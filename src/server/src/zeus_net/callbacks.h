#ifndef ZEUS_NET_CALLBACKS_H_
#define ZEUS_NET_CALLBACKS_H_

#include <functional>
#include "zeus_net_def.h"

typedef std::function<void (const TcpConnectionPtr& connection, uint32 bytes_transferred)> WriteCompletedCallback;
typedef std::function<void (const TcpConnectionPtr& connection, const InetAddress& address)> NewConnectionCallback;

#endif