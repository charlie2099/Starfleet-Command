#include "Panel.hpp"

Panel::Panel()
{
    loadTextures();
    loadFonts();

    // default origin and design for panel upon construction
    text.setString("Text");
    text.setFont(font_regular);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(400, 400);

    panel.setTexture(&panel_texture);
    auto panel_offset = 50.0F;
    panel.setSize({text.getGlobalBounds().width + panel_offset*2, text.getGlobalBounds().height + panel_offset});
    panel.setPosition(text.getPosition().x - panel_offset, (text.getGlobalBounds().top + text.getGlobalBounds().height/2) - panel.getGlobalBounds().height/2);
}

bool Panel::loadTextures()
{
    if (!panel_texture.loadFromFile("images/panel_image.png"))
    {
        return false;
    }
    return true;
}

/// Unnecessary to load fonts which may not even be used
bool Panel::loadFonts()
{
    if(!font_regular.loadFromFile("fonts/Orbitron/Orbitron-Regular.ttf"))
    {
        return false;
    }
    /*if(!font_bold.loadFromFile("fonts/Orbitron/Orbitron-Bold.ttf"))
    {
        return false;
    }*/
    return true;
}

void Panel::render(sf::RenderWindow& window)
{
    window.draw(panel);
    window.draw(text);
}
