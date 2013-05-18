#ifndef ZEUS_NET_ACCEPTOR_H_
#define ZEUS_NET_ACCEPTOR_H_

#include <boost/noncopyable.hpp>
#include "inet_address.hpp"
#include "zeus_net_def.h"
#include "callbacks.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class Acceptor 
    : private boost::noncopyable
{
public:
    explicit Acceptor(const InetAddress& listenAddress, boost::asio::io_service& io_service, uint32 threadNums);
    virtual ~Acceptor();

public:
    std::string host() const;
    uint16 port() const;
    void listen(int32 backlog = socket_base::max_connections);
    void startAccept();
    void stopAccept();
    bool listenning() const;

public:
    void setNewConnectionCallback(const NewConnectionCallback& cb);
    void setWriteComplectedCallback(const WriteCompletedCallback& cb);

private:
    void acceptHandler(const TcpConnectionPtr& connection);
    void postAcceptEvent();

private:
    boost::asio::io_service& _io_service;
    boost::asio::strand _strand;
    bool _listenning;
    uint32 _threadNums;
    InetAddress _listenAddr;
    tcp::acceptor _acceptor;

    //callbacks
    NewConnectionCallback _newConnectionCallback;
    WriteCompletedCallback _writeComplectedCallback;
};

#endif