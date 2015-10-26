#include <utils/teamcity.hpp>

#include <iostream>

void utils::teamcity::block_opened(const std::string & name)
{
    // CAUTION: TeamCity 9.1.1 incorrectly reports tests as succeed when it includes blocks
    std::cout << "##teamcity[blockOpened name='" << name << "']" << std::endl;
}

void utils::teamcity::block_closed(const std::string & name)
{
    // CAUTION: TeamCity 9.1.1 incorrectly reports tests as succeed when it includes blocks
    std::cout << "##teamcity[blockClosed name='" << name << "']" << std::endl;
}

void utils::teamcity::build_problem(const std::string & description)
{
    std::cout << "##teamcity[buildProblem description='" << description << "']" << std::endl;
}

void utils::teamcity::build_statistic(const std::string & name, double value)
{
    std::cout << "##teamcity[buildStatisticValue key='" << name << "' value='" << value << "']"
              << std::endl;
}

void utils::teamcity::message(const std::string & text)
{
    std::cout << "##teamcity[message text='" << text << "']" << std::endl;
}

void utils::teamcity::progressMessage(const std::string & message)
{
    std::cout << "##teamcity[progressMessage '" << message << "']" << std::endl;
}

void utils::teamcity::test_failed(const std::string & name, const std::string & message)
{
    std::cout << "##teamcity[testFailed name='" << name << "' message='" << message << "']"
              << std::endl;
}

void utils::teamcity::test_failed(const std::string & name,
                                  const std::string & message,
                                  const std::string & details)
{
    std::cout << "##teamcity[testFailed name='" << name << "' message='" << message << "' details='"
              << details << "']" << std::endl;
}

void utils::teamcity::test_finished(const std::string & name)
{
    std::cout << "##teamcity[testFinished name='" << name << "']" << std::endl;
}

void utils::teamcity::test_started(const std::string & name)
{
    std::cout << "##teamcity[testStarted name='" << name << "' captureStandardOutput='true']"
              << std::endl;
}
