#include "Utility/CustomFonts.hpp"

bool Chilli::CustomFonts::LoadFonts()
{
    bool success = true;

    if (!orbitronRegularFont.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        std::cout << "Orbitron Regular font failed to load from file." << std::endl;
        success = false;
    }

    if (!orbitronBoldFont.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Bold.ttf"))
    {
        std::cout << "Orbitron Bold font failed to load from file." << std::endl;
        success = false;
    }

    _fontsLoaded = success;
    return success;
}

const sf::Font& Chilli::CustomFonts::GetRegularFont()
{
    if(! _fontsLoaded)
    {
        LoadFonts();
    }
    return orbitronRegularFont;
}

const sf::Font& Chilli::CustomFonts::GetBoldFont()
{
    if(! _fontsLoaded)
    {
        LoadFonts();
    }
    return orbitronBoldFont;
}




