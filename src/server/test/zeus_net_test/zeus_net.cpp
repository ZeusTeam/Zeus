#include <functional>
#include "tcp_server.h"
#include "tcp_connection.h"
#include "zeus_net_def.h"
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
        //connection->send((byte*)"Hello Zeus\n", 12);
        connection->read();
    }

    void WriteCompletedHandler(const TcpConnectionPtr& connection, uint32 bytes_transferred)
    {
        std::cout << "Write complected handler." << std::endl;
    }

    void ReadCompletedHandler(const TcpConnectionPtr& connection, uint32 bytes_transferred)
    {
        std::cout << "Read complected handler." << std::endl;
        connection->read();
    }

    void ConnectionClosed(const TcpConnectionPtr& connection)
    {
        std::cout << "Connection closed handler." << std::endl;
    }
};

int main()
{
    try
    {
        EventHandler eventHandler;
        InetAddress inetAddress(36911);

        //boost::asio::io_service io_service;
        IOService service;
        TcpServer server(inetAddress, service, 4);
        
        server.setNewConnectionCallback(
            std::bind(&EventHandler::NewConnectionHandler, &eventHandler, std::placeholders::_1, std::placeholders::_2)
            );

        server.setWriteCompletedCallback(
            std::bind(&EventHandler::WriteCompletedHandler, &eventHandler, std::placeholders::_1, std::placeholders::_2)
            );

        server.setReadCompletedCallback(
            std::bind(&EventHandler::ReadCompletedHandler, &eventHandler, std::placeholders::_1, std::placeholders::_2)
            );

        server.setConnectionClosedCallback(
            std::bind(&EventHandler::ConnectionClosed, &eventHandler, std::placeholders::_1)
            );

        server.start();
    }
    catch (...)
    {
        std::cout << "exception occurred" << std::endl;
    }

    return 0;
}