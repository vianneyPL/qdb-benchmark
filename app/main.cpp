#include "test_pool.hpp"
#include "command_line.hpp"
#include "test_scheduler.hpp"

#include <iostream>

using namespace qdb::bench;
using namespace qdb::bench::app;
using namespace qdb::bench::framework;

int main(int argc, const char* argv[]) 
{
    try
    {
        qdb::bench::tests::test_pool test_pool;  
        command_line_parser command_line(argc, argv);

        std::cout << "quasardb cluster benchmarking tool" << std::endl;    

        if (command_line.options().help)
        {

            std::cout << command_line.help();

            std::cout << "Available tests:" << std::endl;
            for(auto& test : test_pool)
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

        std::cout << "Using the following settings:" << std::endl;
        std::cout << " - Cluster: " << command_line.options().cluster_uri << std::endl;

        test_scheduler scheduler;
        scheduler.set_threads(command_line.options().threads);
        scheduler.set_cluster(command_line.options().cluster_uri);
        for (const test_class& test : test_pool)
        {
            scheduler.add_test_class(test);
        }
        
        std::cout << "The following test will be performed: " << std::endl; 
        scheduler.for_each([](const test_instance& x)
        {
            std::cout << " - " << x.info().id << " with " << x.config().thread_count << " threads " << std::endl; 
        });
    }
    catch (std::exception &e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

}