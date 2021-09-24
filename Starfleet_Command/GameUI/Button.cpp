#include "Button.hpp"

Button::Button(const std::string &filepath)
{
    initTexture(filepath);
    sprite.setTexture(texture);
}

void Button::render(sf::RenderWindow &window)
{
    window.draw(sprite);
}

bool Button::initTexture(const std::string &filepath)
{
    if(!texture.loadFromFile(filepath))
    {
        return false;
    }
    return true;
}
