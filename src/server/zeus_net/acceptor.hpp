#ifndef ZEUS_NET_ACCEPTOR_H_
#define ZEUS_NET_ACCEPTOR_H_

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <thread>
#include "inet_address.hpp"
#include "connection.hpp"
#include "callbacks.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class Acceptor : boost::noncopyable
{
public:
    Acceptor(const InetAddress& listenAddress, boost::asio::io_service& io_service)
        : _io_service(io_service),
        _listenAddr(listenAddress),
        _listenning(false),
        _acceptor(io_service)
    {
        //�󶨵�ַ
        boost::asio::ip::address address;
        address.from_string(_listenAddr.host());
        tcp::endpoint endpoint(address, _listenAddr.port());
        _acceptor.open(tcp::v4());
        _acceptor.bind(endpoint);
    }

public:
    inline std::string host() const
    {
        return _listenAddr.host();
    }

    inline uint16 port() const
    {
        return _listenAddr.port();
    }

    void listen(int32 backlog = socket_base::max_connections)
    {
        _acceptor.listen(backlog);
        _listenning = true;
    }

    void startAccept()
    {
        postAcceptEvent();

        std::thread t(&Acceptor::workerThread, this);
        t.join();
    }

    void stopAccept()
    {
        std::cout << "stopAccept." << std::endl;
        _io_service.stop();
        _acceptor.close();
    }

    bool listenning() const { return _listenning; }

public:
    void setNewConnectCallback(const NewConnectionCallback& cb)
    {
        _newConnectionCallback = cb;
    }

private:
    void workerThread()
    {
        _io_service.run();
    }

    void acceptHandler(const TcpConnectionPtr& connection)
    {
        postAcceptEvent();
        if (connection->isOpen())
        {
            if (!_newConnectionCallback.empty())
            {
                //����ͨ�ŵ�ַ�ṹ
                tcp::socket& socket = connection->socket();
                std::string remote_address = socket.remote_endpoint().address().to_string();
                uint16 remote_port = socket.remote_endpoint().port();
                InetAddress peerAddress(remote_address, remote_port);

                //�ص��������Ӵ�����
                _newConnectionCallback(connection, peerAddress);
            }
            else
            {
                connection->close();
            }
        }
    }

    void postAcceptEvent()
    {
        //����һ���µ����ӣ��º��������ӳأ����⿪���ڴ�Ŀ�����
        TcpConnectionPtr new_connection(new TcpConnection(_io_service)); 

        //Ͷ��һ��accept����io���У����ص���acceptHandler
        _acceptor.async_accept(new_connection->socket(),
            std::bind(&Acceptor::acceptHandler, this, new_connection));
    }

private:
    boost::asio::io_service& _io_service;
    bool _listenning;
    InetAddress _listenAddr;
    tcp::acceptor _acceptor;
    NewConnectionCallback _newConnectionCallback;
};

#endif