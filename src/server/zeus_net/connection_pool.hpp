#include "zeus_net_def.h"
#include "tcp_connection.hpp"

#define POOL_MAX  100
#define POOL_OK        1
#define POOL_ERROR     2

class ConnectionPool
{
private:
	CONNECTED   pool_list[POOL_MAX];

public:
	ConnectionPool(boost::asio::io_service& );
	void          free_connectionPtr(int );
	CONNECTED     get_connectionPtr();
	~ConnectionPool();
};

ConnectionPool::ConnectionPool(boost::asio::io_service& io_service)
{
	for(int j=0;j<POOL_MAX;j++)
	{
	
		TcpConnectionPtr  connectionPtr(new TcpConnection(io_service));
	
		this->pool_list[j].connectionPtr=connectionPtr;
		this->pool_list[j].type=0;
		this->pool_list[j].index=j;
	}
}

void ConnectionPool::free_connectionPtr(int index)
{
	pool_list[index].type=0;
	pool_list[index].connectionPtr->close();
}

CONNECTED ConnectionPool::get_connectionPtr()
{
	for(int j=0;j<POOL_MAX;j++)
	{
		if(this->pool_list[j].type==0)
		{
			std::cout<<"pool index="<<pool_list[j].index<<std::endl;
			this->pool_list[j].type=1;
			this->pool_list[j].index=j;

			return pool_list[j];
		}
	}

	//没有可用的TcpConnectionPtr
	CONNECTED  pool;
	pool.type=2;
	return pool;
}

ConnectionPool::~ConnectionPool()
{
}