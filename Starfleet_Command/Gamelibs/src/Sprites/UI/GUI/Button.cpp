#include "Sprites/UI/GUI/Button.hpp"

Button::Button(const std::string& filepath)
{
    _spriteComponent.LoadSprite(filepath);
    _colour = _spriteComponent.GetSprite().getColor();
}

void Button::Update(sf::RenderWindow &window)
{
    auto mouse_pos_relative = sf::Mouse::getPosition(window); // Mouse _innerPosition relative to the window
    auto mouse_pos_world = window.mapPixelToCoords(mouse_pos_relative); // Mouse _innerPosition translated into world coordinates

    // if mouse within button bounds, do something
    if(_spriteComponent.GetSprite().getGlobalBounds().contains(mouse_pos_world))
    {
        _isHoveredOver = true;
    }
    else
    {
        _isHoveredOver = false;
    }
}

void Button::Render(sf::RenderWindow &window)
{
    window.draw(_spriteComponent.GetSprite());
}

void Button::SetPos(sf::Vector2f pos)
{
    _spriteComponent.SetPos(pos);
}

void Button::SetScale(sf::Vector2f scale)
{
    _spriteComponent.GetSprite().setScale(scale);
}

void Button::SetColour(sf::Color colour)
{
    _spriteComponent.GetSprite().setColor(colour);
    _colour = colour;
}





