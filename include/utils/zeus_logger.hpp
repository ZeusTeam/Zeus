#ifndef ZEUS_LOGGER_H_
#define ZEUS_LOGGER_H_

#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <utils/Singleton.h>
#include <iosfwd>

using namespace log4cplus;
using namespace log4cplus::helpers;

namespace ZLogger
{
#ifdef UNICODE
typedef std::wstring tstring;
typedef std::wostringstream tstrstream;   
#else
typedef std::string tstring;
typedef std::ostringstream tstrstream;
#endif
}

class ZeusLogger : public Singleton<ZeusLogger>
{
    friend class Singleton<ZeusLogger>;

public:
    bool initLogger(const ZLogger::tstring& configFilename, const ZLogger::tstring& instanceName)
    {
        log4cplus::initialize();
        PropertyConfigurator::doConfigure(configFilename);
        _logger = Logger::getInstance(instanceName);
        _logger.isEnabledFor(ALL_LOG_LEVEL);

        return true;
    }

    void debug(const ZLogger::tstring& log)
    {
        LOG4CPLUS_DEBUG(_logger, log);
    }

    void warn(const ZLogger::tstring& log)
    {
        LOG4CPLUS_WARN(_logger, log);
    }

    void info(const ZLogger::tstring& log)
    {
        LOG4CPLUS_INFO(_logger, log);
    }

    void trace(const ZLogger::tstring& log)
    {
        LOG4CPLUS_TRACE(_logger, log);
    }

    void error(const ZLogger::tstring& log)
    {
        LOG4CPLUS_ERROR(_logger, log);
    }

    void fatal(const ZLogger::tstring& log)
    {
        LOG4CPLUS_FATAL(_logger, log);
    }

private:
    Logger _logger;
};

template<> ZeusLogger* Singleton<ZeusLogger>::m_pInst = NULL;

#define INIT_LOGGER(x, o)       \
    ZeusLogger::Instance()->initLogger(LOG4CPLUS_TEXT(x), LOG4CPLUS_TEXT(o))

#define DEFINE_OSTREAM(x)       \
    ZLogger::tstrstream os;     \
    os << x;

#define WD(x)                   \
{                               \
    DEFINE_OSTREAM(x)           \
    ZeusLogger::Instance()->debug(os.str()); \
}

#define WW(x)                   \
{                               \
    DEFINE_OSTREAM(x)           \
    ZeusLogger::Instance()->warn(os.str()); \
}

#define WI(x)                   \
{                               \
    DEFINE_OSTREAM(x)           \
    ZeusLogger::Instance()->info(os.str()); \
}

#define WT(x)                   \
{                               \
    DEFINE_OSTREAM(x)           \
    ZeusLogger::Instance()->trace(os.str()); \
}

#define WE(x)                   \
{                               \
    DEFINE_OSTREAM(x)           \
    ZeusLogger::Instance()->error(os.str()); \
}

#define WF(x)                   \
{                               \
    DEFINE_OSTREAM(x)           \
    ZeusLogger::Instance()->fatal(os.str()); \
}

#endif