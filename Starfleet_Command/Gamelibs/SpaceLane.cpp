#include "SpaceLane.hpp"

bool SpaceLane::Init()
{
    laneRect.setOutlineThickness(5.0F);
    laneRect.setOutlineColor(sf::Color(0,0,255,50));
    laneRect.setFillColor(sf::Color::Transparent);
    laneRect.setSize({2500.0F, 50.0F});

    return true;
}

void SpaceLane::Update(sf::RenderWindow& window, sf::Time deltaTime)
{

}

void SpaceLane::Render(sf::RenderWindow& window)
{
    window.draw(laneRect);
}

void SpaceLane::SetPos(sf::Vector2f pos)
{
    laneRect.setPosition(pos);
}

void SpaceLane::SetColour(sf::Color colour)
{
    laneRect.setOutlineColor(colour);
}

sf::Vector2f SpaceLane::GetPos()
{
    return laneRect.getPosition();
}

float SpaceLane::GetCentreYPos()
{
    return laneRect.getPosition().y + laneRect.getSize().y/2.0F;
}

sf::Vector2f SpaceLane::GetSize()
{
    return laneRect.getSize();
}

