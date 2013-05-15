#include <boost/program_options.hpp> 
#include <utils/zeus_logger.hpp>
#include <common.h>
#include "service.h"
#include "share_library.hpp"

using namespace ZLogger;

class ServiceBox
{

public:
    int doMain(int argc, char* argv[])
    {
        using namespace boost::program_options;

        options_description desc("Options:");
        desc.add_options()
            ("config,c", value<std::string>(), "Input service configuration file.")
            ("help,h", "Show this message.")
            ;

        variables_map vm;        
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);  

        if (vm.size() == 0)
        {
            std::cout << desc;
            return 0;
        }

        if (vm.count("help") > 0) {
            std::cout << desc;
        }

        if (vm.count("config") > 0)
        {
            std::string filename = vm["config"].as<std::string>();
            if (!filename.empty())
            {
                return loadServerConfig(filename);
            }
        }

#ifdef _WIN32
        system("pause");
#endif
        return 0;
    }

private:
    int loadServerConfig(std::string filename)
    {
        WD("Loading config [" << filename << "]");
        return 0;
    }
};

int main(int argc, char* argv[])
{
    ServiceBox serviceBox;
    return serviceBox.doMain(argc, argv);
}
