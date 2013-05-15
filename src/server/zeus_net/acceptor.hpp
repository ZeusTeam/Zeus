#ifndef ZEUS_NET_ACCEPTOR_H_
#define ZEUS_NET_ACCEPTOR_H_

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <thread>
#include "inet_address.hpp"
#include "tcp_connection.hpp"
#include "connection_pool.hpp"
#include "zeus_net_def.h"

using namespace boost::asio;
using namespace boost::asio::ip;

class Acceptor : boost::noncopyable
{
public:
    Acceptor(const InetAddress& listenAddress, boost::asio::io_service& io_service, uint32 threadNums)
        : _io_service(io_service),
        _strand(io_service),
        _listenAddr(listenAddress),
        _listenning(false),
        _acceptor(io_service),
        _threadNums(threadNums),
		_connectionPool(io_service)
    {
        //绑定地址
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
        assert(_threadNums != 0);

		std::cout<<"Welcome to Zeus!!!"<<std::endl;
		std::cout<<"Waiting for connection..."<<std::endl;
        //投递一个接受事件
        postAcceptEvent();

        //为IO队列创建线程
        std::vector<ThreadPtr> threads;
        for (std::size_t i = 0; i < _threadNums; ++i)
        {
			//Run方法执行队列中的所有任务，直到任务执行完毕,_io_service可以理解为用来标识一个IO队列
            ThreadPtr t(new std::thread(boost::bind(&boost::asio::io_service::run, &_io_service)));
            threads.push_back(t);
        }

        for(auto& thread : threads)
        {
            thread->join();
        }
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
    void acceptHandler(const  CONNECTED& connection)
    {
        std::cout << "thread id = " << std::this_thread::get_id() << std::endl;

		//本次连接已被处理，可以accept下一个连接
        postAcceptEvent();

        if (connection.connectionPtr->isOpen())
        {
            if (!_newConnectionCallback.empty())
            {
                //构造通信地址结构,此处的地址为客户端的信息
                tcp::socket& socket = connection.connectionPtr->socket();
                std::string remote_address = socket.remote_endpoint().address().to_string();
                uint16 remote_port = socket.remote_endpoint().port();
                InetAddress peerAddress(remote_address, remote_port);

                //回调到新连接处理函数
				//_newConnectionCallback是指向EventHandler类的NewConnectionHandler成员函数指针
                _newConnectionCallback(connection, peerAddress);


				//连接处理完，回收TcpConnectionPtr
				_connectionPool.free_connectionPtr(connection.index);
            }
			else
			{

			}
			
           
        }
    }

    void postAcceptEvent()
    {
        //创建一个新的连接（事后增加连接池，避免开辟内存的开销）
     // TcpConnectionPtr new_connection(new TcpConnection(_io_service));
		CONNECTED  new_connection;
		new_connection=_connectionPool.get_connectionPtr();
		if(new_connection.type==POOL_ERROR)
		{
			std::cout<<"暂时没有可用TcpConnectionPtr"<<std::endl;
			postAcceptEvent();
		}
		else
		{
			//		_acceptor.async_accept(new_connection->socket(),
			//			std::bind(&Acceptor::acceptHandler, this, new_connection));
			//投递一个accept请求到io队列，并回调到acceptHandler
			//async_accept会调用_io_service.post()方法，投递一个async_accept的任务到_io_service队列,new_connection作为参数
			_acceptor.async_accept(new_connection.connectionPtr->socket(),
				std::bind(&Acceptor::acceptHandler, this, new_connection));
		}
	}

private:
	ConnectionPool  _connectionPool;
    boost::asio::io_service& _io_service;
    boost::asio::strand _strand;
    bool _listenning;
    uint32 _threadNums;
    InetAddress _listenAddr;
    tcp::acceptor _acceptor;
    NewConnectionCallback _newConnectionCallback;
};

#endif