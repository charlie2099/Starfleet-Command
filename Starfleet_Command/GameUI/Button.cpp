#include "Button.hpp"

Button::Button(const std::string& filepath)
{
    spriteComponent.LoadSprite(filepath);
}

void Button::Update(sf::RenderWindow &window)
{
    auto mouse_pos_relative = sf::Mouse::getPosition(window); // Mouse position relative to the window
    auto mouse_pos_world = window.mapPixelToCoords(mouse_pos_relative); // Mouse position translated into world coordinates

    // if mouse within button bounds, do something
    if(spriteComponent.GetSprite().getGlobalBounds().contains(mouse_pos_world))
    {
        is_within_bounds = true;
    }
    else
    {
        is_within_bounds = false;
    }
}

void Button::Render(sf::RenderWindow &window)
{
    window.draw(spriteComponent.GetSprite());
}

SpriteComponent &Button::GetSpriteComponent()
{
    return spriteComponent;
}


