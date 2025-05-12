#include "Sprites/UI/GUI/ImageButton.hpp"

ImageButton::ImageButton(const std::string& filepath)
{
    _spriteComponent.LoadSprite(filepath);
    _colour = _spriteComponent.GetSprite().getColor();
}

void ImageButton::EventHandler(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left && _isMouseHoveredOver)
    {
        _isClicked = true;
    }
    else if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left)
    {
        _isClicked = false;
    }
}

void ImageButton::Update(sf::RenderWindow &window)
{
    auto mouse_pos_relative = sf::Mouse::getPosition(window);
    auto mouse_pos_world = window.mapPixelToCoords(mouse_pos_relative);

    if(_spriteComponent.GetSprite().getGlobalBounds().contains(mouse_pos_world))
    {
        _isMouseHoveredOver = true;
    }
    else
    {
        _isMouseHoveredOver = false;
    }
}

void ImageButton::Render(sf::RenderWindow &window)
{
    window.draw(_spriteComponent.GetSprite());
}

void ImageButton::SetPos(sf::Vector2f pos)
{
    _spriteComponent.SetPos(pos);
}

void ImageButton::SetScale(sf::Vector2f scale)
{
    _spriteComponent.GetSprite().setScale(scale);
}

void ImageButton::SetColour(sf::Color colour)
{
    _spriteComponent.GetSprite().setColor(colour);
    _colour = colour;
}





