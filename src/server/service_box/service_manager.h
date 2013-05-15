#ifndef SERVICE_MANAGER_H_
#define SERVICE_MANAGER_H_

#include <common.h>

class ServiceManager
{
public:
    ServiceManager();
    virtual ~ServiceManager();

public:
    bool start(const std::string& service, const std::string& entryPoint)
    {
    
    }

};

#endif