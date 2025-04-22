#ifndef STARFLEET_COMMAND_JSONCOLOURMAPPING_HPP
#define STARFLEET_COMMAND_JSONCOLOURMAPPING_HPP
#include "PredefinedColours.hpp"
#include <SFML/Graphics/Color.hpp>
#include <unordered_map>
#include <string>

namespace Chilli
{
    class JsonColourMapping
    {
    public:
        static sf::Color GetColourFromStringName(const std::string &colourName)
        {
            static const std::unordered_map<std::string, sf::Color> colourMap =
            {
                    {"BLUE",   Chilli::PredefinedColours::LIGHTBLUE},
                    {"RED",    Chilli::PredefinedColours::LIGHTRED},
                    {"GREEN",  Chilli::PredefinedColours::LIGHTGREEN},
                    {"ORANGE", Chilli::PredefinedColours::LIGHTORANGE},
                    {"YELLOW", Chilli::PredefinedColours::YELLOW}
            };

            /// Return the queried colour if it exists, otherwise return LIGHTBLUE by default
            auto iter = colourMap.find(colourName);
            return (iter != colourMap.end()) ? iter->second : Chilli::PredefinedColours::LIGHTBLUE;
        }
    };
}

#endif //STARFLEET_COMMAND_JSONCOLOURMAPPING_HPP
