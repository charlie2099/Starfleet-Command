#include "Starship.hpp"

Starship::Starship(Type type) : ship_type(type)
{
    switch(type)
    {
        case Type::FIGHTER:
            spriteComponent.loadSprite("images/starfleet_ship_fighternew2.png");
            break;
        case Type::REPAIR:
            spriteComponent.loadSprite("images/starfleet_ship_repairnew2.png");
            break;
        case Type::DESTROYER:
            spriteComponent.loadSprite("images/starfleet_ship_destroyernew2.png");
            break;
        case Type::BATTLESHIP:
            spriteComponent.loadSprite("images/starfleet_ship_battleshipnew2.png");
            break;
        case Type::FLAGSHIP:
            spriteComponent.loadSprite("images/starfleet_ship_flagshipnew3.png");
            break;
    }
    spriteComponent.getSprite().scale({0.05F, 0.05F});
}

void Starship::render(sf::RenderWindow &window)
{
    window.draw(spriteComponent.getSprite());
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

SpriteComponent &Starship::getSpriteCompo()
{
    return spriteComponent;
}


