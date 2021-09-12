#include "RepairShip.hpp"

RepairShip::RepairShip()
{
    spriteComponent.loadSprite("images/starfleet_ship_repair.png");
    spriteComponent.getSprite().scale(sf::Vector2<float>{0.1F,0.1F});
    setHealth(400);
    setDamage(0);
    setSpeed(14);
    setAcceleration(1);
}

void RepairShip::render(sf::RenderWindow &window)
{
    window.draw(spriteComponent.getSprite());
}

SpriteComponent &RepairShip::getSpriteComp()
{
    return spriteComponent;
}