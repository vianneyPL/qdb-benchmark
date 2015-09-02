#include <utils/teamcity.hpp>

#include <iostream>

void utils::teamcity::block_opened(std::string name)
{
    // CAUTION: TeamCity 9.1.1 incorrectly reports tests as succeed when it includes blocks
    std::cout << "##teamcity[blockOpened name='" << name << "']" << std::endl;
}

void utils::teamcity::block_closed(std::string name)
{
    // CAUTION: TeamCity 9.1.1 incorrectly reports tests as succeed when it includes blocks
    std::cout << "##teamcity[blockClosed name='" << name << "']" << std::endl;
}

void utils::teamcity::build_problem(std::string description)
{
    std::cout << "##teamcity[buildProblem description='" << description << "']" << std::endl;
}

void utils::teamcity::build_statistic(std::string name, double value)
{
    std::cout << "##teamcity[buildStatisticValue key='" << name << "' value='" << value << "']"
              << std::endl;
}

void utils::teamcity::message(std::string text)
{
    std::cout << "##teamcity[message text='" << text << "']" << std::endl;
}

void utils::teamcity::test_failed(std::string name, std::string message)
{
    std::cout << "##teamcity[testFailed name='" << name << "' message='" << message << "']"
              << std::endl;
}

void utils::teamcity::test_failed(std::string name, std::string message, std::string details)
{
    std::cout << "##teamcity[testFailed name='" << name << "' message='" << message << "' details='"
              << details << "']" << std::endl;
}

void utils::teamcity::test_finished(std::string name)
{
    std::cout << "##teamcity[testFinished name='" << name << "']" << std::endl;
}

void utils::teamcity::test_started(std::string name)
{
    std::cout << "##teamcity[testStarted name='" << name << "' captureStandardOutput='true']"
              << std::endl;
}
