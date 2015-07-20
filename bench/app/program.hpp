#pragma once

#include <bench/app/settings.hpp>
#include <bench/tests/test_pool.hpp>
#include <bench/core/test_instance.hpp>
#include <utils/command_line.hpp>

namespace bench {
namespace app {

enum class mode { normal, help, version };
  
class program 
{    
  public:
    program(int argc, const char** argv)
        : _cmd_line(argc, argv)
    {
    }

    void run();

  private:
    void parse_command_line();
    void prepare_schedule();
    void print_schedule();
    void run_tests();
    void save_jsonp_report();
    void show_help();
    bool should_run_test(std::string) const;

    bench::app::mode _mode;
    bench::app::settings _settings;
    bench::tests::test_pool _test_pool;
    utils::command_line _cmd_line;
    std::vector<test_instance> _schedule;
};

}}