#ifndef ZEUS_NET_ACCEPTOR_H_
#define ZEUS_NET_ACCEPTOR_H_

#include <boost/noncopyable.hpp>
#include "inet_address.hpp"
#include "zeus_net_def.h"
#include "io_service.h"

using namespace boost::asio;

class Acceptor 
    : private boost::noncopyable
{
public:
    explicit Acceptor(const InetAddress& listenAddress, IOService& io_service, uint32 threadNums);
    virtual ~Acceptor();

public:
    std::string host() const;
    uint16 port() const;
    void listen(int32 backlog = socket_base::max_connections);
    void startAccept();
    void stopAccept();
    bool listenning() const;

public:
    void setAcceptedCallback(const AcceptedCallback& cb);

private:
    void accept();
    void acceptHandler(const TcpConnectionPtr& connection);

private:
    bool _listenning;
    uint32 _threadNums;
    InetAddress _listenAddr;
    AcceptedCallback _acceptedCallback;
    IOService& _io_service;
    boost::asio::strand _strand;
    boost::asio::ip::tcp::acceptor _acceptor;
};

#endif