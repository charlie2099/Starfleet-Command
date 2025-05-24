#ifndef STARFLEET_COMMAND_JSONCOLOURMAPPING_HPP
#define STARFLEET_COMMAND_JSONCOLOURMAPPING_HPP
#include "Colour.hpp"
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
                    {"BLUE",   Chilli::Colour::LIGHTBLUE},
                    {"RED",    Chilli::Colour::LIGHTRED},
                    {"GREEN",  Chilli::Colour::LIGHTGREEN},
                    {"LIGHTERGREEN",  Chilli::Colour::LIGHTERGREEN},
                    {"ORANGE", Chilli::Colour::LIGHTORANGE},
                    {"YELLOW", Chilli::Colour::YELLOW},
                    {"PURPLE", Chilli::Colour::LIGHTPURPLE},
                    {"PINK", Chilli::Colour::LIGHTPINK}
            };

            /// Return the queried colour if it exists, otherwise return LIGHTBLUE by default
            auto iter = colourMap.find(colourName);
            return (iter != colourMap.end()) ? iter->second : Chilli::Colour::LIGHTBLUE;
        }
    };
}

#endif //STARFLEET_COMMAND_JSONCOLOURMAPPING_HPP
