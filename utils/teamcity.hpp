#pragma once

#include <string>

namespace utils
{
namespace teamcity
{
void block_opened(std::string name);
void block_closed(std::string name);
void build_problem(std::string text);
void build_statistic(std::string name, double value);
void message(std::string message);
void test_failed(std::string name, std::string message);
void test_failed(std::string name, std::string message, std::string details);
void test_finished(std::string name);
void test_started(std::string name);
}
}