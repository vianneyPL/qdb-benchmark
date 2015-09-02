#pragma once

#include <cstdio>
#include <string>

namespace bench
{
namespace tests
{
namespace stdio
{
class fwrite : public test_template<fwrite>
{
public:
    fwrite(bench::test_config config) : test_template(config)
    {
        _filename = utils::get_temporary_filename();
        _content = utils::create_random_string(config.content_size);
    }

    void run_iteration(unsigned long iteration)
    {
        auto fp = std::fopen(_filename.c_str(), "wb");
        size_t n = std::fwrite(const_cast<char *>(_content.c_str()), 1, _content.size(), fp);
        std::fclose(fp);
        if (n != _content.size()) throw std::exception();
    }

    ~fwrite() override
    {
        std::remove(_filename.c_str());
    }

    static std::string name()
    {
        return "stdio_fwrite";
    }

    static std::string description()
    {
        return "Call fwrite() on one file.";
    }

    static bool size_dependent()
    {
        return true;
    }

private:
    std::string _filename;
    std::string _content;
};
}
}
}