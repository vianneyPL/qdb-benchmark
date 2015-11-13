#include <snmp/sys_info.hpp>

#include <iomanip>
#include <iostream>
#include <thread>

int main()
{
    try
    {
        snmp::sys_info sys_info("127.0.0.1");

        sys_info.connect();

        for (;;)
        {
            sys_info.update();

            std::cout << std::left << std::setw(24) << "[NAME]" << std::setw(18) << "[TYPE]"
                      << std::setw(14) << "[SIZE]" << std::setw(14) << "[USED]" << std::endl;

            for (auto s : sys_info.storages())
            {
                std::cout << std::left << std::setw(24) << s.name() << std::setw(18) << s.type()
                          << std::setw(14) << s.size() * s.allocation_unit() << std::setw(14)
                          << s.used_space() * s.allocation_unit() << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(5));

            std::cout << std::endl << std::endl << std::endl;
        }

        sys_info.close();
        return 0;
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
}
