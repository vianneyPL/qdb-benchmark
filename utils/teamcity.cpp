#include <utils/teamcity.hpp>

#include <iostream>

void utils::teamcity::build_problem(std::string description)
{
    std::cout << "##teamcity[buildProblem description='" << description << "']" << std::endl;
}

void utils::teamcity::build_statistic(std::string name, double value)
{
    std::cout << "##teamcity[buildStatisticValue key='" << name << "' value='" << value << "']"
              << std::endl;
}

void utils::teamcity::test_failed(std::string name, std::string message)
{
    std::cout << "##teamcity[testFailed name='" << name << "', message='" << message << "']"
              << std::endl;
}

void utils::teamcity::test_failed(std::string name, std::string message, std::string details)
{
    std::cout << "##teamcity[testFailed name='" << name << "', message='" << message
              << "' details='" << details << "']" << std::endl;
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
