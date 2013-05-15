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
        connection->send((byte*)"Hello Zeus\n", 12);
    }
};

int main()
{
    try
    {
        InetAddress inetAddress(36911);

        boost::asio::io_service _io_service;
        TcpServer server(inetAddress, _io_service, 4/*zeus::net_params::smart_thread_nums()*/);

        EventHandler eventHandler;
        server.setNewConnectCallback(
            std::bind(&EventHandler::NewConnectionHandler, &eventHandler, std::placeholders::_1, std::placeholders::_2)
            );

        server.start();
    }
    catch (...)
    {
        std::cout << "exception occurred" << std::endl;
    }

    return 0;
}