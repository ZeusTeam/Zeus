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

    void WriteComplectedHandler(const TcpConnectionPtr& connection, uint32 bytes_transferred)
    {
        std::cout << "Write complected handler." << std::endl;
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