#include "Utility/CustomFonts.hpp"

// Static member definitions
sf::Font Chilli::CustomFonts::orbitronBoldFont;
sf::Font Chilli::CustomFonts::orbitronRegularFont;

const sf::Font& Chilli::CustomFonts::GetRegularFont() // OPTIMISE: Loads the font EVERY time this method is called!
{
    if(!orbitronRegularFont.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        std::cout << "Orbitron Regular font failed to load from file." << std::endl;
    }
    return orbitronRegularFont;
}

const sf::Font& Chilli::CustomFonts::GetBoldFont() // OPTIMISE: Loads the font EVERY time this method is called!
{
    if(!orbitronBoldFont.loadFromFile("Resources/Fonts/Orbitron/Orbitron-Bold.ttf"))
    {
        std::cout << "Orbitron Bold font failed to load from file." << std::endl;
    }
    return orbitronBoldFont;
}



