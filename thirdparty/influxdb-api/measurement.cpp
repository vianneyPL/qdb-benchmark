#include "measurement.hpp"
#include <cppformat/ostream.h>

namespace idb
{
namespace api
{
namespace measurement
{
measurement & measurement::operator<<(const tag & t)
{
    if (m_state == WritingState::fields)
    {
        std::runtime_error(std::string("Measurement should not write tags after fields."));
    }
    else if (m_state == WritingState::timestamp)
    {
        std::runtime_error(std::string("Measurement should not write tags after timestamp."));
    }
    m_line += ",";
    m_line += t.key();
    m_line += "=";
    m_line += t.value();
    m_state = WritingState::tags;
    return *this;
}
measurement & measurement::operator<<(tag && t)
{
    if (m_state == WritingState::fields)
    {
        std::runtime_error(std::string("Measurement should not write tags after fields."));
    }
    else if (m_state == WritingState::timestamp)
    {
        std::runtime_error(std::string("Measurement should not write tags after timestamp."));
    }
    m_line += ",";
    m_line += std::move(t.key());
    m_line += "=";
    m_line += std::move(t.value());
    m_state = WritingState::tags;
    return *this;
}

// measurement&    measurement::operator<<(const field &f)
// measurement&    measurement::operator<<(field &&f)

measurement & measurement::operator<<(const idb_time_t & t)
{
    if (m_state == WritingState::timestamp)
    {
        std::runtime_error(std::string("Measurement should have none or only one timestamp."));
    }
    else if (m_state != WritingState::fields)
    {
        std::runtime_error(std::string("Measurement should have at least one field."));
    }
    m_line += " ";
    m_line += std::to_string(t);
    m_state = WritingState::timestamp;
    return *this;
}
measurement & measurement::operator<<(idb_time_t && t)
{
    if (m_state == WritingState::timestamp)
    {
        std::runtime_error(std::string("Measurement should have none or only one timestamp."));
    }
    else if (m_state != WritingState::fields)
    {
        std::runtime_error(std::string("Measurement should have at least one field."));
    }
    m_line += " ";
    m_line += std::to_string(std::move(t));
    m_state = WritingState::timestamp;
    return *this;
}

// const std::string measurement::line() const
// {
//     if (m_fields.empty())
//     { std::runtime_error(std::string("measurement should have at least one field set.")); }

//     fmt::MemoryWriter line;
//     line << std::quoted(m_name);
//     for (const auto &t : m_tags)
//     { line << "," << std::quoted(t.key()) << "=" << std::quoted(t.value()); }
//     auto count = 0;
//     for (const auto &f : m_fields)
//     {
//         if (count > 0)
//         { line << ","; }
//         else
//         { line << " "; }
//         line << std::quoted(f.key()) << "=" << f.value();
//         ++count;
//     }
//     return line.str();
// }
}
}
}
