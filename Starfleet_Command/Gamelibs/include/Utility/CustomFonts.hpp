#ifndef STARFLEET_COMMAND_CUSTOMFONTS_HPP
#define STARFLEET_COMMAND_CUSTOMFONTS_HPP
#include <SFML/Graphics/Font.hpp>
#include <iostream>

namespace Chilli
{
    class CustomFonts
    {
    public:
        static const sf::Font& GetRegularFont();
        static const sf::Font& GetBoldFont();

    private:
        static bool LoadFonts();
        inline static bool _fontsLoaded = false;
        inline static sf::Font orbitronRegularFont;
        inline static sf::Font orbitronBoldFont;
    };
}

#endif //STARFLEET_COMMAND_CUSTOMFONTS_HPP
