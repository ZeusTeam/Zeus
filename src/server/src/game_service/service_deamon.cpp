#include "service_deamon.h"

#ifdef __cplusplus
extern "C"
{
#endif
    ZUES_DECLSPEC_EXPORT Zues::Service* create()
    {
        return new ServiceDeamon;
    }
#ifdef __cplusplus
}
#endif

ServiceDeamon::ServiceDeamon()
{

}

ServiceDeamon::~ServiceDeamon()
{

}

void ServiceDeamon::start(const std::string& serviceName)
{
    _serviceName = serviceName;
}

void ServiceDeamon::stop()
{

}

const std::string& ServiceDeamon::serviceName() const
{
    return _serviceName;
}