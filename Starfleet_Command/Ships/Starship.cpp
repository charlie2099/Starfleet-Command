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
        case Type::FLAGSHIP:
            spriteComponent.loadSprite("images/starfleet_ship_flagship.png");
            break;
    }
    spriteComponent.getSprite().scale({0.05F, 0.05F});

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = spriteComponent.getSprite().getLocalBounds().width/2;
    centered_origin.y = spriteComponent.getSprite().getLocalBounds().height/2;
    spriteComponent.getSprite().setOrigin(centered_origin);
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

SpriteComponent &Starship::getSpriteComponent()
{
    return spriteComponent;
}

std::vector<std::unique_ptr<Projectile>>& Starship::getProjectile()
{
    return projectile;
}


