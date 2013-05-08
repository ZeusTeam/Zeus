#ifndef ZEUS_NET_EVENT_LOOP_H_
#define ZEUS_NET_EVENT_LOOP_H_

#include <common.h>
#include <boost/noncopyable.hpp>

class EventLoop : boost::noncopyable
{
public:
    EventLoop()
    {
    
    }

    ~EventLoop()
    {
    
    }

public:
    void loop();
};

#endif