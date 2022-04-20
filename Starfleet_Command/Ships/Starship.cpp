#include "Starship.hpp"

Starship::Starship(Type type) : ship_type(type)
{
    switch(type)
    {
        case Type::FIGHTER:
            spriteComponent.loadSprite("images/starfleet_ship_fighter.png");
            spriteComponent.getSprite().scale({0.05F, 0.05F});
            _speed = 100;
            break;
        case Type::REPAIR:
            spriteComponent.loadSprite("images/starfleet_ship_repair.png");
            spriteComponent.getSprite().scale({0.05F, 0.05F});
            _speed = 80;
            break;
        case Type::DESTROYER:
            spriteComponent.loadSprite("images/starfleet_ship_destroyer.png");
            spriteComponent.getSprite().scale({0.05F, 0.05F});
            _speed = 40;
            break;
        case Type::BATTLESHIP:
            spriteComponent.loadSprite("images/starfleet_ship_battleship.png");
            spriteComponent.getSprite().scale({0.05F, 0.05F});
            _speed = 40;
            break;
        case Type::FLAGSHIP:
            spriteComponent.loadSprite("images/starfleet_ship_flagship.png");
            spriteComponent.getSprite().scale({0.10F, 0.10F});
            _speed = 20;
            break;
    }
    //spriteComponent.getSprite().scale({0.05F, 0.05F});

    /// Change default origin to center
    sf::Vector2<float> centered_origin;
    centered_origin.x = spriteComponent.getSprite().getLocalBounds().width/2;
    centered_origin.y = spriteComponent.getSprite().getLocalBounds().height/2;
    spriteComponent.getSprite().setOrigin(centered_origin);
}

void Starship::Update(sf::RenderWindow &window, sf::Time deltaTime)
{

}

void Starship::Render(sf::RenderWindow &window)
{
    window.draw(spriteComponent.getSprite());
}

void Starship::SetHealth(float health)
{
    health_ = health;
}

void Starship::SetDamage(float damage)
{
    damage_ = damage;
}

void Starship::SetSpeed(float speed)
{
    _speed = speed;
}

void Starship::SetAcceleration(float acceleration)
{
    acceleration_ = acceleration;
}

float Starship::GetHealth() const
{
    return health_;
}

float Starship::GetDamage() const
{
    return damage_;
}

float Starship::GetSpeed() const
{
    return _speed;
}

float Starship::GetAcceleration() const
{
    return acceleration_;
}

SpriteComponent &Starship::GetSpriteComponent()
{
    return spriteComponent;
}

std::vector<std::unique_ptr<Projectile>>& Starship::GetProjectile()
{
    return projectile;
}

void Starship::MoveTowards(sf::Vector2f target, sf::Time deltaTime)
{
    auto& ship_sprite = spriteComponent.getSprite();

    sf::Vector2f ship_dir = Chilli::Vector::Normalize(target - ship_sprite.getPosition());
    sf::Vector2f ship_move = ship_dir * _speed;
    float ship_rot = atan2(ship_dir.y, ship_dir.x) * 180 / 3.141;

    ship_sprite.move(ship_move * deltaTime.asSeconds());
    ship_sprite.setRotation(ship_rot);
}




