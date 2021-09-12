#include "Battleship.hpp"

Battleship::Battleship()
{
    spriteComponent.loadSprite("images/starfleet_ship_battleship.png");
    spriteComponent.getSprite().scale(sf::Vector2<float>{0.15F,0.15F});
    setHealth(1200);
    setDamage(200);
    setSpeed(12);
    setAcceleration(1);
}

void Battleship::render(sf::RenderWindow &window)
{
    window.draw(spriteComponent.getSprite());
}

SpriteComponent &Battleship::getSpriteComp()
{
    return spriteComponent;
}