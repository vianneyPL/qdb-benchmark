#include <bench/app/settings.hpp>
#include <utils/command_line.hpp>

namespace bench
{
namespace app
{

static size_t parse_size(const std::string & s)
{
    switch (s.back())
    {
    case 'K':
    case 'k':
        return std::stoi(s) << 10;

    case 'M':
    case 'm':
        return std::stoi(s) << 20;

    case 'G':
    case 'g':
        return std::stoi(s) << 30;

    default:
        return std::stoi(s);
    }
}

settings parse_command_line(int argc, const char ** argv)
{
    utils::command_line cmd_line(argc, argv),
        bool version = cmd_line.get_flag("-v", "--version", "Display program version and exists");

    bool help = cmd_line.get_flag("-h", "--help", "Display program help and exists");

    s.cluster_uri = cmd_line.get_string("-c", "--cluster", "Set cluster URI", "qdb://127.0.0.1:2836");
    s.pause =
        std::chrono::seconds(cmd_line.get_integer("-p", "--pause", "Set the delay between each test, in seconds", "2"));
    s.duration = std::chrono::seconds(
        cmd_line.get_integer("-d", "--duration", "Set the duration of each test, in seconds", "2"));
    s.snmp_peers = cmd_line.get_strings("-s", "--snmp", "Set SNMP peers");
    s.thread_counts = cmd_line.get_integers("", "--threads", "Set number of threads", "1,2,4,8,16,32");
    s.content_sizes = cmd_line.get_values<std::size_t>("", "--sizes", "Set contents sizes",
                                                       "1,10,100,1K,10K,100K,1M,10M", parse_size);
    s.tests = cmd_line.get_strings("", "--tests", "Select the tests to run (default=all)");

    if (version) std::exit(0);
    if (help)
    {
        show_help();
        std::exit(0);
    }

    return s;
}

bool program::should_run_test(std::string id) const
{
    if (_settings.tests.empty()) return true;

    return std::find(_settings.tests.begin(), _settings.tests.end(), id) != _settings.tests.end();
}

void program::prepare_schedule()
{
    test_config config;
    config.cluster_uri = _settings.cluster_uri;
    config.duration = _settings.duration;

    for (auto & test_class : _test_pool)
    {
        if (!should_run_test(test_class->id)) continue;

        for (auto thread_count : _settings.thread_counts)
        {
            config.thread_count = thread_count;
            if (test_class->size_dependent)
            {
                for (auto content_size : _settings.content_sizes)
                {
                    config.content_size = content_size;
                    _schedule.emplace_back(create_test_instance(*test_class, config));
                }
            }
            else
            {
                config.content_size = 0;
                _schedule.emplace_back(create_test_instance(*test_class, config));
            }
        }
    }

    _logger.schedule(_schedule);
}

void program::run_tests()
{
    for (auto i = 0u; i < _schedule.size(); i++)
    {
        auto & test_instance = _schedule[i];

        _logger.test_started(i + 1, _schedule.size(), test_instance);
        framework::run_test(test_instance);
        _logger.test_finished(i + 1, _schedule.size(), test_instance);

        std::this_thread::sleep_for(_settings.pause);
    }
}

void program::save_jsonp_report()
{
    report::jsonp report;
    for (const auto & test : _schedule)
    {
        report.add_test(test);
    }
    report.save();
}

void program::show_help()
{
    std::cout << "Available command line options:" << std::endl;
    std::cout << cmd_line.help();

    std::cout << "Available tests:" << std::endl;
    for (const auto & test_class : _test_pool)
    {
        std::cout << " - " << test_class->id << ":" << std::endl;
        std::cout << "   " << test_class->description << std::endl;
    }
}

} // namespace app
} // namespace bench
