#include <functional>
#include <thread>
#include <boost/bind.hpp>
#include "acceptor.h"
#include "tcp_connection.h"
#include "zeus_net_def.h"

Acceptor::Acceptor(const InetAddress& listenAddress, boost::asio::io_service& io_service, uint32 threadNums)
    : _io_service(io_service),
    _strand(io_service),
    _listenAddr(listenAddress),
    _listenning(false),
    _acceptor(io_service),
    _threadNums(threadNums)
{
    //绑定地址
    boost::asio::ip::address address;
    address.from_string(_listenAddr.host());
    tcp::endpoint endpoint(address, _listenAddr.port());
    _acceptor.open(tcp::v4());
    _acceptor.bind(endpoint);
}

Acceptor::~Acceptor()
{
}

std::string Acceptor::host() const
{
    return _listenAddr.host();
}

uint16 Acceptor::port() const
{
    return _listenAddr.port();
}

void Acceptor::listen(int32 backlog/* = socket_base::max_connections*/)
{
    _acceptor.listen(backlog);
    _listenning = true;
}

void Acceptor::startAccept()
{
    assert(_threadNums != 0);

    //投递一个接受事件
    postAcceptEvent();

    //为IO队列创建线程
    std::vector<ThreadPtr> threads;
    for (std::size_t i = 0; i < _threadNums; ++i)
    {
        ThreadPtr t(
            new std::thread(
                boost::bind(&boost::asio::io_service::run, &_io_service)
            )
        );
        threads.push_back(t);
    }

    for(std::size_t i = 0; i < threads.size(); ++i)
    {
        threads[i]->join();
    }
}

void Acceptor::stopAccept()
{
    std::cout << "stopAccept." << std::endl;
    _io_service.stop();
    _acceptor.close();
}

bool Acceptor::listenning() const { return _listenning; }

void Acceptor::setNewConnectionCallback(const NewConnectionCallback& cb)
{
    _newConnectionCallback = cb;
}

void Acceptor::setWriteComplectedCallback(const WriteCompletedCallback& cb)
{
    _writeComplectedCallback = cb;
}

void Acceptor::acceptHandler(const TcpConnectionPtr& connection)
{
    std::cout << "thread id = " << std::this_thread::get_id() << std::endl;

    postAcceptEvent();

    if (connection->isOpen())
    {
        if (!_newConnectionCallback)
        {
            //构造通信地址结构
            tcp::socket& socket = connection->socket();
            std::string remote_address = socket.remote_endpoint().address().to_string();
            uint16 remote_port = socket.remote_endpoint().port();
            InetAddress peerAddress(remote_address, remote_port);

            //回调到新连接处理函数
            connection->setWriteCompletedCallback(_writeComplectedCallback);
            _newConnectionCallback(connection, peerAddress);
        }
        else
        {
            connection->close();
        }
    }
}

void Acceptor::postAcceptEvent()
{
    //创建一个新的连接（事后增加连接池，避免开辟内存的开销）
    TcpConnectionPtr new_connection(new TcpConnection(_io_service)); 

    //投递一个accept请求到io队列，并回调到acceptHandler
    _acceptor.async_accept(new_connection->socket(),
        std::bind(&Acceptor::acceptHandler, this, new_connection));
}
