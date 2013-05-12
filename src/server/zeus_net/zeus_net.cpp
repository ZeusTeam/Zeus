#include <boost/bind.hpp>
#include "tcp_server.hpp"

class EventHandler
{
public:
    EventHandler(){}
    virtual ~EventHandler(){}

public:
    void NewConnectionHandler(const TcpConnectionPtr& connection, const InetAddress& peerAddress)
    {
        std::cout << "New connection : " << peerAddress.toIpHost() << std::endl;
        connection->send((byte*)"Hello Zeus", 12);
    }
};

int main()
{
    try
    {
        InetAddress inetAddress(36911);

        boost::asio::io_service _io_service;
        TcpServer server(inetAddress, _io_service, 4);

        EventHandler eventHandler;
        server.setNewConnectCallback(
            boost::bind(&EventHandler::NewConnectionHandler, &eventHandler, _1, _2)
            );

        server.start();
    }
    catch (...)
    {
        std::cout << "exception occurred" << std::endl;
    }

    return 0;
}