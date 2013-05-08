#ifndef ZEUS_NET_CALLBACKS_H_
#define ZEUS_NET_CALLBACKS_H_

#include <boost/function.hpp>

class TcpConnection;
typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef boost::function<void (const TcpConnectionPtr&, const InetAddress& )> NewConnectionCallback;

#endif