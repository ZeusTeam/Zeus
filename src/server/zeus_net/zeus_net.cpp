#include <boost/bind.hpp>
#include "tcp_server.hpp"

class EventHandler
{
public:
    EventHandler(){}
    virtual ~EventHandler(){}

public:
	//作为回调函数，处理具体任务
    void NewConnectionHandler(const  CONNECTED& connection, const InetAddress& peerAddress)
    {
        std::cout << "New connection : " << peerAddress.toIpHost() << std::endl;
        connection.connectionPtr->send((byte*)"Hello Zeus", sizeof("Hello Zeus"));
    }
};

int main()
{
    try
    {
        InetAddress inetAddress(36911);

        boost::asio::io_service _io_service;
        TcpServer server(inetAddress, _io_service, zeus::net_params::smart_thread_nums());

        EventHandler eventHandler;
        server.setNewConnectCallback(
			//返回函数对象，此处返回NewConnectionHandler的对象
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