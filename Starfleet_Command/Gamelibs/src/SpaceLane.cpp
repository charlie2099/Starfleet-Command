#include <SFML/Window/Mouse.hpp>
#include "SpaceLane.hpp"

bool SpaceLane::Init()
{
    _laneRect.setOutlineThickness(2.0F);
    _laneRect.setOutlineColor(sf::Color::Transparent);
    _laneRect.setFillColor(sf::Color(100, 100, 100, 50.0F));
    return true;
}

void SpaceLane::Update(sf::RenderWindow& window, sf::Time deltaTime)
{
    auto mouse_pos_relative = sf::Mouse::getPosition(window); // Mouse _innerPosition relative to the window
    auto mouse_pos_world = window.mapPixelToCoords(mouse_pos_relative); // Mouse _innerPosition translated into world coordinates

    if(_laneRect.getGlobalBounds().contains(mouse_pos_world))
    {
        _isHoveredOver = true;
        //_laneRect.setFillColor(sf::Color(100, 100, 100, 100.0F));
        //_laneRect.setFillColor(sf::Color( 252, 162, 66, 100.0F));
    }
    else
    {
        _isHoveredOver = false;
        //_laneRect.setFillColor(sf::Color(100, 100, 100, 25.0F));
        //_laneRect.setFillColor(sf::Color::Transparent);
    }
}

void SpaceLane::Render(sf::RenderWindow& window)
{
    window.draw(_laneRect);
}

void SpaceLane::SetPos(sf::Vector2f pos)
{
    _laneRect.setPosition(pos);
}

void SpaceLane::SetColour(sf::Color colour)
{
    //_laneRect.setOutlineColor(colour);
    _laneRect.setFillColor(colour);
}

void SpaceLane::SetSize(sf::Vector2f size)
{
    _laneRect.setSize(size);
}

sf::Vector2f SpaceLane::GetPos()
{
    return _laneRect.getPosition();
}

float SpaceLane::GetCentreYPos()
{
    return _laneRect.getPosition().y + _laneRect.getSize().y / 2.0F;
}

sf::Vector2f SpaceLane::GetSize()
{
    return _laneRect.getSize();
}



