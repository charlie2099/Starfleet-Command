#include "Button.hpp"

Button::Button(const std::string& filepath)
{
    spriteComponent.loadSprite(filepath);
    idle_colour = sf::Color::White;
}

void Button::update(sf::RenderWindow &window)
{
    auto mouse_pos_relative = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mouse_pos_world = window.mapPixelToCoords(mouse_pos_relative); // Mouse position translated into world coordinates

    // default colour
    spriteComponent.getSprite().setColor(idle_colour);

    // if mouse within button bounds, do something
    if(spriteComponent.getSprite().getGlobalBounds().contains(mouse_pos_world))
    {
        spriteComponent.getSprite().setColor(active_colour);
        is_within_bounds = true;
    }
    else
    {
        is_within_bounds = false;
    }
}

void Button::render(sf::RenderWindow &window)
{
    window.draw(spriteComponent.getSprite());
}

void Button::setActiveColour(sf::Color colour)
{
    active_colour = colour;
}

SpriteComponent &Button::getSpriteComponent()
{
    return spriteComponent;
}


