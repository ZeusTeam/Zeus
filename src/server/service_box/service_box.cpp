#include <boost/program_options.hpp> 
#include <common.h>
#include "service.h"
#include "share_library.hpp"

class ServiceBox
{

public:
    int main(int argc, char* argv[])
    {
        const std::string arg_long_help = "help";

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
            return 0;
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
        return 0;
    }
};

int main(int argc, char* argv[])
{
    ServiceBox serviceBox;
    return serviceBox.main(argc, argv);
}
