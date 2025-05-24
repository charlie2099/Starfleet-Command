#ifndef STARFLEET_COMMAND_COLOUR_HPP
#define STARFLEET_COMMAND_COLOUR_HPP
#include "SFML/Graphics/Color.hpp"

namespace Chilli
{
    struct Colour
    {
        inline static sf::Color LIGHTBLUE {153, 210, 242};
        inline static sf::Color LIGHTGREEN {91, 239, 170};
        inline static sf::Color LIGHTRED {252, 119, 116};
        inline static sf::Color LIGHTPURPLE {153, 171, 242};
        inline static sf::Color LIGHTPINK {242, 153, 226};
        inline static sf::Color LIGHTERGREEN {153, 242, 203};
        inline static sf::Color LIGHTORANGE {253, 172, 101};
        inline static sf::Color ORANGE {252, 162, 66};
        inline static sf::Color YELLOW {252, 252, 136};
        inline static sf::Color TURQUOISE {22, 155, 164};
        inline static sf::Color GRAY {180, 180, 180};
        inline static sf::Color DARKGRAY {90, 90, 90};
    };
}

#endif //STARFLEET_COMMAND_COLOUR_HPP
