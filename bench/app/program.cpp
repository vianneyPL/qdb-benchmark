#include <bench/app/program.hpp>
#include <bench/framework/test_runner.hpp>

#include <iostream>

void bench::app::program::run() 
{
    parse_command_line();

    std::cout << "quasardb cluster benchmarking tool" << std::endl;

    switch (_mode)
    {
        case mode::normal:
            prepare_schedule();
            print_schedule();
            run_tests();
            break;

        case mode::help:
            show_help();
            break;

        case mode::version:
            break;
    }
}

void bench::app::program::parse_command_line()
{
    bool version            = _cmd_line.get_flag    ("-v", "--version", "Display program version and exists");
    bool help               = _cmd_line.get_flag    ("-h", "--help",    "Display program help and exists");
    _settings.cluster_uri   = _cmd_line.get_string  ("-c", "--cluster", "Set cluster URI", "qdb://127.0.0.1:2836");
    _settings.thread_counts = _cmd_line.get_integers("",   "--threads", "Set number of threads", "1,4,16");
    _settings.content_sizes = _cmd_line.get_integers("",   "--sizes",   "Set contents sizes", "1,1000,1000000");

    _mode = 
        version ? mode::version :
        help ? mode::help :
        mode::normal;
}

void bench::app::program::prepare_schedule()
{
    test_config config;
    config.cluster_uri = _settings.cluster_uri;

    for (auto& test : _test_pool)
    {
        for (int thread_count : _settings.thread_counts)
        {
            config.thread_count = thread_count;
            if (test->info().size_dependent)
            {
                for (int content_size : _settings.content_sizes)
                {
                    config.content_size = content_size;
                    _schedule.emplace_back(test->instanciate(config)); 
                }
            }
            else
            {
                config.content_size = 0;
                _schedule.emplace_back(test->instanciate(config)); 
            }
        }
    }
}

void bench::app::program::print_schedule()
{
    std::cout << "Using the following settings:" << std::endl;
    std::cout << " - Cluster: " << _settings.cluster_uri << std::endl;
    std::cout << "The following test will be performed: " << std::endl; 
    for (unsigned i=0; i<_schedule.size(); i++)
    {
        auto& test = _schedule[i];
        std::cout << i << ". " << test->info().id;
        std::cout << ", threads=" << test->config().thread_count;
        if (test->info().size_dependent)
            std::cout << ", size=" << test->config().content_size;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void bench::app::program::run_tests()
{    
    for (unsigned i=0; i<_schedule.size(); i++)
    {
        auto& test = _schedule[i];
        std::cout << "Now running test " << i+1 << "/" << _schedule.size() << ":" << std::endl;
        std::cout << " - test = " << test->info().id << " (" << test->info().description << ")" << std::endl;
        std::cout << " - thread count = " << test->config().thread_count << std::endl;
        if (test->info().size_dependent)
            std::cout << " - content size = " << test->config().content_size << std::endl;

        bench::framework::run_test(*test);
        std::cout << "Done " << std::endl << std::endl;
    }    
}

void bench::app::program::show_help()
{
    std::cout << "Available command line options:" << std::endl;
    std::cout << _cmd_line.help();

    std::cout << "Available tests:" << std::endl;
    for(auto& test : _test_pool)
    {
        std::cout << " - " << test->info().id << ":" << std::endl;
        std::cout << "   " << test->info().description << std::endl;
    }
}
