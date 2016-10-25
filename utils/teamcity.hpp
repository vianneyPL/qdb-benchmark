#pragma once

#include <string>

namespace utils
{
namespace teamcity
{
void block_opened(const std::string & name);
void block_closed(const std::string & name);

void build_problem(const std::string & text);
void build_statistic(const std::string & name, double value);

void message(const std::string & text);
void message(const std::string & text, const std::string & error_details);
void progressMessage(const std::string & message);

void test_failed(const std::string & name, const std::string & message);
void test_failed(const std::string & name, const std::string & message, const std::string & details);
void test_finished(const std::string & name);
void test_started(const std::string & name);
}
}
