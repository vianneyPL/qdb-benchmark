#include <bench/app/command_line.hpp>
#include <utils/command_line.hpp>

#include <algorithm>
#include <iomanip>
#include <iostream>

static size_t parse_size(const std::string & s)
{
    switch (s.back())
    {
    case 'K':
    case 'k': return std::stoi(s) << 10;

    case 'M':
    case 'm': return std::stoi(s) << 20;

    case 'G':
    case 'g': return std::stoi(s) << 30;

    default: return std::stoi(s);
    }
}

void bench::app::command_line::parse(int argc, const char ** argv)
{
    utils::command_line parser(argc, argv);

    std::cout << "quasardb cluster benchmarking tool" << std::endl;

    bool version = parser.get_flag("-v", "--version", "Display program version and exists");
    bool help = parser.get_flag("-h", "--help", "Display program help and exists");
    _settings.cluster_uri =
        parser.get_string("-c", "--cluster", "Set cluster URI", "qdb://127.0.0.1:2836");
    _settings.pause = std::chrono::seconds(
        parser.get_integer("-p", "--pause", "Set the delay between each test, in seconds", "2"));
    _settings.duration = std::chrono::seconds(
        parser.get_integer("-d", "--duration", "Set the duration of each test, in seconds", "2"));
    _settings.thread_counts =
        parser.get_integers("", "--threads", "Set number of threads", "1,2,4,8,16,32");
    _settings.content_sizes = parser.get_values<std::size_t>(
        "", "--sizes", "Set contents sizes", "1,10,100,1K,10K,100K,1M,10M", parse_size);
    _settings.tests = parser.get_strings("", "--tests", "Select the tests to run (default=all)");

    if (help)
    {
        std::cout << "Available command line options:" << std::endl;
        std::cout << parser.help();

        std::cout << "Available tests:" << std::endl;
        for (auto & test_class : _test_pool)
        {
            std::cout << "  " << std::left << std::setw(32) << test_class->id << " "
                      << test_class->description << std::endl;
        }

        std::exit(0);
    }

    if (version)
    {
        std::exit(0);
    }
}
