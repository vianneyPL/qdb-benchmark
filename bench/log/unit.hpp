#pragma once

#include <sstream>
#include <iomanip>

namespace bench
{
namespace log
{
class unit
{
    static std::string ftos(double value, int precision)
    {
        std::ostringstream s;

        s << std::fixed << std::setprecision(precision) << value;
        return s.str();
    }

    static std::string format(double value, int mult, std::string unit)
    {
        if (value < mult && -value < mult) return ftos(value, 0) + " " + unit;
        value /= mult;
        if (value < mult && -value < mult) return ftos(value, 2) + " k" + unit;
        value /= mult;
        if (value < mult && -value < mult) return ftos(value, 2) + " M" + unit;
        value /= mult;
        return ftos(value, 2) + " G" + unit;
    }

public:
    static std::string byte(double value)
    {
        return format(value, 1024, "B");
    }

    static std::string byte_per_second(double value)
    {
        return format(value, 1024, "B/s");
    }

    static std::string hertz(double value)
    {
        return format(value, 1000, "Hz");
    }

    static std::string none(double value)
    {
        return format(value, 1000, "");
    }

    static std::string milliseconds(double value)
    {
        return format(value / 1000, 1000, "s");
    }
};
}
}
