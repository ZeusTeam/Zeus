#include <common.h>
#include <service_box/service.h>

class ServiceDeamon : public Zues::Service
{
public:
    ServiceDeamon();
    virtual ~ServiceDeamon();

public:
    virtual void start(const std::string& serviceName);
    virtual void stop();

public:
    const std::string& serviceName() const;

private:
    std::string _serviceName;
};