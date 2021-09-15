#include "LightFighter.hpp"

LightFighter::LightFighter(int health) : health_test_(health)
{
    spriteComponent.loadSprite("images/starfleet_ship_fighter.png");
    spriteComponent.getSprite().scale(sf::Vector2<float>{0.1F,0.1F});
    setHealth(200);
    setDamage(50);
    setSpeed(20);
    setAcceleration(1);
}

void LightFighter::render(sf::RenderWindow &window)
{
    window.draw(spriteComponent.getSprite());
}

SpriteComponent &LightFighter::getSpriteComp()
{
    return spriteComponent;
}
