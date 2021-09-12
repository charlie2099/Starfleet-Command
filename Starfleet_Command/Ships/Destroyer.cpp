#include "Destroyer.hpp"

Destroyer::Destroyer()
{
    spriteComponent.loadSprite("images/starfleet_ship_destroyer.png");
    spriteComponent.getSprite().scale(sf::Vector2<float>{0.15F,0.15F});
    setHealth(600);
    setDamage(500);
    setSpeed(16);
    setAcceleration(1);
}

void Destroyer::render(sf::RenderWindow &window)
{
    window.draw(spriteComponent.getSprite());
}

SpriteComponent &Destroyer::getSpriteComp()
{
    return spriteComponent;
}