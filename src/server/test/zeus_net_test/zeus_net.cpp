#include <functional>
#include "tcp_server.h"
#include "tcp_connection.h"
#include "zeus_net_def.h"
#include "callbacks.h"
#include "inet_address.hpp"

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

    void WriteComplectedHandler(const TcpConnectionPtr& connection, uint32 bytes_transferred)
    {
        std::cout << "Write complected handler." << std::endl;
    }

};

int main()
{
    try
    {
        EventHandler eventHandler;
        InetAddress inetAddress(36911);

        boost::asio::io_service _io_service;
        TcpServer server(inetAddress, _io_service, 4);
        
        server.setNewConnectionCallback(
            std::bind(&EventHandler::NewConnectionHandler, &eventHandler, std::placeholders::_1, std::placeholders::_2)
            );

        server.setWriteComplectedCallback(
            std::bind(&EventHandler::WriteComplectedHandler, &eventHandler, std::placeholders::_1, std::placeholders::_2)
            );

        server.start();
    }
    catch (...)
    {
        std::cout << "exception occurred" << std::endl;
    }

    return 0;
}