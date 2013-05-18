#ifndef SERVICE_H_
#define SERVICE_H_

#include <common.h>

#if defined(__cplusplus) || (defined(_MSC_VER))
#   define ZUES_DECLSPEC_EXPORT __declspec(dllexport)
#   define ZUES_DECLSPEC_IMPORT __declspec(dllimport)
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x550)
#   define ZUES_DECLSPEC_EXPORT __global
#   define ZUES_DECLSPEC_IMPORT
#else
#   define ZUES_DECLSPEC_EXPORT /**/
#   define ZUES_DECLSPEC_IMPORT /**/
#endif

namespace Zues
{
class Service
{
public:
    virtual void start(const std::string& serviceName) = 0;
    virtual void stop() = 0;
};

}

#endif