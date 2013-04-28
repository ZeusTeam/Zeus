#include <common.h>

namespace Zues
{

class IService
{
public:
    IService();
    virtual ~IService() = 0;

public:
    virtual void start(const std::string& serviceName) = 0;
    virtual void stop() = 0;

public:
    const std::string& serviceName() const
    {
        return _serviceName;
    }

private:
    std::string _serviceName;
};

}