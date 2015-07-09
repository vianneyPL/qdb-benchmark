#include "test_pool.hpp"
#include "command_line.hpp"

#include <iostream>

using namespace qdb::bench::app;

int main(int argc, const char* argv[]) 
{
    qdb::bench::tests::test_pool tests;
    command_line_parser command_line(argc, argv);

    std::cout << "quasardb cluster benchmarking tool" << std::endl;    

    if (command_line.options().help)
    {

        std::cout << command_line.help();

        std::cout << "Available tests:" << std::endl;
        for(auto& test : tests)
        {
            std::cout << " - " << test.info().id << ":" << std::endl;
            std::cout << "   " << test.info().description << std::endl;
        }

        return 0;
    }   

    if (command_line.options().version)
    {
        return 0;
    }

    std::cout << "Performing tests on " << command_line.options().cluster_uri << std::endl;
}