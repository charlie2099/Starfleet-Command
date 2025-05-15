#ifndef STARFLEET_COMMAND_STRINGFORMATTER_HPP
#define STARFLEET_COMMAND_STRINGFORMATTER_HPP
#include <sstream>
#include <iomanip>

namespace Chilli
{
    class StringFormatter
    {
    public:
        static std::string FormatFloat(float value, int decimalPlaces = 1)
        {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(decimalPlaces) << value;
            return oss.str();
        }
    };
}

#endif //STARFLEET_COMMAND_STRINGFORMATTER_HPP
