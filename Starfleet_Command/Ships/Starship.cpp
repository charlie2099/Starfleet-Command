#include "Starship.hpp"

/*Starship::Starship()
{
    spriteComponent.loadSprite("images/starfleet_ship.png");
}*/

void Starship::render(sf::RenderWindow &/*window*/)
{
    //window.draw(spriteComponent.getSprite());
}

void Starship::setHealth(float health)
{
    health_ = health;
}

void Starship::setDamage(float damage)
{
    damage_ = damage;
}

void Starship::setSpeed(float speed)
{
    speed_ = speed;
}

void Starship::setAcceleration(float acceleration)
{
    acceleration_ = acceleration;
}

float Starship::getHealth() const
{
    return health_;
}

float Starship::getDamage() const
{
    return damage_;
}

float Starship::getSpeed() const
{
    return speed_;
}

float Starship::getAcceleration() const
{
    return acceleration_;
}


