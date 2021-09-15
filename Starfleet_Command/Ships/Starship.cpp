#include "Starship.hpp"

Starship::Starship(Type type) : ship_type(type)
{
    switch(type)
    {
        case Type::FIGHTER:
            spriteComponent.loadSprite("images/starfleet_ship_fighter.png");
            break;
        case Type::REPAIR:
            spriteComponent.loadSprite("images/starfleet_ship_repair.png");
            break;
        case Type::DESTROYER:
            spriteComponent.loadSprite("images/starfleet_ship_destroyer.png");
            break;
        case Type::BATTLESHIP:
            spriteComponent.loadSprite("images/starfleet_ship_battleship.png");
            break;
        /*case Type::FLAGSHIP:
            spriteComponent.loadSprite("images/starfleet_ship_command.png");
            spriteComponent.getSprite().scale({0.1F, 0.1F});
            break;*/
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


