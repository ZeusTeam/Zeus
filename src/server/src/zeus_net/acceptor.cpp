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
    //�󶨵�ַ
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

    //Ͷ��һ�������¼�
    postAcceptEvent();

    //ΪIO���д����߳�
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

    for(auto& thread : threads)
    {
        thread->join();
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
        if (!_newConnectionCallback._Empty())
        {
            //����ͨ�ŵ�ַ�ṹ
            tcp::socket& socket = connection->socket();
            std::string remote_address = socket.remote_endpoint().address().to_string();
            uint16 remote_port = socket.remote_endpoint().port();
            InetAddress peerAddress(remote_address, remote_port);

            //�ص��������Ӵ�����
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
    //����һ���µ����ӣ��º��������ӳأ����⿪���ڴ�Ŀ�����
    TcpConnectionPtr new_connection(new TcpConnection(_io_service)); 

    //Ͷ��һ��accept����io���У����ص���acceptHandler
    _acceptor.async_accept(new_connection->socket(),
        std::bind(&Acceptor::acceptHandler, this, new_connection));
}